/*
 * TWI_int.h
 *
 *  Created on: Feb 14, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_TWI_TWI_INT_H_
#define ATMEGA32_CTOS_MCAL_TWI_TWI_INT_H_

/* Macro to be sent in case of no address for master */
#define TWI_NO_ADDRESS	54
#define TWI_NO_ACK		0
#define TWI_ACK			1


/**
 * @brief function to initialize the TWI in master mode.
 *
 * @param[in] Copy_u8Address: the node's address, in case there's no address send " TWI_NO_ADDRESS ".
 *
 * @return the error statues.
 */
ES_t TWI_enuMasterInit(u8 Copy_u8Address);


/**
 * @brief function to initialize the TWI in slave mode.
 *
 * @param[in] Copy_u8Address: the node's address.
 *
 * @return the error statues.
 */
ES_t TWI_enuSlaveInit(u8 Copy_u8Address);


/**
 * @brief function to Send a start condition.
 *
 * @return the error statues.
 */
ES_t TWI_enuSendStart(void);


/**
 * @brief function to Send a repeated start condition.
 *
 * @return the error statues.
 */
ES_t TWI_enuSendRepeatedStart(void);


/**
 * @brief function to send a a slave address with write request.
 *
 * @param[in] Copy_u8Address: the slave's address.
 *
 * @return the error statues.
 */
ES_t TWI_enuSendSlaveAddressWithWrite(u8 Copy_u8Address);


/**
 * @brief function to send a a slave address with read request.
 *
 * @param[in] Copy_u8Address: the slave's address.
 *
 * @return the error statues.
 */
ES_t TWI_enuSendSlaveAddressWithRead(u8 Copy_u8Address);


/**
 * @brief function to enable the master to write a byte of data.
 *
 * @param[in] Copy_u8Data: the transmitted data.
 *
 * @return the error statues.
 */
ES_t TWI_enuMasterWriteByte(u8 Copy_u8Data);


/**
 * @brief function to enable the master to read a byte of data.
 *
 * @param[in] Copy_u8Data: the received data.
 *
 * @return the error statues.
 */
ES_t TWI_enuMasterReadByte(u8* Copy_pu8Data, u8 Copy_u8Ack);


/**
 * @brief function to Send a stop condition.
 *
 * @return the error statues.
 */
ES_t TWI_enuSendStop(void);






#endif /* ATMEGA32_CTOS_MCAL_TWI_TWI_INT_H_ */
