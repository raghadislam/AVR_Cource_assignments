/*
 * TWI_config.h
 *
 *  Created on: Feb 14, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_TWI_TWI_CONFIG_H_
#define ATMEGA32_CTOS_MCAL_TWI_TWI_CONFIG_H_


/*choose the TWI state
 * option:	1- TWI_ENABLED
 * 			2- TWI_DISABLED
 */
#define TWI_STATE				TWI_ENABLED


/*choose the TWI prescaler
 * option:	1- TWI_PRESCALER_1
 * 			2- TWI_PRESCALER_4
 * 			3- TWI_PRESCALER_16
 * 			4- TWI_PRESCALER_64
 */
#define TWI_PRESCALER			TWI_PRESCALER_1


/*choose the Acknowledge bit state
 * option:	1- TWI_ENABLED
 * 			2- TWI_DISABLED
 */
#define TWI_ACK_BIT_STATE		TWI_ENABLED

#define TWI_INT_STATE			TWI_DISABLED

#define TWI_GENERAL_CALL_STATE	TWI_ENABLED

//#define TWI_SLAVE_ADDRESS		0b0101010

#define TWI_BIT_RATE			12 /* this is for 16MH cpu freq and 400Kbps */

/* Macro to define the timeout which determines the fault time in the TWI */
#define	TWI_TIMEOUT				800000000ULL

#endif /* ATMEGA32_CTOS_MCAL_TWI_TWI_CONFIG_H_ */
