/*
 * pathMonitor.h
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef PATHMONITOR_H_
#define PATHMONITOR_H_

#include "TLI4970.h"

static const SPIConfig aSpiCfg = {
    NULL,
    GPIOB,
    1,
    SPI_CR1_MSTR | SPI_CR1_DFF | SPI_CR1_BR_1 | SPI_CR1_BR_0 |
    SPI_CR1_CPHA | SPI_CR1_SSM
};

static const SPIConfig bSpiCfg = {
    NULL,
    GPIOB,
    0,
    SPI_CR1_MSTR | SPI_CR1_DFF | SPI_CR1_BR_1 | SPI_CR1_BR_0 |
    SPI_CR1_CPHA | SPI_CR1_SSM
};

typedef struct pathStatus{

  currentSensor pathA;
  currentSensor pathB;

}pathStatus;

pathStatus* pathMonitorGet(void);
void pathMonitorInit(void);

#endif /* 2_ROUTINE_INC_PATHMONITOR_H_ */
