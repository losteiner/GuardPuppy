/*
 * utils.h
 *
 *  Created on: Feb 19, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: Some tools just in case. The testing related code come here as well.
 */


#define US2ST(usec) ((systime_t)(((((usec) - 1L) * CH_FREQUENCY) / 1000000L) + 1L))
