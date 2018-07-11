/*
 * buckProg.c
 *
 *  Created on: 11 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "buckProg.h"
#include "MCP4726.h"

static dac_t dac;

static THD_WORKING_AREA(buckProgThd_wa, 1024);
static THD_FUNCTION(buckProgThd, p) {

  (void)p;

  while(true) {

    for (uint16_t i = 0; i < 40; i++) {
      chThdSleep(US2ST(500));
      dac.dacVal = i * 100;
      dacUpdate(&dac);
    }

  }

}

void buckInit(void) {

  dacInit(&dac);

  chThdCreateStatic(buckProgThd_wa, sizeof(buckProgThd_wa),
                      NORMALPRIO + 6, buckProgThd, NULL);

}
