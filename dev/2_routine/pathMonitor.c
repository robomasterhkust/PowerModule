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

static THD_WORKING_AREA(pathMonitorThd_wa, 512);
static THD_FUNCTION(pathMonitorThd, p) {

  (void)p;

  while(!chThdShouldTerminateX()) {

    currentSensorUpdate(&(currentPath.pathA));
    currentSensorUpdate(&(currentPath.pathB));
    chThdSleep(MS2ST(1));

  }

}

void pathMonitorInit(void) {

  //memset((void*)&currentPath, 0, sizeof(pathStatus));

  currentSensorInit(&(currentPath.pathA), GPIOA, 7);
  currentSensorInit(&(currentPath.pathB), GPIOB, 0);

  chThdCreateStatic(pathMonitorThd_wa, sizeof(pathMonitorThd_wa),
                    NORMALPRIO + 10, pathMonitorThd, NULL);

}
