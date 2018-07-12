/*
 * pathMonitor.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "pathMonitor.h"
#include "TLI4970.h"

static pathStatus currentPath;

static THD_WORKING_AREA(pathMonitorThd_wa, 1024);
static THD_FUNCTION(pathMonitorThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(1000);
    currentSensorUpdate(&(currentPath.pathA), &aSpiCfg,
                        &(currentPath.pathB), &bSpiCfg);
    chThdSleepUntilWindowed(now, next);

  }

}

void pathMonitorInit(void) {

  currentSensorInit(&(currentPath.pathA), &aSpiCfg);
  currentSensorInit(&(currentPath.pathB), &bSpiCfg);

  chThdCreateStatic(pathMonitorThd_wa, sizeof(pathMonitorThd_wa),
                    NORMALPRIO + 10, pathMonitorThd, NULL);

}
