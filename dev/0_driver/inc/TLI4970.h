#ifndef TLI4970_H_
#define TLI4970_H_

#define TLI4970_NORMAL_ID       (uint16_t)0
#define TLI4970_D025_OFFSET     4096
#define TLI4970_D025_LSB2MA     6.25f

typedef struct currentSensor{

  SPIDriver* driver;
  ioportid_t port;
  uint16_t pad;
  uint16_t error;
  uint16_t raw_current;
  int32_t current;      //mA

} currentSensor;

void currentSensorInit(currentSensor* sensor, ioportid_t port, uint16_t pad);
void currentSensorUpdate(currentSensor* sensor);

#endif
