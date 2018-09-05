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
 * LED.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "LED.h"

/*
 * LED connected to PA15, which is mapped to JTDI by default
 * This function remaps PA15 to GPIO
 */
void LEDinit(void) {

  uint32_t afio = AFIO->MAPR & 0xF8FFFFFF;
  afio |= 0x2000000;
  AFIO->MAPR = afio;
  palSetPadMode(GPIOA, 15, PAL_MODE_OUTPUT_PUSHPULL);

}
