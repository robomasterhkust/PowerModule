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

voltages* voltMonData(void) {

	return &voltData;

}

void voltMoninit(void) {

  adcDriverInit();

  chThdCreateStatic(voltMonThd_wa, sizeof(voltMonThd_wa),
                      NORMALPRIO + 5, voltMonThd, NULL);

}

