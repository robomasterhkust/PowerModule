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
 * ADC.h
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef ADCDRIVER_H_
#define ADCDRIVER_H_

#define ADCNUMCH            5
#define ADCDEPTH            10

#define TEMPSCALE           0.187363735f
#define TEMPOFFSET          357.5881395f

#define ADC2MV              8.862304688f

#define ADC2MA              16.11328125f
#define MAOFFSET            12500

typedef struct voltages{

  uint16_t tempC;
  uint16_t vinMv;
  uint16_t vcapMv;
  uint16_t voutMv;
  int32_t ioutMa;

} voltages;

void adcDriverInit(void);
void adcDriverUpdate(voltages* data);

#endif /* 0_DRIVER_INC_ADC_H_ */
