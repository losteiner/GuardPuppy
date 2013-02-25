/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

#include "ch.h"
#include "hal.h"

#include "lwipthread.h"
#include "web/web.h"

#include "modules/adc_simple.h"

extern unsigned int valTRIM;
extern unsigned int valMicIn;


static void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n);

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS 2

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH 4

/*
* ADC samples buffer.
*/
static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
* ADC conversion group.
* Mode: Linear buffer, 4 samples of 2 channels, SW triggered.
* Channels:
* Sensor:
*/
static ADCConversionGroup acg = {
		FALSE,					// circular
		ADC_GRP1_NUM_CHANNELS, 	// num_channels (2)
		adccb,					// end_cb
		NULL,					// error_cb
		ADC_CHN_7 | ADC_CHN_8,	// channelselects (TRIM and MIC)
		ADC_TRIGGER_TIMER,						// trigger
		4000			/* Frequency 4khz */
		};


/*
* ADC end conversion callback.
* The PWM channels are reprogrammed using the latest ADC samples.
* The latest samples are transmitted into a single SPI transaction.
*/
void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

  (void) buffer; (void) n;
  /* Note, only in the ADC_COMPLETE state because the ADC driver fires an
intermediate callback when the buffer is half full.*/
  if (adcp->state == ADC_COMPLETE) {
    adcsample_t avg_ch1, avg_ch2;

    /* Calculates the average values from the ADC samples.*/
    avg_ch1 = (samples[0] + samples[2] + samples[4] + samples[6]) / 4;
    avg_ch2 = (samples[1] + samples[3] + samples[5] + samples[7]) / 4;

    chSysLockFromIsr();

    valTRIM = avg_ch1;
    valMicIn = avg_ch2;

    /* Changes the channels pulse width, the change will be effective starting from the next cycle.*/
    //pwmEnableChannelI(&PWMD3, 2, PWM_FRACTION_TO_WIDTH(&PWMD3, 4096, avg_ch1));
    //pwmEnableChannelI(&PWMD3, 3, PWM_FRACTION_TO_WIDTH(&PWMD3, 4096, avg_ch2));

    /* SPI slave selection and transmission start.*/
    //spiSelectI(&SPID1);
    //spiStartSendI(&SPID1, ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH, samples);

    chSysUnlockFromIsr();
  }
}

/** Application entry point. */
int main(void) {

  /* System initializations.  */
  halInit();
  chSysInit();

  /*
   * Initializes the ADC driver 1.
   * The pin PC0 on the port GPIOC is programmed as analog input.
   */
  adcStart(&ADCD1, NULL);
  //palSetGroupMode(GPIOC, PAL_PORT_BIT(0), 0, PAL_MODE_INPUT_ANALOG);


  /* Activates the serial driver 1 using the driver default configuration. */
  sdStart(&SD1, NULL);


  /* Creates the LWIP and HTTP threads (it changes priority internally).  */
  chThdCreateStatic(wa_lwip_thread, LWIP_THREAD_STACK_SIZE, NORMALPRIO + 1,  lwip_thread, NULL);
  chThdCreateStatic(wa_http_server, sizeof(wa_http_server), NORMALPRIO + 1,  http_server, NULL);

  //char valChar[16] = "";

  /* Normal main() thread activity.  */
  while (TRUE) {
    chThdSleepMilliseconds(5);
    adcStartConversionI(&ADCD1, &acg, samples, ADC_GRP1_BUF_DEPTH);

    if (!palReadPad(IOPORT2, PIOB_SW1))
      sdWrite(&SD1, (uint8_t *)"Hello World!\r\n", 14);
    if (!palReadPad(IOPORT2, PIOB_SW2))
    {
    	// TODO: Move this to thread
    	//chprintf((BaseChannel*)&SD1, "TRIM: %d\r\nTemp: %d\r\n", valTRIM , calcTempC(valTempSensor));
    	chprintf((BaseChannel*)&SD1, "TRIM: %d\tMic: %d\r\n", valTRIM, valMicIn );
    }
  }

  return 0;
}
