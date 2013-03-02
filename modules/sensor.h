/*
 * sensor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#ifndef SENSOR_H_
#define SENSOR_H_

/* ============================================================ [MACROS] ==== */

#define MIC_BUFFER_DEPTH	100


/* ============================================================ [TYPES] ==== */
typedef struct measuredVal {
	unsigned int val;
	unsigned short isNew;
} measVal;

/* ============================================================ [VARIABLES] ==== */



/* ============================================================ [FUNCTIONS] ==== */

void initBuffer();
unsigned short pushSamplesToBuffer(unsigned int*, unsigned short);

#endif /* SENSOR_H_ */
