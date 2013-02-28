/*
 * adc_simple.c
 *
 *  Created on: Feb 18, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: A very simple adc aquire module. Should be improved later on.
 */

#ifndef SAM7_PLATFORM
#define SAM7_PLATFORM SAM7X256
#endif

#include "adc_simple.h"
//#include "sensor.h"

//extern measVal* pBuffMicPosition;

/*
* ADC end conversion callback.
* The PWM channels are reprogrammed using the latest ADC samples.
* The latest samples are transmitted into a single SPI transaction.
*/
void adc_cb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

  (void) buffer; (void) n;
  /* Note, only in the ADC_COMPLETE state because the ADC driver fires an
intermediate callback when the buffer is half full.*/
  if (adcp->state == ADC_COMPLETE) {
    adcsample_t avg_ch;

    /* Calculates the average values from the ADC samples.*/
    avg_ch = (	mic_samples[0] + mic_samples[2] + mic_samples[4] + mic_samples[6] +
    			mic_samples[1] + mic_samples[3] + mic_samples[5] + mic_samples[7]) / (ADC_MIC_GRP1_BUF_DEPTH);

    chSysLockFromIsr();

    valMicIn = (unsigned int)avg_ch;

    //(*pBuffMicPosition).val = (unsigned int)avg_ch;
    //(*pBuffMicPosition).isNew += 1;
    //pBuffMicPosition++;

    chSysUnlockFromIsr();
  }
}


static WORKING_AREA(waThreadADC, 128);
static msg_t ThreadADC(void *p) {

  (void)p;
  chRegSetThreadName("adcHigh");
  while (TRUE) {

	  adcStartConversionI(&ADCD1, &acg_mic, mic_samples, ADC_MIC_GRP1_BUF_DEPTH);

	  // TODO: Should wait after adcStartConversion?
	  chThdSleepMilliseconds(5);

  }
  return 0;
}

void startADCThread()
{
	/* Starts the ADC conversion thread */
	chThdCreateStatic(waThreadADC, sizeof(waThreadADC), HIGHPRIO, ThreadADC, NULL);
}

