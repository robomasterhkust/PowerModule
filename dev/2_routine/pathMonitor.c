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
 * pathMonitor.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "pathMonitor.h"
#include "TLI4970.h"

static pathStatus currentPath;

static THD_WORKING_AREA(pathMonitorThd_wa, 1024);
static THD_FUNCTION(pathMonitorThd, p) {

  (void)p;

  static systime_t now = 0;
  static systime_t next = 0;

  while(true) {

    now = chVTGetSystemTime();
    next = now + US2ST(1000);
    currentSensorUpdate(&(currentPath.pathA), &aSpiCfg,
                        &(currentPath.pathB), &bSpiCfg);
    chThdSleepUntilWindowed(now, next);

  }

}

pathStatus* pathMonitorData(void) {

	return &currentPath;

}

void pathMonitorInit(void) {

  currentSensorInit(&(currentPath.pathA), &aSpiCfg);
  currentSensorInit(&(currentPath.pathB), &bSpiCfg);

  chThdCreateStatic(pathMonitorThd_wa, sizeof(pathMonitorThd_wa),
                    NORMALPRIO + 10, pathMonitorThd, NULL);

}
