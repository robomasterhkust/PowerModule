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
 * LED.h
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef LED_H_
#define LED_H_

#define LEDoff()        palSetPad(GPIOA, 15)
#define LEDon()         palClearPad(GPIOA, 15)

void LEDinit(void);

#endif /* 0_DRIVER_INC_LED_H_ */
