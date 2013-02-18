/*
 * adc_simple.h
 *
 *  Created on: Feb 18, 2013
 *      Author: David Losteiner (losteiner)
 *      Description: A very simple adc aquire module. Should be improved later on.
 */

#define ADC_CHN_1   0x01
#define ADC_CHN_2   0x02
#define ADC_CHN_3   0x04
#define ADC_CHN_4   0x08
#define ADC_CHN_5   0x10
#define ADC_CHN_6   0x20 // TEMP on SAM7EX256
#define ADC_CHN_7   0x40 // TRIM on SAM7EX256
#define ADC_CHN_8   0x80 // MIC on SAM7EX256



void InitADC(void);
unsigned int GetAdcChanel(unsigned char chanel);



