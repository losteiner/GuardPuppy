/*
 * sensor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#ifndef SENSOR_H_
#define SENSOR_H_


/* Temperature sensor measured value */
volatile unsigned int valTempSensor = 0;

/* TRIM potentiometer measured value */
volatile unsigned int valTRIM = 0;

/* microphone input measured value */
volatile unsigned int valMicIn = 0;


//int calcTempC(unsigned int measADC);
//void aquireADC();

#endif /* SENSOR_H_ */
