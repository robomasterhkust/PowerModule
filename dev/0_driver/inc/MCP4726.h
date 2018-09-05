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
#ifndef MCP4726_H_
#define MCP4726_H_

#define SDAPORT     GPIOB
#define SCLPORT     GPIOB

#define SDAPIN      7
#define SCLPIN      6

//Refer to part order code and datasheet for slave address
#define DACADDR     0b1100000

typedef struct dac_t{

  I2CDriver* driver;
  uint16_t mV;
  uint16_t dacVal;

}dac_t;

void dacInit(dac_t* dac);
void dacUpdate(dac_t* dac);

#endif
