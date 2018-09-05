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
 *
 * MCP4726.c
 *
 *  Created on: 11 Jul 2018
 *  Author: Alex's Desktop
 *
 */

#include "ch.h"
#include "hal.h"
#include "MCP4726.h"

static uint8_t tx_data[4];
static uint8_t rx_data[4];

static const I2CConfig i2cfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

void dacInit(dac_t* dac) {

  dac->driver = &I2CD1;
  palSetPadMode(SDAPORT, SDAPIN, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(SCLPORT, SCLPIN, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  i2cStart(dac->driver, &i2cfg);

  //[7:5] W/ all mem, [4:3] vref = vcc, [2:1] power on, [0] gain = 1
  tx_data[0] = 0b01100000;
  //[7:0] for DAC[11:4]
  tx_data[1] = 0b00000000;
  //[7:4] for DAC[3:0], [3:0] don't care
  tx_data[2] = 0b00000000;

  i2cAcquireBus(dac->driver);
  i2cMasterTransmitTimeout(dac->driver, DACADDR,
                           tx_data, 3, rx_data, 0, MS2ST(5));
  i2cReleaseBus(dac->driver);

}

void dacUpdate(dac_t* dac) {

  //[7:6] W/ DAC, [5:4] power on, [3:0] for DAC[11:8]
  tx_data[0] = (dac->dacVal >> 8) & 0b00001111;
  //[7:0] for DAC[7:0]
  tx_data[1] = dac->dacVal & 0b11111111;

  i2cAcquireBus(dac->driver);
  i2cMasterTransmitTimeout(dac->driver, DACADDR,
                           tx_data, 2, rx_data, 0, MS2ST(5));
  i2cReleaseBus(dac->driver);

}
