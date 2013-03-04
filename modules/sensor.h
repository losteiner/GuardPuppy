/*
 * sensor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "ch.h"
#include "hal.h"

/* ============================================================ [MACROS] ==== */

#define MIC_BUFFER_DEPTH	100


/* ============================================================ [TYPES] ==== */
typedef struct measuredVal {
	uint16_t val;
	unsigned short isNew;
} measVal;

/* ============================================================ [VARIABLES] ==== */



/* ============================================================ [FUNCTIONS] ==== */

void initBuffer();
unsigned short pushSamplesToBuffer(uint16_t*, unsigned short);

#endif /* SENSOR_H_ */
