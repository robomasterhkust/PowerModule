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

pathData_t pathData;

static THD_WORKING_AREA(pathCalcThd_wa, 1024);
static THD_FUNCTION(pathCalcThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(100);

    pathData.judgePower = -pathData.current->pathA.current * pathData.voltage->vinMv / 1000000;
    pathData.outPower = pathData.voltage->ioutMa * pathData.voltage->voutMv / 1000000;

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

  pathData.buckProg = buckData();
  pathData.current = pathMonitorData();
  pathData.voltage = voltMonData();

  chThdCreateStatic(pathCalcThd_wa, sizeof(pathCalcThd_wa),
                    NORMALPRIO + 13, pathCalcThd, NULL);

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(100);

//    pathData.judgePower = -pathData.current->pathA.current * pathData.voltage->vinMv / 1000000;
//    pathData.outPower = pathData.voltage->ioutMa * pathData.voltage->voutMv / 1000000;

    if(true) {
      if((pathData.path == JUDGE) && (pathData.judgePower > pathData.riseThresh)) {
        pathData.path = BOOST;
        //pathSwitch(pathData.path);
        pal_lld_writegroup(GPIOB, 0b111, 12, PATHBOOST);
        //pathData.lockTill = now + pathData.deadTime;
        next += MS2ST(pathData.deadTime);
      } else if ((pathData.path == BOOST) && (pathData.outPower < pathData.fallThresh)) {
        pathData.path = JUDGE;
        //pathSwitch(pathData.path);
        pal_lld_writegroup(GPIOB, 0b111, 12, PATHJUDGE);
        //pathData.lockTill = now + pathData.deadTime;
        next += MS2ST(pathData.deadTime);
      }
    }

    chThdSleepUntilWindowed(now, next);

  }

}

void pathControlInit(void) {

  pathData.path = JUDGE;

  pathSwitchInit();

  chThdCreateStatic(pathSwitchThd_wa, sizeof(pathSwitchThd_wa),
                    NORMALPRIO + 12, pathSwitchThd, NULL);

}
