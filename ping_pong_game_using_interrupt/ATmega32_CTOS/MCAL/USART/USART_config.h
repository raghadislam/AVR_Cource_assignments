/*
 * USART_config.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_USART_USART_CONFIG_H_
#define ATMEGA32_CTOS_MCAL_USART_USART_CONFIG_H_

/* define the system clock frequency */
#define SYSTEM_CLK					8000000ULL

/* define the desired baud rate */
#define USART_BAUD_RATE				9600ULL

/* Define desired Parity
 * options:	1- USART_NO_PARITY
 * 			2- USART_ODD_PARITY
 * 			3- USART_EVEN_PARITY
 */
#define USART_PARITY				USART_NO_PARITY


/* Define desired number of stop bits
 * options:	1- USART_ONE_STOP_BIT
 * 			2- USART_TWO_STOP_BITS
 */
#define USART_STOP_BITS				USART_ONE_STOP_BIT


/* Define desired synchronization mode
 * options:	1- USART_ASYNCH
 * 			2- USART_SYNCH
 */
#define USART_SYNCHRONIZATION		USART_ASYNCH


/**
 * define the desired USART mode of operation
 * options: USART_NORMAL_MODE
 *        USART_DBL_SPEED_MODE
 */
#define USART_MODE 					USART_DBL_SPEED_MODE


/**
 * define the desired USART state of TX and RX
 * options: USART_ENABLE
 *        	USART_DISABLE
 */

#define USART_TX_STATE 				USART_ENABLE
#define USART_RX_STATE 				USART_ENABLE

#define USART_TX_INT_STATE 			USART_ENABLE
#define USART_RX_INT_STATE 			USART_ENABLE
#define USART_EMBTY_DR_INT_STATE 	USART_DISABLE


/**
 * define the desired clock polarity for synchronization mode
 * options: USART_TRANSMIT_AT_RISING   ( transmit at rising and receive at falling )
 *        	USART_TRANSMIT_AT_FALLING  ( transmit at falling and receive at rising )
 */
#define USART_CLK_POLARITY			USART_TRANSMIT_AT_RISING


/**
 * define the data size
 * options: USART_FIVE_BITS
 *       	USART_SIX_BITS
 *      	USART_SEVEN_BITS
 *      	USART_EIGHT_BITS
 *      	USART_NINE_BITS
 */
#define USART_DATA_SIZE 		USART_EIGHT_BITS


/* Define the timeout for USART TX/RX */
#define USART_TIMEOUT 			40000000ULL

#define UBRR_VAL		(((SYSTEM_CLK / (USART_BAUD_RATE * 16ULL))) - 1)
#define UBRR_DBL_VAL	(((SYSTEM_CLK / (USART_BAUD_RATE * 8ULL))) - 1)


#endif /* ATMEGA32_CTOS_MCAL_USART_USART_CONFIG_H_ */
