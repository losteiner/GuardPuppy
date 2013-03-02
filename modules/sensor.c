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

/* ============================================================ [MACROS] ==== */
#define BUFFER_STATE_EMPTY		0x00
#define BUFFER_STATE_READY		0x01
#define BUFFER_STATE_FULL		0xFF

/* ============================================================ [LOCAL VARIABLES] ==== */
measVal  L_buffMicIn[MIC_BUFFER_DEPTH];
measVal* L_pBuffMicPosition;

unsigned short L_bufferState;

/* ============================================================ [FUNCTIONS] ==== */

/* Buffer init, fill with zeros*/
void initBuffer()
{
	int i;
	for(i=0; i<MIC_BUFFER_DEPTH;i++)
	{
		L_buffMicIn[i].val = 0;
		L_buffMicIn[i].isNew = 0;
	}
	L_pBuffMicPosition = &L_buffMicIn;
	L_bufferState = BUFFER_STATE_EMPTY;
}

/* Push sample(s) into buffer */
unsigned short pushSamplesToBuffer(unsigned int* sampleBuff, unsigned short sizeBuff)
{
	// TODO: Copy the content of sampleBuff into working area buffer
	int i;
	for(i=0; i < sizeBuff && !BUFFER_STATE_FULL; i++)
	{

		L_pBuffMicPosition[i].val = (unsigned int)*sampleBuff;
		sampleBuff++;
		L_pBuffMicPosition++;
	}
}
