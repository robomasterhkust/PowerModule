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

#define TIMEOUTCNT		150			// 1 count = 100us

#define MARGINFINAL		10
#define RISETHRESH		75
#define RAMPTIME			20000		//ms

typedef struct pathData_t{

  uint16_t riseThresh;       //W
  uint16_t fallThresh;       //W
  uint16_t chargeMargin;
  uint16_t deadTime;
  systime_t lockTill;
  int32_t buckPower;
  int32_t judgePower;
  int32_t outPower;
  pathEnum path;
  dac_t* buckProg;
  pathStatus* current;
  voltages* voltage;
  int16_t capEnergy;
  int16_t capacitance;
  uint16_t VcapMin;
  uint8_t sysInit;

}pathData_t;

typedef struct pidData_t {

	float kP;
	float kI;
	float kD;
	float p;
	float i;
	float iDecay;
	float d;
	int32_t fb;
	int32_t out;
	int32_t target;
	int32_t error;
	int32_t accumError;
	int32_t last_error;
	int32_t maxOut;
	int32_t maxTarget;
	uint16_t maxMilliVolt;

} pidData_t;

pathData_t* returnPathData(void);
void pathControlInit(void);

#endif /* 2_ROUTINE_INC_PATHCONTROL_H_ */
