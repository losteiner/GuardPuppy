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

//#include "modules/adc_simple.h"

//extern unsigned int valTRIM;
extern unsigned int valMicIn;
extern short L_bufferState;


/****************************
 * Application entry point. *
 ****************************/
int main(void) {

  /* System initializations.  */
  halInit();
  chSysInit();

  /* Initializes the ADC driver 1. */
  adcStart(&ADCD1, NULL);

  /* Activates the serial driver 1 using the driver default configuration. */
  sdStart(&SD1, NULL);

  /* Creates the LWIP and HTTP threads (it changes priority internally).  */
  chThdCreateStatic(wa_lwip_thread, LWIP_THREAD_STACK_SIZE, NORMALPRIO + 1,  lwip_thread, NULL);
  chThdCreateStatic(wa_http_server, sizeof(wa_http_server), NORMALPRIO + 1,  http_server, NULL);

  /* Here starts the ADC conversion thread */
  startADCThread();

  int isPrinted = 0;

  /* Normal main() thread activity.  */
  while (TRUE) {
    chThdSleepMilliseconds(100);

    if(L_bufferState == 0xFF && !isPrinted)
    {
    	printBufferToSerial();
    	isPrinted++;

    }

    if (!palReadPad(IOPORT2, PIOB_SW1))
      sdWrite(&SD1, (uint8_t *)"Hello World!\r\n", 14);
    if (!palReadPad(IOPORT2, PIOB_SW2))
    {
    	// TODO: Move this to a thread
    	chprintf((BaseChannel*)&SD1, "Mic: \t%d\r\n",  valMicIn );
    }
  }

  return 0;
}
