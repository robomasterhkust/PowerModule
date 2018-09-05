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
 * pathSwitch.h
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef PATHSWITCH_H_
#define PATHSWITCH_H_

#define PATHSWPORT          GPIOB
#define PATHDIODE           0b000
#define PATHJUDGE           0b101
#define PATHBOOST           0b011

typedef enum {

  DIODE = 0,
  JUDGE = 1,
  BOOST = 2

} pathEnum;

void pathSwitchInit(void);
void pathSwitch(pathEnum path);

#endif /* 0_DRIVER_INC_PATHSWITCH_H_ */
