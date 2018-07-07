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
