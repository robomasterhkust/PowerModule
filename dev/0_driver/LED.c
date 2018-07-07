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
