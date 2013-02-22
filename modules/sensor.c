/*
 * sensor.c
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#include "adc_simple.h"
#include "sensor.h"
#include "modconf.h"

/* Converts the measured temperature to Celsius */
int calcTempC(unsigned int measADC)
{
	return ((measADC*10)/19);
}

/* Measurement from sensors (10 bit)*/
void aquireADC()
{
	// TODO: Here some buffering would be good.
	/* Aquire values from ADC and increase refresh counters */
	valTempSensor	= GetAdcChanel(ADC_CHN_6);
	//refrTempSensor++;
	valTRIM			= GetAdcChanel(ADC_CHN_7);
	//refrTRIM++;
	valMicIn		= GetAdcChanel(ADC_CHN_8);
	refrMicIn++;
}


