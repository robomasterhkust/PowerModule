/*
 * pathSwitch.c
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "pathSwitch.h"

void pathSwitchInit(void) {

  palSetPadMode(PATHSWPORT, 12, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(PATHSWPORT, 13, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(PATHSWPORT, 14, PAL_MODE_OUTPUT_PUSHPULL);
  pal_lld_writegroup(GPIOB, 0b111, 12, PATHDIODE);

}

void pathSwitch(pathType path){

  switch(path) {

  case DIODE :
    pal_lld_writegroup(GPIOB, 0b111, 12, PATHDIODE);
    break;

  case JUDGE :
    pal_lld_writegroup(GPIOB, 0b111, 12, PATHJUDGE);
    break;

  case BOOST :
    pal_lld_writegroup(GPIOB, 0b111, 12, PATHBOOST);
    break;

  }

}
