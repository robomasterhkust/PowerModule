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
