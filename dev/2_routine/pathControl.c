/*
 * pathControl.c
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "pathControl.h"
#include "pathSwitch.h"

pathType path[1];

static THD_WORKING_AREA(pathSwitchThd_wa, 1024);
static THD_FUNCTION(pathSwitchThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(100);

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
