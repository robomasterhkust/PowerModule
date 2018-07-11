/*
 * TLI4970.c
 *
 *  Created on: 5 Jul 2018
 *      Author: Alex's Desktop
 *
 *  SPI RX only mode does not fking work,
 *  took me 2 days to figure that out
 *
 */

#include "ch.h"
#include "hal.h"
#include "TLI4970.h"

void currentSensorInit(currentSensor* sensor, const SPIConfig* cfg) {

  sensor->driver = &SPID1;

  palSetPadMode(cfg->ssport, cfg->sspad, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(cfg->ssport, cfg->sspad);

  spiStart(sensor->driver, cfg);

}

uint16_t rxbuf[1];

void currentSensorUpdate(currentSensor* sensor, const SPIConfig* cfg) {

  spiAcquireBus(sensor->driver);
  spiStart(sensor->driver, cfg);
  spiSelect(sensor->driver);
  spiReceive(sensor->driver, 1, &sensor->rawData);
  spiUnselect(sensor->driver);
  spiReleaseBus(sensor->driver);

  if (((sensor->rawData >> 15) & 1) == TLI4970_NORMAL_ID) {
    uint16_t parity = sensor->rawData & 0x1FFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    if (((sensor->rawData >> 14) & 1) == parity) {
      sensor->error = 0;
      sensor->rawCurrent = sensor->rawData & 0x1FFF;
      sensor->current = (sensor->rawCurrent - TLI4970_D025_OFFSET) * TLI4970_D025_LSB2MA;
    }
  } else {
    uint16_t parity = sensor->rawData & 0xFFFF;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;         //get parity bit, equals to 1 if data is even
    if (((sensor->rawData >> 14) & 1) == parity) {
      sensor->error = sensor->rawData;
    }
  }

}
