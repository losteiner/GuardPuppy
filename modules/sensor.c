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
//measVal* L_pBuffMicPosition;
unsigned int L_pBuffMicPosition;

unsigned short L_bufferState;

/* ============================================================ [FUNCTIONS] ==== */

/* Buffer init, fill with zeros*/
void initBuffer()
{
	int i;
	for(i=0; i<MIC_BUFFER_DEPTH;i++)
	{
		L_buffMicIn[i].val = 0x0000;
		L_buffMicIn[i].isNew = 0;
	}
	//L_pBuffMicPosition = &L_buffMicIn;
	L_pBuffMicPosition = 0;
	L_bufferState = BUFFER_STATE_EMPTY;
}

/* Push sample(s) into buffer */
unsigned short pushSamplesToBuffer(uint16_t* sampleBuff, unsigned short sizeBuff)
{

	// TODO: Copy the content of sampleBuff into working area buffer
	int i;
	for(i=0; i < sizeBuff && BUFFER_STATE_FULL != L_bufferState; i++)
	{
		// FIXME: The sampleBuff gives here 32bit back... dereference needed????
		L_buffMicIn[L_pBuffMicPosition].val = sampleBuff[i];
		L_buffMicIn[L_pBuffMicPosition].isNew++;
		//sampleBuff++;
		L_pBuffMicPosition++;

		/* The buffer reached the limit */
		if(L_pBuffMicPosition >= MIC_BUFFER_DEPTH)
		{
			L_bufferState = BUFFER_STATE_FULL;
		}
		else
		{
			L_bufferState = BUFFER_STATE_READY;
		}
	}

	return L_bufferState;
}

void printBufferToSerial()
{
	chprintf((BaseChannel*)&SD1, "Mic = [" );

	int i;
	for(i=0; i < MIC_BUFFER_DEPTH; i++)
	{
		chprintf((BaseChannel*)&SD1, "%d,",  L_buffMicIn[i].val );
	}

	chprintf((BaseChannel*)&SD1, "]\r\n" );

	chprintf((BaseChannel*)&SD1, "isNew = [" );

	for(i=0; i < MIC_BUFFER_DEPTH; i++)
	{
		chprintf((BaseChannel*)&SD1, "%d,", L_buffMicIn[i].isNew );
	}

	chprintf((BaseChannel*)&SD1, "]\r\n" );

	chprintf((BaseChannel*)&SD1,"L_pBuffMicPosition:%d\r\n",L_pBuffMicPosition);

}
