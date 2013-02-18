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
#include "test.h"

#include "lwipthread.h"
#include "web/web.h"

//#include "modules/adc_simple.h"
//#include "modules/sensor.h"

extern int valTRIM;

static WORKING_AREA(waSensorThread, 128);
static msg_t SensorThread(void *p) {

	//(void)p;
	//chRegSetThreadName("aquireADCThread");
	systime_t time = chTimeNow();     // T0
	while (TRUE) {
		time += MS2ST(10);            // Next deadline
		aquireADC();
		chThdSleepUntil(time);
	}
	return 0;
}

/* Move this somewhere else! */
char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

/** Application entry point. */
int main(void) {

  /* System initializations.  */
  halInit();
  chSysInit();

  InitADC();

  /* Activates the serial driver 1 using the driver default configuration. */
  sdStart(&SD1, NULL);

  /* Creates the sensor aquire thread. */
  chThdCreateStatic(waSensorThread, sizeof(waSensorThread), NORMALPRIO, SensorThread, NULL);

  /* Creates the LWIP and HTTP threads (it changes priority internally).  */
  chThdCreateStatic(wa_lwip_thread, LWIP_THREAD_STACK_SIZE, NORMALPRIO + 1,  lwip_thread, NULL);
  chThdCreateStatic(wa_http_server, sizeof(wa_http_server), NORMALPRIO + 1,  http_server, NULL);

  char valChar[16] = "";

  /* Normal main() thread activity.  */
  while (TRUE) {
    chThdSleepMilliseconds(500);
    if (!palReadPad(IOPORT2, PIOB_SW1))
      sdWrite(&SD1, (uint8_t *)"Hello World!\r\n", 14);
    if (!palReadPad(IOPORT2, PIOB_SW2))
    {
    	/* Just for checking.*/
    	sdWrite(&SD1, (uint8_t *)itoa(valTRIM,&valChar,10), 14);
    }
  }

  return 0;
}
