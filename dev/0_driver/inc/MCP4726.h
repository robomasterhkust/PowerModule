#ifndef MCP4726_H_
#define MCP4726_H_

#define SDAPORT     GPIOB
#define SCLPORT     GPIOB

#define SDAPIN      7
#define SCLPIN      6

//Refer to part order code and datasheet for slave address
#define DACADDR     0b1100000

typedef struct dac_t{

  I2CDriver* driver;
  uint16_t mV;
  uint16_t dacVal;

}dac_t;

void dacInit(dac_t* dac);
void dacUpdate(dac_t* dac);

#endif
