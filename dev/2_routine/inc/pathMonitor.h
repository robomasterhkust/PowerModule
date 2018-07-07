/*
 * pathMonitor.h
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef PATHMONITOR_H_
#define PATHMONITOR_H_

#include "TLI4970.h"

typedef struct pathStatus{

  currentSensor pathA;
  currentSensor pathB;

}pathStatus;

pathStatus* pathMonitorGet(void);
void pathMonitorInit(void);

#endif /* 2_ROUTINE_INC_PATHMONITOR_H_ */
