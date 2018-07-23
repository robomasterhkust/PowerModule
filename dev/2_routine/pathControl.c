/*
 * pathControl.c
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"
#include "pathMonitor.h"
#include "buckProg.h"
#include "MCP4726.h"
#include "adcDriver.h"
#include "voltMonitor.h"
#include "pathControl.h"
#include "pathSwitch.h"
#include "LED.h"
#include "bxCAN.h"

pathData_t pathData;
pidData_t buckPid;
userCommand_t* userCommand;

uint32_t timeoutCount = 0;

pathData_t* returnPathData(void) {

	return &pathData;

}

static THD_WORKING_AREA(pidCalcThd_wa, 1024);
static THD_FUNCTION(pidCalcThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  buckPid.kP = 1;
  buckPid.kI = 0.2;
  buckPid.kD = 0;
  buckPid.last_error = 0;
  buckPid.maxTarget = pathData.riseThresh - pathData.chargeMargin;
  buckPid.maxOut = 500;
  buckPid.maxMilliVolt = 23200;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(1000);

    buckPid.fb = pathData.buckPower;
    buckPid.error = buckPid.target - pathData.buckPower;
    buckPid.p = buckPid.error * buckPid.kP;
    buckPid.d = (buckPid.error - buckPid.last_error) * buckPid.kD;
    buckPid.i = buckPid.accumError * buckPid.kI;
    buckPid.out = buckPid.p + buckPid.i + buckPid.d;
    buckPid.out = buckPid.out > buckPid.maxOut ? buckPid.maxOut : buckPid.out;
    buckPid.accumError += buckPid.out == buckPid.maxOut ? 0 : buckPid.error * buckPid.kI;
    buckPid.accumError = pathData.voltage->vcapMv > buckPid.maxMilliVolt ? 0 : buckPid.accumError;
    buckPid.out = buckPid.out < 0 ? 0 : buckPid.out;
    pathData.buckProg->mV = buckPid.out;
    buckPid.last_error = buckPid.error;

    chThdSleepUntilWindowed(now, next);

  }

}

static THD_WORKING_AREA(pathCalcThd_wa, 1024);
static THD_FUNCTION(pathCalcThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  static int32_t target;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(100);

    pathData.judgePower = -pathData.current->pathA.current * pathData.voltage->vinMv / 1000000;
    pathData.outPower = pathData.voltage->ioutMa * pathData.voltage->voutMv / 1000000;
    pathData.buckPower = -pathData.current->pathB.current * pathData.voltage->vinMv / 1000000;

    pathData.capEnergy = pathData.capacitance / 2 *
    										 (((pathData.voltage->vcapMv / 1000)^2) - ((pathData.VcapMin / 1000)^2));

    target = pathData.path == JUDGE ?
    				 pathData.riseThresh - pathData.chargeMargin - pathData.outPower :		//Judge Power
						 pathData.riseThresh - pathData.chargeMargin;													//Cap Power
						 //0;

    target = target > buckPid.maxOut ? buckPid.maxOut : target;
    target = target < 0 ? 0 : target;

    buckPid.target = target;

    chThdSleepUntilWindowed(now, next);

  }

}

static THD_WORKING_AREA(pathSwitchThd_wa, 1024);
static THD_FUNCTION(pathSwitchThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  pathData.riseThresh = 75;
  pathData.fallThresh = 55;
  pathData.deadTime = 200;
  pathData.chargeMargin = 5;
  pathData.capacitance = 11.1;
  pathData.VcapMin = 14000;

  pathData.buckProg = buckData();
  pathData.current = pathMonitorData();
  pathData.voltage = voltMonData();

  chThdCreateStatic(pathCalcThd_wa, sizeof(pathCalcThd_wa),
                    NORMALPRIO + 13, pathCalcThd, NULL);

  chThdCreateStatic(pidCalcThd_wa, sizeof(pidCalcThd_wa),
  									NORMALPRIO + 11, pidCalcThd, NULL);

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(100);

    //Auto path switch

//		if((pathData.path == JUDGE) && (pathData.judgePower > pathData.riseThresh)) {
//			pathData.path = BOOST;
//			//pathSwitch(pathData.path);
//			pal_lld_writegroup(GPIOB, 0b111, 12, PATHBOOST);
//			//pathData.lockTill = now + pathData.deadTime;
//			next += MS2ST(pathData.deadTime);
//		} else if ((pathData.path == BOOST) && (pathData.outPower < pathData.fallThresh)) {
//			pathData.path = JUDGE;
//			//pathSwitch(pathData.path);
//			pal_lld_writegroup(GPIOB, 0b111, 12, PATHJUDGE);
//			//pathData.lockTill = now + pathData.deadTime;
//			next += MS2ST(pathData.deadTime);
//		}

    //Manual path switch

    timeoutCount += 1 - userCommand->msgUpdated;

    if (userCommand->msgUpdated) {
    	pathData.path = userCommand->pathType;
			userCommand->msgUpdated = 0;
			timeoutCount = 0;
    } else if (timeoutCount > TIMEOUTCNT) {
    	pathData.path = JUDGE;
    }

    if (pathData.voltage->vcapMv < pathData.VcapMin) {
    	pathData.path = JUDGE;
    }

    pathSwitch(pathData.path);

    chThdSleepUntilWindowed(now, next);

  }

}

void pathControlInit(void) {

  pathData.path = JUDGE;

  userCommand = returnCommand();

  pathSwitchInit();

  chThdCreateStatic(pathSwitchThd_wa, sizeof(pathSwitchThd_wa),
                    NORMALPRIO + 12, pathSwitchThd, NULL);

}
