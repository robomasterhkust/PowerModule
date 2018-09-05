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
#ifndef TLI4970_H_
#define TLI4970_H_

#define TLI4970_NORMAL_ID       (uint16_t)0
#define TLI4970_D025_OFFSET     4096
#define TLI4970_D025_LSB2MA     12.5f

#define CURRENTSAMPLES          20

typedef struct currentSensor{

  SPIDriver* driver;
  uint16_t error;
  uint16_t rawData;
  uint16_t rawCurrent;
  int32_t current;      //mA

} currentSensor;

typedef struct spiDriver_t{

  SPIDriver* driver;
  ioportid_t port;
  uint16_t pad;
  uint16_t data;
  uint8_t flag;

} spiDriver_t;

void currentSensorInit(currentSensor* sensor, const SPIConfig* cfg);
void currentSensorUpdate(currentSensor* sensorA, const SPIConfig* cfgA,
                         currentSensor* sensorB, const SPIConfig* cfgB);

#endif
