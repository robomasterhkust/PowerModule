/*
 * main.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"
#include "LED.h"

int main(void) {

  //ChibiOS init
  halInit();
  chSysInit();

  //Driver init
  LEDinit();

  //Routine init
  pathMonitorInit();

  while (true) {

    LEDon();
    chThdSleepMilliseconds(100);
    LEDoff();
    chThdSleepMilliseconds(100);

  }
}
