/*
 * sensor.h
 *
 *  Created on: Feb 17, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: The sensors module contains the temperature and potentiometer handling.
 */

#ifndef SENSOR_H_
#define SENSOR_H_


#define MIC_BUFFER_DEPTH	100



typedef struct measuredVal {
	unsigned int val;
	unsigned short isNew;
} measVal;

measVal buffMicIn[MIC_BUFFER_DEPTH];
measVal* pBuffMicPosition;

#endif /* SENSOR_H_ */
