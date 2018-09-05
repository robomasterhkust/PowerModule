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

pathStatus* pathMonitorData(void);
void pathMonitorInit(void);

#endif /* 2_ROUTINE_INC_PATHMONITOR_H_ */
