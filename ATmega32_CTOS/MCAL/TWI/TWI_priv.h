/*
 * TWI_priv.h
 *
 *  Created on: Feb 14, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_TWI_TWI_PRIV_H_
#define ATMEGA32_CTOS_MCAL_TWI_TWI_PRIV_H_


/* TWI Bit Rate Register */
#define TWBR		*((volatile u8*)0x20)


/* TWI Control Register */
#define TWCR		*((volatile u8*)0x56)

/* TWI Interrupt Flag */
#define	TWCR_TWINT	7

/* TWI Enable Acknowledge Bit */
#define TWCR_TWEA	6

/* TWI START Condition Bit */
#define	TWCR_TWSTA	5

/* TWI STOP Condition Bit */
#define	TWCR_TWSTO	4

/* TWI Write Collision Flag */
#define TWCR_TWWC	3

/* TWI Enable Bit */
#define TWCR_TWEN	2

/* TWI Interrupt Enable */
#define TWCR_TWIE	0

/* TWI Status Register */
#define TWSR		*((volatile u8*)0x21)

/* prescaler bit 0 */
#define TWSR_TWPS0	0

/* prescaler bit 1 */
#define TWSR_TWPS1	1

/* Mask for checking the TWI status */
#define TWSR_STATUS_MASK	0xF8	 //0b11111000


/*	TWI Data Register */
#define TWDR		*((volatile u8*)0x23)


/* TWI (Slave) Address */
#define TWAR		*((volatile u8*)0x22)

/* TWI General Call Recognition Enable Bit */
#define TWAR_TWGCE	0

/*============================= Status Codes =============================*/

#define	START_ACK					0x08	/* A start condition has been transmitted */
#define	REP_START_ACK				0x10	/* A Repeated start condition has been transmitted */
#define SLAVE_ADD_AND_WR_ACK		0x18	/* Master transmit ( Slave address + Write request ) ACK */
#define SLAVE_ADD_AND_RD_ACK		0x40	/* Master transmit ( Slave address + Read request ) ACK */
#define MASTER_WR_BYTE_ACK			0x28	/* Master transmit data ACK */
#define MASTER_RD_BYTE_WITH_ACK		0x50	/* Master received data with ACK */
#define MASTER_RD_BYTE_WITH_NACK	0x58	/* Master received data without ACK */
#define SLAVE_ADD_RCVD_RD_REQ		0xA8	/* Slave address is received with read request */
#define SLAVE_ADD_RCVD_WR_REQ		0x60	/* Slave address is received with write request */
#define SLAVE_DATA_RECEIVED			0x80	/* A byte is received */
#define SLAVE_BYTE_TRANSMITTED		0xB8	/* The written byte is transmitted */

/*============================= Private Macros =============================*/
#define TWI_ENABLED			2
#define TWI_DISABLED		7

#define	TWI_PRESCALER_1		0
#define	TWI_PRESCALER_4		1
#define	TWI_PRESCALER_16	2
#define	TWI_PRESCALER_64	3

#define TWI_NO_ADDRESS		8

#define TWI_NO_ACK			0
#define TWI_ACK				1




#endif /* ATMEGA32_CTOS_MCAL_TWI_TWI_PRIV_H_ */
