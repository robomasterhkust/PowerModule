/*
 * TLI4970.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"

static const SPIConfig tli4970SpiCfg = {
	NULL,
	NULL,
	0,
	SPI_CR1_MSTR | SPI_CR1_DFF | SPI_CR1_BR_1 | SPI_CR1_BR_0 |
	SPI_CR1_BIDIMODE | SPI_CR1_RXONLY | SPI_CR1_CPHA
};

static const SPIConfig aSpiCfg = {
	NULL,
	GPIOA,
	7,
	SPI_CR1_MSTR | SPI_CR1_DFF | SPI_CR1_BR_1 | SPI_CR1_BR_0 |
	SPI_CR1_BIDIMODE | SPI_CR1_RXONLY | SPI_CR1_CPHA
};

static const SPIConfig bSpiCfg = {
	NULL,
	GPIOB,
	0,
	SPI_CR1_MSTR | SPI_CR1_DFF | SPI_CR1_BR_2 | SPI_CR1_BR_0 |
	SPI_CR1_BIDIMODE | SPI_CR1_RXONLY | SPI_CR1_CPHA
};

void currentSensorInit(currentSensor* sensor, const ioportid_t port, const uint16_t pad) {

  sensor->driver = &SPID1;
//  sensor->driver->rxdmamode |= STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD;
//  sensor->driver->txdmamode |= STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD;

//  if (sensor->driver->state == SPI_STOP) {
//    sensor->driver->rxdmamode |= STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD;
//    //sensor->driver->txdmamode |= STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD;
//    spiStart(sensor->driver, &tli4970SpiCfg);
//  }

  spiStop(sensor->driver);
  spiStart(sensor->driver, &bSpiCfg);

  sensor->port = port;
  sensor->pad = pad;
  palSetPadMode(sensor->port, sensor->pad, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(sensor->port, sensor->pad);

}

uint16_t rxbuf[2];

void currentSensorUpdate(currentSensor* sensor){

  uint16_t data = 0;

  spiAcquireBus(&SPID1);

  //slave select
//  osalDbgCheck(sensor->driver != NULL);
//  osalSysLock();
//  osalDbgAssert(sensor->driver->state == SPI_READY, "not ready");
//  palClearPad(sensor->port, sensor->pad);
//  osalSysUnlock();

  //spiStart(&SPID1, &bSpiCfg);
  spiSelect(&SPID1);

  //chThdSleep();
  spiReceive(&SPID1, 2, &rxbuf);
  spiUnselect(&SPID1);
//  chThdSleep(US2ST(1));

  //slave unselect
//  osalDbgCheck(sensor->driver != NULL);
//  osalSysLock();
//  osalDbgAssert(sensor->driver->state == SPI_READY, "not ready");
//  palSetPad(sensor->port, sensor->pad);
//  osalSysUnlock();

  //spiStop(sensor->driver);
  //release ownership of bus
  spiReleaseBus(&SPID1);

  //if (((data >> 15) & 1) == TLI4970_NORMAL_ID) {
  if (true) {
    uint16_t parity = data & 0x1FFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    //if (((data >> 14) & 1) == parity) {
    if (true) {
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
      sensor->error = data;
    }
  }

}
