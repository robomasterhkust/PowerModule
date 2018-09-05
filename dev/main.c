/*******************************************************************************
 *    This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *******************************************************************************/
/*
 * main.c
 *
 *  Created on: 5 Jul 2018    #DeadlineFighter
 *  Author: Alex's Desktop
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
