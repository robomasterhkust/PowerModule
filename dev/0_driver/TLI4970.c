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
 * TLI4970.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 *
 *  SPI RX only mode does not fking work,
 *  took me 2 days to figure that out
 *
 */

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"

void currentSensorInit(currentSensor* sensor, const SPIConfig* cfg) {

  sensor->driver = &SPID1;

  palSetPadMode(cfg->ssport, cfg->sspad, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(cfg->ssport, cfg->sspad);

  spiStart(sensor->driver, cfg);

}

uint16_t currentSensorSample(currentSensor* sensor, const SPIConfig* cfg) {

  static uint16_t data;

  spiAcquireBus(sensor->driver);
  spiStart(sensor->driver, cfg);
  spiSelect(sensor->driver);
  spiReceive(sensor->driver, 1, &data);
  spiUnselect(sensor->driver);
  spiReleaseBus(sensor->driver);

  if (((data >> 15) & 1) == TLI4970_NORMAL_ID) {
    uint16_t parity = data & 0x1FFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    if (((data >> 14) & 1) == parity) {
      sensor->error = 0;
      sensor->rawCurrent = data & 0x1FFF;
    }
  } else {
    uint16_t parity = data & 0xFFFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    if (((data >> 14) & 1) == parity) {
      sensor->error = data;
    }
  }

  return sensor->rawCurrent;

}
//sensor->current = (sensor->rawCurrent - TLI4970_D025_OFFSET) * TLI4970_D025_LSB2MA;

void currentSensorUpdate(currentSensor* sensorA, const SPIConfig* cfgA,
                         currentSensor* sensorB, const SPIConfig* cfgB) {

  int32_t avgA = 0;
  int32_t avgB = 0;

  for (uint8_t i = 0; i < CURRENTSAMPLES; i++) {

    avgA += currentSensorSample(sensorA, cfgA);
    avgB += currentSensorSample(sensorB, cfgB);

  }

  sensorA->current = ((avgA / CURRENTSAMPLES) - TLI4970_D025_OFFSET) * TLI4970_D025_LSB2MA;
  sensorB->current = ((avgB / CURRENTSAMPLES) - TLI4970_D025_OFFSET) * TLI4970_D025_LSB2MA;

}
