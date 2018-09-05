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
 * buckProg.h
 *
 *  Created on: 11 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef BUCKPROG_H_
#define BUCKPROG_H_

#include "MCP4726.h"

#define MV2DAC      1.241212f

dac_t* buckData(void);
void buckInit(void);

#endif /* 2_ROUTINE_INC_BUCKPROG_H_ */
