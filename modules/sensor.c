/*
 * sensor.c
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#include "adc_simple.h"
#include "sensor.h"

/* Converts the measured temperature to Celsius */
int calcTempC(unsigned int measADC)
{
	return ((measADC*10)/19);
}

/* Measurement from sensors (10 bit)*/
void aquireADC()
{
	valTempSensor	= GetAdcChanel(ADC_CHN_6);
	valTRIM			= GetAdcChanel(ADC_CHN_7);
	valMicIn		= GetAdcChanel(ADC_CHN_8);
}
