/*
 * adc_simple.h
 *
 *  Created on: Feb 18, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: A very simple adc aquire module. Should be improved later on.
 */


#include "ch.h"
#include "hal.h"


#ifndef ADC_SIMPLE_H_
#define ADC_SIMPLE_H_

#define ADC_CHN_1   0x01
#define ADC_CHN_2   0x02
#define ADC_CHN_3   0x04
#define ADC_CHN_4   0x08
#define ADC_CHN_5   0x10
#define ADC_CHN_6   0x20 // TEMP on SAM7EX256
#define ADC_CHN_7   0x40 // TRIM on SAM7EX256
#define ADC_CHN_8   0x80 // MIC on SAM7EX256


/* Temperature sensor measured value */
unsigned int valTempSensor = 0;

/* TRIM potentiometer measured value */
unsigned int valTRIM = 0;

/* Microphone input measured value */
unsigned int valMicIn = 0;

static void adc_cb(ADCDriver *adcp, adcsample_t *buffer, size_t n);

/* Total number of channels to be sampled by a single ADC operation.*/
/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_MIC_GRP1_NUM_CHANNELS	1
#define ADC_MIC_GRP1_BUF_DEPTH		8

/* Sampling frequency of ADC conversion */\
#define ADC_MIC_GRP1_FREQUENCY	4000

/* ADC samples buffer. */
static adcsample_t mic_samples[ADC_MIC_GRP1_NUM_CHANNELS * ADC_MIC_GRP1_BUF_DEPTH];

/*
* ADC MIC conversion group.
* Mode: Linear buffer, 8 samples of 1 channels, triggered.
* Channels: 1
* Sensor: Microphone
*/
static ADCConversionGroup acg_mic = {
		FALSE,					// circular
		ADC_MIC_GRP1_NUM_CHANNELS, 	// num_channels (1)
		adc_cb,					// end_cb
		NULL,					// error_cb
		ADC_CHN_8,	// channelselects (TRIM and MIC)
		ADC_TRIGGER_TIMER,		// trigger
		ADC_MIC_GRP1_FREQUENCY			/* Frequency [khz] */
		};


void startADCThread();


#endif /* ADC_SIMPLE*/
