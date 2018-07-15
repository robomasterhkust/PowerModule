/*
 * pathControl.h
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef PATHCONTROL_H_
#define PATHCONTROL_H_

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"
#include "pathMonitor.h"
#include "buckProg.h"
#include "MCP4726.h"
#include "adcDriver.h"
#include "voltMonitor.h"
#include "pathControl.h"
#include "pathSwitch.h"
#include "LED.h"

typedef struct pathData_t{

  uint16_t riseThresh;       //W
  uint16_t fallThresh;       //W
  uint16_t deadTime;
  systime_t lockTill;
  int32_t judgePower;
  int32_t outPower;
  pathType path;
  dac_t* buckProg;
  pathStatus* current;
  voltages* voltage;

}pathData_t;

void pathControlInit(void);

#endif /* 2_ROUTINE_INC_PATHCONTROL_H_ */
