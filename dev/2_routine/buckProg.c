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

    dac.dacVal = (uint16_t) dac.mV * MV2DAC;
    dacUpdate(&dac);
    chThdSleep(US2ST(100));

  }

}

void buckInit(void) {

  dacInit(&dac);

  chThdCreateStatic(buckProgThd_wa, sizeof(buckProgThd_wa),
                      NORMALPRIO + 6, buckProgThd, NULL);

}
