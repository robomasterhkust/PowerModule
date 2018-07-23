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
