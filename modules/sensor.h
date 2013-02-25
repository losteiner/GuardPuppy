/*
 * sensor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#ifndef SENSOR_H_
#define SENSOR_H_

/* Sampling interval in ms */
unsigned int sampleInterval = 5;

/*
 * NOTE: The refresh counter used only in case of MicIn because thats the time-critical.
 */

/* Temperature sensor measured value and refresh counte*/
volatile unsigned int valTempSensor = 0;
//volatile unsigned short refrTempSensor = 0;

/* TRIM potentiometer measured value and refresh counter*/
volatile unsigned int valTRIM = 0;
//volatile unsigned short refrTRIM = 0;

/* microphone input measured value and refresh counter*/
volatile unsigned int valMicIn = 0;
volatile unsigned short refrMicIn = 0;

typedef struct measuredVal {
	unsigned int val;
	unsigned short isProcessed;
} measVal;

measVal bufMicIn[5];


#endif /* SENSOR_H_ */
