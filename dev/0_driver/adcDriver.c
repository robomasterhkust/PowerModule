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
  ADC_SMPR2_SMP_AN3(ADC_SAMPLE_239P5) |
  ADC_SMPR2_SMP_AN4(ADC_SAMPLE_55P5),       //Sample time setting 2
  ADC_SQR1_NUM_CH(ADCNUMCH),                //Sequence setting 1
  0,                                        //Sequence setting 2
  ADC_SQR3_SQ5_N(ADC_CHANNEL_IN3)   |
  ADC_SQR3_SQ4_N(ADC_CHANNEL_SENSOR)|
  ADC_SQR3_SQ3_N(ADC_CHANNEL_IN4)   |
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1)   |
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)           //Sequence setting 3

};

void adcDriverInit(void) {

  palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA, 3, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);

  adcStart(&ADCD1, NULL);

  adcStartConversion(&ADCD1, &adcCfg, (adcsample_t*) &sample, ADCDEPTH);

}

void * memset (void *block, int c, size_t size);

void adcDriverUpdate(voltages* data) {

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
  data->voutMv = (uint16_t) (avg[0] * ADC2MV);
  data->ioutMa = (int32_t) (avg[4] * ADC2MA);

}
