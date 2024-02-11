/*
 * USART_priv.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_USART_USART_PRIV_H_
#define ATMEGA32_CTOS_MCAL_USART_USART_PRIV_H_

/* parity options */
#define USART_NO_PARITY			1
#define USART_ODD_PARITY		2
#define USART_EVEN_PARITY		3


/* Number of stop bits options */
#define USART_ONE_STOP_BIT  	4
#define USART_TWO_STOP_BITS 	5

/* Sunchronization options */
#define USART_ASYNCH			12
#define USART_SYNCH				11

/* Speed mode options */
#define USART_NORMAL_MODE    	19
#define USART_DBL_SPEED_MODE 	20

/* State options */
#define USART_ENABLE			33
#define USART_DISABLE			44


/* Data size options */
#define USART_FIVE_BITS			23
#define USART_SIX_BITS			45
#define USART_SEVEN_BITS		87
#define USART_EIGHT_BITS		24
#define USART_NINE_BITS			17

/* Clock Polarity options */
#define USART_TRANSMIT_AT_RISING	29
#define USART_TRANSMIT_AT_FALLING	14


/*========================== USART I/O Data Register ==========================*/

#define UDR *((volatile u8 *)(0x2C))

/*==================== USART Control and Status Register A ====================*/

#define UCSRA *((volatile u8 *)(0x2B))

/* USART Receive Complete Bit */
#define UCSRA_RXC	7

/* USART Transmit Complete Bit */
#define UCSRA_TXC	6

/* USART Data Register Empty Bit */
#define UCSRA_UDRE	5

/* Frame Error Bit */
#define UCSRA_FE	4

/* Data OverRun Bit */
#define UCSRA_DOR	3

/* Parity Error Bit */
#define UCSRA_PE	2

/* Double the USART Transmission Speed Bit */
#define UCSRA_U2X	1

/* Multi-processor Communication Mode Bit */
#define UCSRA_MPCM	0

/*==================== USART Control and Status Register B ====================*/

#define UCSRB *((volatile u8 *)(0x2A))

/* RX Complete Interrupt Enable Bit */
#define UCSRB_RXCIE	7

/* TX Complete Interrupt Enable Bit */
#define UCSRB_TXCIE 6

/* USART Data Register Empty Interrupt Enable Bit */
#define UCSRB_UDRIE	5

/* Receiver Enable Bit */
#define UCSRB_RXEN	4

/* Transmitter Enable Bit */
#define UCSRB_TXEN	3

/* Character Size Bit */
#define UCSRB_UCSZ2	2

/* Receive Data Bit 8 */
#define UCSRB_RXB8	1

/* Transmit Data Bit 8 */
#define UCSRB_TXB8	0

/*====================== USART Control and Status Register C ======================*/

#define UCSRC *((volatile u8 *)(0x40))

/* Register Select Bit */
#define UCSRC_URSEL	7

/* USART Mode Select Bit */
#define UCSRC_UMSEL	6

/* Parity Mode Bit */
#define UCSRC_UPM1	5
#define UCSRC_UPM0	4

/* Stop Bit Select Bit */
#define UCSRC_USBS	3

/* Character Size Bit */
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1

/* Clock Polarity Bit */
#define UCSRC_UCPOL	0

/*============================ USART Baud Rate Registers ============================*/
#define UBRRL *((volatile u8 *)(0x29))
#define UBRRH *((volatile u8 *)(0x40))



#endif /* ATMEGA32_CTOS_MCAL_USART_USART_PRIV_H_ */
