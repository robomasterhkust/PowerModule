/*
 * ADC.h
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#ifndef ADCDRIVER_H_
#define ADCDRIVER_H_

#define ADCNUMCH            4
#define ADCDEPTH            10

#define TEMPSCALE           0.187363735f
#define TEMPOFFSET          357.5881395f

#define ADC2MV              8.862304688f

typedef struct voltages{

  uint16_t tempC;
  uint16_t vinMv;
  uint16_t vcapMv;
  uint16_t voutMV;

} voltages;

void adcDriverInit(void);
void adcDriverUpdate(voltages* data);

#endif /* 0_DRIVER_INC_ADC_H_ */
