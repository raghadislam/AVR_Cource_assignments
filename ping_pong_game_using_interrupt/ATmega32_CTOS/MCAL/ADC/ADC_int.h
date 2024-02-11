/*
 * ADC_int.h
 *
 *  Created on: Sep 21, 2023
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_ADC_ADC_INT_H_
#define ATMEGA32_CTOS_MCAL_ADC_ADC_INT_H_

ES_t ADC_enuInit();
ES_t ADC_enuBlockingRead(u8 Copy_u8Channel, u8* Copy_u8Reading);
ES_t ADC_enuReadNonBlocking(u8 Copy_u8Channel, u16* Copy_pu16Reading, void (*Copy_pvNotficationFunc)(void));

/*Analog Channel and Gain Selection*/


//Single ended input channels

#define ADC_SINGLE_ENDED_ADC0		0x0
#define ADC_SINGLE_ENDED_ADC1		0x1
#define ADC_SINGLE_ENDED_ADC2		0x2
#define ADC_SINGLE_ENDED_ADC3       0x3
#define ADC_SINGLE_ENDED_ADC4       0x4
#define ADC_SINGLE_ENDED_ADC5       0x5
#define ADC_SINGLE_ENDED_ADC6       0x6
#define ADC_SINGLE_ENDED_ADC7       0x7
#define V_BG					    0x1E
#define GND					     	0x1F


//differential channels *Positive_negative_gain*

#define ADC0_ADC0_X10		0x8
#define ADC1_ADC0_X10		0x9
#define ADC0_ADC0_X200		0xA
#define ADC1_ADC0_X200  	0xB
#define ADC2_ADC2_X10  		0xC
#define ADC3_ADC2_X10 	    0xD
#define ADC2_ADC2_X200      0xE
#define ADC3_ADC2_X200      0xF
#define ADC0_ADC1	        0x10
#define ADC1_ADC1	        0x11
#define ADC2_ADC1	        0x12
#define ADC3_ADC1	        0x13
#define ADC4_ADC1	        0x14
#define ADC5_ADC1	        0x15
#define ADC6_ADC1	        0x16
#define ADC7_ADC1	        0x17
#define ADC0_ADC2	        0x18
#define ADC1_ADC2	        0x19
#define ADC2_ADC2	        0x1A
#define ADC3_ADC2	        0x1B
#define ADC4_ADC2	        0x1C
#define ADC5_ADC2	        0x1D


#endif /* ATMEGA32_CTOS_MCAL_ADC_ADC_INT_H_ */
