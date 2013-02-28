/*
 * sensor.c
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

//#include "adc_simple.h"
#include "sensor.h"
#include "modconf.h"


/* Buffer init */
void initBuffer()
{
	int i;
	for(i=0; i<MIC_BUFFER_DEPTH;i++)
	{
		buffMicIn[i].val = 0;
		buffMicIn[i].isNew = 0;
	}
	pBuffMicPosition = &buffMicIn;
}


