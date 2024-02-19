/*
 * TWI_prog.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Raghad Islam
 */

#include"../../SERVICE/STDTypes.h"
#include"../../SERVICE/errorState.h"
#include"../../SERVICE/BIT_MATH.h"

#include "TWI_priv.h"
#include "TWI_config.h"


/**
 * @brief function to initialize the TWI in master mode.
 * @param[in] Copy_u8Address: the node's address, in case there's no address send " TWI_NO_ADDRESS ".
 * @return the error statues.
 */
ES_t TWI_enuMasterInit(u8 Copy_u8Address)
{
	ES_t Local_enuErrorState = ES_OK;

	/* set bit rate for */
	TWBR = TWI_BIT_RATE;

	/* set prescaler */
#if TWI_PRESCALER == TWI_PRESCALER_1
	Clr_bit(TWSR,TWSR_TWPS0);
	Clr_bit(TWSR,TWSR_TWPS1);
#elif TWI_PRESCALER == TWI_PRESCALER_4
	Set_bit(TWSR,TWSR_TWPS0);
	Clr_bit(TWSR,TWSR_TWPS1);
#elif TWI_PRESCALER == TWI_PRESCALER_16
	Clr_bit(TWSR,TWSR_TWPS0);
	Set_bit(TWSR,TWSR_TWPS1);
#elif TWI_PRESCALER == TWI_PRESCALER_64
	Set_bit(TWSR,TWSR_TWPS0);
	Set_bit(TWSR,TWSR_TWPS1);
#else
#error "wrong prescaler"
#endif


	/* Checking the state of the Acknowledge Bit */
	if (TWI_ACK_BIT_STATE == TWI_ENABLED)
	{
		Set_bit(TWCR,TWCR_TWEA);
	}

	/* Initialize the node address */
	if(Copy_u8Address != TWI_NO_ADDRESS)
	{
		if((Copy_u8Address & 0b1111000) == 0b1111000 )
		{
			Local_enuErrorState = ES_RESERVED_ADDRESSES;
		}
		else
		{
			/* set the corresponding address */
			TWAR = (Copy_u8Address<<1);
		}
	}

	/* Checking the state of the TWI Interrupt */
#if TWI_INT_STATE == TWI_ENABLED
	Set_bit(TWCR, TWCR_TWIE);
#endif

	/* Checking the state of the General Call recognition */
#if TWI_GENERAL_CALL_STATE == TWI_ENABLED
	Set_bit(TWAR, TWAR_TWGCE);
#endif


	/* Enable TWI */
	Set_bit(TWCR,TWCR_TWEN);

	return Local_enuErrorState;
}


/**
 * @brief function to initialize the TWI in slave mode.
 * @param[in] Copy_u8Address: the node's address.
 * @return the error statues.
 */
ES_t TWI_enuSlaveInit(u8 Copy_u8Address)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Initialize the node address */
	if((Copy_u8Address & 0b1111000) == 0b1111000 )
	{
		Local_enuErrorState = ES_RESERVED_ADDRESSES;
	}
	else
	{
		/* set the corresponding address */
		TWAR = Copy_u8Address<<1;
	}

	/* Checking the state of the TWI Interrupt */
	if (TWI_INT_STATE == TWI_ENABLED)
	{
		Set_bit(TWCR, TWCR_TWIE);
	}

	/* Checking the state of the General Call recognition */
	if (TWI_GENERAL_CALL_STATE == TWI_ENABLED)
	{
		Set_bit(TWAR, TWAR_TWGCE);
	}

	/* Checking the state of the Acknowledge Bit */
	if (TWI_ACK_BIT_STATE == TWI_ENABLED)
	{
		Set_bit(TWCR,TWCR_TWEA);
	}

	/* Enable TWI */
	Set_bit(TWCR,TWCR_TWEN);

	return Local_enuErrorState;
}


/**
 * @brief function to Send a start condition.
 * @return the error statues.
 */
ES_t TWI_enuSendStart()
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32TimeOut = 0;

	/* send start condition and clear the flag */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN); // Start condition

	/* wait for the flag */
	while ((!(TWCR & (1 << TWCR_TWINT))) && Local_u32TimeOut < TWI_TIMEOUT)
	{
		Local_u32TimeOut++;
	}

	/* check if the the loop is breaked beacause of time out*/
	if(Local_u32TimeOut >= TWI_TIMEOUT)
	{
		Local_enuErrorState = ES_TIME_OUT;
	}

	/* check if  operation is completed successfully */
	if(((TWSR & TWSR_STATUS_MASK) != START_ACK) || Local_enuErrorState != ES_OK )
	{
		Local_enuErrorState = ES_START_COND;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to Send a repeated start condition.
 * @return the error statues.
 */
ES_t TWI_enuSendRepeatedStart()
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32TimeOut = 0;

	/* send repeated start condition and clear the flag */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN); // Start condition

	/* wait for the flag */
	while ((!(TWCR & (1 << TWCR_TWINT))) && Local_u32TimeOut < TWI_TIMEOUT)
	{
		Local_u32TimeOut++;
	}

	/* check if the the loop is breaked beacause of time out*/
	if(Local_u32TimeOut >= TWI_TIMEOUT)
	{
		Local_enuErrorState = ES_TIME_OUT;
	}

	/* check if  operation is completed successfully */
	if(((TWSR & TWSR_STATUS_MASK) != REP_START_ACK) || Local_enuErrorState != ES_OK )
	{
		Local_enuErrorState = ES_REP_START_COND;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to send a a slave address with write request.
 * @param[in] Copy_u8Address: the slave's address.
 * @return the error statues.
 */
ES_t TWI_enuSendSlaveAddressWithWrite(u8 Copy_u8Address)
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32TimeOut = 0;

	/* Set write request */
	Clr_bit(Copy_u8Address,0);

	/* Set the slave address in 7 MSBs th data register, 0Bit contains 0 as we need for write */
	TWDR = Copy_u8Address;

	/* clear the flag to start the previous operation */
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	/* wait for the flag */
	while ((!(TWCR & (1<<TWCR_TWINT))) && Local_u32TimeOut < TWI_TIMEOUT)
	{
		Local_u32TimeOut++;
	}

	/* check if the the loop is breaked beacause of time out*/
	if(Local_u32TimeOut >= TWI_TIMEOUT)
	{
		Local_enuErrorState = ES_TIME_OUT;
	}

	/* check if  operation is completed successfully */
	if(((TWSR & TWSR_STATUS_MASK) != SLAVE_ADD_AND_WR_ACK) || Local_enuErrorState != ES_OK )
	{
		Local_enuErrorState = ES_SLAVE_ADD_WITH_WR;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to send a slave address with read request.
 * @param[in] Copy_u8Address: the slave's address.
 * @return the error statues.
 */
ES_t TWI_enuSendSlaveAddressWithRead(u8 Copy_u8Address)
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32TimeOut = 0;

	/* Set read request */
	Set_bit(Copy_u8Address,0);

	/* Set the slave address in 7 MSBs th data register, 0Bit contains 1 as we need for read */
	TWDR = Copy_u8Address;

	/* clear the flag to start the previous operation */
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	/* wait for the flag */
	while ((!(TWCR & (1<<TWCR_TWINT))) && Local_u32TimeOut < TWI_TIMEOUT)
	{
		Local_u32TimeOut++;
	}

	/* check if the the loop is breaked beacause of time out*/
	if(Local_u32TimeOut >= TWI_TIMEOUT)
	{
		Local_enuErrorState = ES_TIME_OUT;
	}

	/* check if  operation is completed successfully */
	if(((TWSR & TWSR_STATUS_MASK) != SLAVE_ADD_AND_RD_ACK) || Local_enuErrorState != ES_OK )
	{
		Local_enuErrorState = ES_SLAVE_ADD_WITH_RD ;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to enable the master to write a byte of data.
 * @param[in] Copy_u8Data: the transmitted data.
 * @return the error statues.
 */
ES_t TWI_enuMasterWriteByte(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32TimeOut = 0;

	/* write the data byte */
	TWDR = Copy_u8Data;

	/* clear the flag to start the previous operation */
	//	Set_bit(TWCR,TWCR_TWINT);
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);

	/* wait for the flag */
	while ((!(TWCR & (1<<TWCR_TWINT))) && Local_u32TimeOut < TWI_TIMEOUT)
	{
		Local_u32TimeOut++;
	}

	/* check if the the loop is breaked beacause of time out*/
	if(Local_u32TimeOut >= TWI_TIMEOUT)
	{
		Local_enuErrorState = ES_TIME_OUT;
	}

	/* check if  operation is completed successfully */
	if(((TWSR & TWSR_STATUS_MASK) != MASTER_WR_BYTE_ACK) || Local_enuErrorState != ES_OK )
	{
		Local_enuErrorState = ES_MASTER_WR_BYTE ;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to enable the master to read a byte of data.
 * @param[in] Copy_u8Data: the received data.
 * @param[in] Copy_u8Ack: the acknowledge bit state.
 * @return the error statues.
 */
ES_t TWI_enuMasterReadByte(u8* Copy_pu8Data, u8 Copy_u8Ack)
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32TimeOut = 0;
	u8 Local_u8StatusCheck;

	if(Copy_pu8Data != NULL){

		/* clear the flag to start the receiving form the salve, set the acknowledge state  */
		TWCR = (1 << TWCR_TWINT) | (Copy_u8Ack << TWCR_TWEA) | (1 << TWCR_TWEN);

		/* wait for the flag */
		while ((!(TWCR & (1<<TWCR_TWINT))) && Local_u32TimeOut < TWI_TIMEOUT)
		{
			Local_u32TimeOut++;
		}

		/* check if the the loop is breaked beacause of time out*/
		if(Local_u32TimeOut >= TWI_TIMEOUT)
		{
			Local_enuErrorState = ES_TIME_OUT;
		}

		/* check the ackmowledge state to know the right operation check state*/
		if(Copy_u8Ack == TWI_NO_ACK)
		{
			Local_u8StatusCheck = MASTER_RD_BYTE_WITH_NACK;
		}
		else
		{
			Local_u8StatusCheck = MASTER_RD_BYTE_WITH_ACK;
		}

		/* check if  operation is completed successfully */
		if(((TWSR & TWSR_STATUS_MASK) != Local_u8StatusCheck) || Local_enuErrorState != ES_OK )
		{
			Local_enuErrorState = ES_MASTER_RD_BYTE ;
		}
		else
		{
			/* write the data byte */
			*Copy_pu8Data = TWDR ;
		}
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}


/**
 * @brief function to Send a stop condition.
 * @return the error statues.
 */
ES_t TWI_enuSendStop(void)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Generate stop cindition on the bus */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTO) | (1 << TWCR_TWEN);

	return Local_enuErrorState;
}


/*========================== ISR ==========================*/

void __vector_19 (void) __attribute__((signal));
void __vector_19 (void)
{

}

