/*
 * pathSwitch.c
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "pathSwitch.h"
#include "LED.h"

void pathSwitchInit(void) {

  palSetPadMode(PATHSWPORT, 12, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(PATHSWPORT, 13, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(PATHSWPORT, 14, PAL_MODE_OUTPUT_PUSHPULL);
  pal_lld_writegroup(GPIOB, 0b111, 12, PATHDIODE);

}

void pathSwitch(pathEnum path){

	chSysLock();

  switch(path) {

  case DIODE :
    pal_lld_writegroup(GPIOB, 0b111, 12, PATHDIODE);
    break;

  case JUDGE :
    pal_lld_writegroup(GPIOB, 0b111, 12, PATHJUDGE);
    LEDoff();
    break;

  case BOOST :
    pal_lld_writegroup(GPIOB, 0b111, 12, PATHBOOST);
    LEDon();
    break;

  }

  chSysUnlock();

}
