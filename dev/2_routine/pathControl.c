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

pathType path[1];
dac_t* buckProg;
pathStatus* current;
voltages* voltage;

#define riseThd				500	//mA
#define fallThd				350	//mA

static THD_WORKING_AREA(pathSwitchThd_wa, 1024);
static THD_FUNCTION(pathSwitchThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  buckProg = buckData();
  current = pathMonitorData();
  voltage = voltMonData();

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(100);

    if((path[0] == JUDGE) && (current->pathA.current > riseThd)) {
    	path[0] = BOOST;
    } else if ((path[0] == BOOST) && (current->pathA.current < fallThd)) {
    	path[0] = JUDGE;
    }

    pathSwitch(path[0]);

    chThdSleepUntilWindowed(now, next);

  }

}

void pathControlInit(void) {

  path[0] = DIODE;

  pathSwitchInit();

  chThdCreateStatic(pathSwitchThd_wa, sizeof(pathSwitchThd_wa),
                    NORMALPRIO + 12, pathSwitchThd, NULL);

}
