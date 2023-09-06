/*
 * Seven_segment_config.h
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#ifndef SEVEN_SEGMENT_CONFIG_H_
#define SEVEN_SEGMENT_CONFIG_H_

#define SEG_APORT		 DIO_u8PORTA
#define SEG_APIN		 DIO_u8PIN6

#define SEG_BPORT		 DIO_u8PORTA
#define SEG_BPIN	     DIO_u8PIN4

#define SEG_CPORT	 	 DIO_u8PORTC
#define SEG_CPIN	 	 DIO_u8PIN4

#define SEG_DPORT		 DIO_u8PORTD
#define SEG_DPIN	  	 DIO_u8PIN4

#define SEG_EPORT	 	 DIO_u8PORTB
#define SEG_EPIN		 DIO_u8PIN4

#define SEG_FPORT	 	 DIO_u8PORTA
#define SEG_FPIN		 DIO_u8PIN0

#define SEG_GPORT	 	 DIO_u8PORTB
#define SEG_GPIN		 DIO_u8PIN0

#define SEG_DOT_PORT	 NOT_CONNECTED
#define SEG_DOT_PIN	     NOT_CONNECTED

#define SEG_CMN_PORT	 NOT_CONNECTED
#define SEG_CMN_PIN	     NOT_CONNECTED

#define SEG_TYPE	 	 COMMON_ANODE

#endif /* SEVEN_SEGMENT_CONFIG_H_ */
