#ifndef TLI4970_H_
#define TLI4970_H_

#define TLI4970_NORMAL_ID       (uint16_t)0
#define TLI4970_D025_OFFSET     4096
#define TLI4970_D025_LSB2MA     12.5f

typedef struct currentSensor{

  SPIDriver* driver;
  ioportid_t port;
  uint16_t pad;
  uint16_t error;
  uint8_t dataReady;
  uint16_t rawData;
  uint16_t rawCurrent;
  int32_t current;      //mA

} currentSensor;

typedef struct spiDriver_t{

  SPIDriver* driver;
  ioportid_t port;
  uint16_t pad;
  uint16_t data;
  uint8_t flag;

} spiDriver_t;

void currentSensorInit(currentSensor* sensor, const SPIConfig* cfg);
void currentSensorUpdate(currentSensor* sensor, const SPIConfig* cfg);

#endif
