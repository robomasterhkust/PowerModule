/*
 * ADC.c
 *
 *  Created on: 12 Jul 2018
 *      Author: Alex's Desktop
 */

#include "ch.h"
#include "hal.h"
#include "adcDriver.h"

static adcsample_t sample [ADCDEPTH] [ADCNUMCH];
static adcsample_t avg    [ADCNUMCH];


/*
 * Regular in, out, cap and temperature voltage sensing
 */
static const ADCConversionGroup adcCfg = {

  TRUE,	                 										//Continuous conversion
  ADCNUMCH,              										//Number of ADC channels
  NULL,                  										//end of conversion callback
	NULL,						      										//ADC error callback
	0,						           									//CR1
  ADC_CR2_TSVREFE,       										//CR2
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_55P5),    //Sample time setting 1
  ADC_SMPR2_SMP_AN0(ADC_SAMPLE_55P5) |
  ADC_SMPR2_SMP_AN1(ADC_SAMPLE_55P5) |
  ADC_SMPR2_SMP_AN4(ADC_SAMPLE_55P5),       //Sample time setting 2
  ADC_SQR1_NUM_CH(ADCNUMCH),                //Sequence setting 1
  0,                                        //Sequence setting 2
  ADC_SQR3_SQ4_N(ADC_CHANNEL_SENSOR)|
  ADC_SQR3_SQ3_N(ADC_CHANNEL_IN4)   |
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1)   |
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)           //Sequence setting 3

};

void adcDriverInit(void) {

  palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);

  adcStart(&ADCD1, NULL);

  adcStartConversion(&ADCD1, &adcCfg, (adcsample_t*) &sample, ADCDEPTH);

}

void * memset (void *block, int c, size_t size);

void adcDriverUpdate(voltages* data) {

  //adcConvert(&ADCD1, &adcCfg, (adcsample*) &sample, ADCDEPTH);

  memset(avg, 0, sizeof(avg));

  for (uint8_t channelno = 0; channelno < ADCNUMCH; channelno++) {

    for (uint8_t sampleno = 0; sampleno < ADCDEPTH; sampleno++) {
      avg[channelno] += sample[sampleno] [channelno];
    }

    avg[channelno] = (uint16_t) avg[channelno] / ADCDEPTH;

  }

  data->tempC = (uint16_t) (TEMPOFFSET - avg[3] * TEMPSCALE);
  data->vinMv = (uint16_t) (avg[2] * ADC2MV);
  data->vcapMv = (uint16_t) (avg[1] * ADC2MV);
  data->voutMV = (uint16_t) (avg[0] * ADC2MV);

}
