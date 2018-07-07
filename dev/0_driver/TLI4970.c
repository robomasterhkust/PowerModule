/*
 * TLI4970.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"

void currentSensorInit(currentSensor* sensor, const ioportid_t port, const uint16_t pad) {

	sensor->port = port;
  sensor->pad = pad;
  palSetPadMode(sensor->port, sensor->pad, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(sensor->port, sensor->pad);

  if (sensor->driver->state == SPI_UNINIT) {
    SPIConfig tli4970SpiCfg = {
      NULL,
      port,
      pad,
      SPI_CR1_MSTR | SPI_CR1_DFF | SPI_CR1_BR_1 | SPI_CR1_BR_0 |
      SPI_CR1_BIDIMODE | SPI_CR1_RXONLY
    };
    sensor->driver->rxdmamode |= STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD;
    spiStart(sensor->driver, &tli4970SpiCfg);
  }

}

void currentSensorUpdate(currentSensor* sensor){

  uint16_t data = 0;

  spiAcquireBus(sensor->driver);

  //slave select
  osalDbgCheck(sensor->driver != NULL);
  osalSysLock();
  osalDbgAssert(sensor->driver->state == SPI_READY, "not ready");
  palClearPad(sensor->port, sensor->pad);
  osalSysUnlock();

  spiReceive(sensor->driver, 1, &data);

  //slave unselect
  osalDbgCheck(sensor->driver != NULL);
  osalSysLock();
  osalDbgAssert(sensor->driver->state == SPI_READY, "not ready");
  palSetPad(sensor->port, sensor->pad);
  osalSysUnlock();

  //release ownership of bus
  spiReleaseBus(sensor->driver);

  if (((data >> 15) & 1) == TLI4970_NORMAL_ID) {
    uint16_t parity = data & 0x1FFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    if (((data >> 14) & 1) == parity) {
      sensor->error = 0;
      sensor->raw_current = data & 0x1FFF;
      sensor->current = (sensor->raw_current - TLI4970_D025_OFFSET) * TLI4970_D025_LSB2MA;
    }
  } else {
    uint16_t parity = data & 0xFFFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    if (((data >> 14) & 1) == parity) {
      sensor->error = data & 0x3C00;
    }
  }

}
