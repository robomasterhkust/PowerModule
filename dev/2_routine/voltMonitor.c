/*
 * voltMonitor.c
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "adcDriver.h"

static voltages voltData;

static THD_WORKING_AREA(voltMonThd_wa, 1024);
static THD_FUNCTION(voltMonThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(1000);
    adcDriverUpdate(&voltData);
    chThdSleepUntilWindowed(now, next);

  }

}

void voltMoninit(void) {

  adcDriverInit();

  chThdCreateStatic(voltMonThd_wa, sizeof(voltMonThd_wa),
                      NORMALPRIO + 5, voltMonThd, NULL);

}

