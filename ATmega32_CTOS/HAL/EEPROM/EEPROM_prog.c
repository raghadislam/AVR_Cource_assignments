/********************************
 * EEPROM_prog.c				*
 *  Created on: Feb 14, 2024	*
 *      Author: Raghad Islam	*
 *								*
 ********************************/

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TWI/TWI_int.h"

#include "EEPROM_priv.h"
#include "EEPROM_config.h"

/**
 * @brief function to write one byte of data in the EEPROM.
 *
 * @param[in] Copy_u16Address: address to be written in the EEPROM
 *
 * @param[in] Copy_u8Data: data to be written.
 *
 * @return the error statues.
 */
ES_t EEPROM_enuWriteByte(u16 Copy_u16Address, u8 Copy_u8Data)
{
	/* Local variable related the Error state */
	ES_t Local_enuErrorState = ES_OK;
	u64 Local_u64Check = 0;
	u8 Local_u8Iterator;

	/* Send start condition */
	Local_u64Check |= ((u64)TWI_enuSendStart()<<0);

	/* send the EEPROM address with write request */
	Local_u64Check |= ((u64)TWI_enuSendSlaveAddressWithWrite(EEPROM_ADDRESS) << 5);

	/* set the EEPROM chosen address*/
	Local_u64Check |= ((u64)TWI_enuMasterWriteByte((u8)Copy_u16Address) << 10);

	/* write in the EEPROM chosen address*/
	Local_u64Check |= ((u64)TWI_enuMasterWriteByte(Copy_u8Data) << 15);

	/* Send stop condition */
	Local_u64Check |= ((u64)TWI_enuSendStop() << 20);

	/* check the error state */
	for(Local_u8Iterator = 0; Local_u8Iterator < 25; Local_u8Iterator+=5)
	{
		if(((Local_u64Check >> Local_u8Iterator) & (0b11111)) != ES_OK)
		{
			return ((Local_u64Check >> Local_u8Iterator) & (0b11111));
		}
	}

	return Local_enuErrorState;
}


/**
 * @brief function to Read one byte of data from the EEPROM.
 *
 * @param[in] Copy_u8Data: data to be read.
 *
 * @param[in] Copy_u16Address : address to read from the EEPROM
 *
 * @return the error statues.
 */
ES_t EEPROM_enuReadByte(u8 *Copy_Pu8Data, u16 Copy_u16Address)
{
	/* Local variable related the Error state */
	ES_t Local_enuErrorState = ES_OK;
	u64 Local_u64Check = 0;
	u8 Local_u8Iterator;

	/* Send start condition */
	Local_u64Check |= ((u64)TWI_enuSendStart()<<0);

	/* send the EEPROM address with write request */
	Local_u64Check |= ((u64)TWI_enuSendSlaveAddressWithWrite(EEPROM_ADDRESS) << 5);

	/* set the EEPROM chosen address*/
	Local_u64Check |= ((u64)TWI_enuMasterWriteByte((u8)Copy_u16Address) << 10);

	/* send repeated start condition */
	Local_u64Check |= ((u64)TWI_enuSendRepeatedStart() << 15);

	/* send the EEPROM address with read request */
	Local_u64Check |= ((u64)TWI_enuSendSlaveAddressWithRead(EEPROM_ADDRESS) << 20);

	/* read from the EEPROM chosen address*/
	Local_u64Check |= ((u64)TWI_enuMasterReadByte(Copy_Pu8Data, TWI_NO_ACK) << 25);

	/* Send stop condition */
	Local_u64Check |= ((u64)TWI_enuSendStop() << 30);

	/* check the error state */
	for(Local_u8Iterator = 0; Local_u8Iterator < 35; Local_u8Iterator+=5)
	{
		if(((Local_u64Check >> Local_u8Iterator) & (0b11111)) != ES_OK)
		{
			return ((Local_u64Check >> Local_u8Iterator) & (0b11111));
		}
	}

	return Local_enuErrorState;
}


