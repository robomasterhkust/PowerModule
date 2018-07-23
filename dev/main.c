/*
 * main.c
 *
 *  Created on: 5 Jul 2018
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
#include "bxCAN.h"
#include "canFeedback.h"

int main(void) {

  //ChibiOS init
  halInit();
  chSysInit();

  //Driver init
  can_processInit();
  LEDinit();

  //Routine init
  pathMonitorInit();
  buckInit();
  voltMoninit();
  pathControlInit();
  canFeedbackInit();

  while (true) {

    chThdSleepMilliseconds(100);

  }
}
