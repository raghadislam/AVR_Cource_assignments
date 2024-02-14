/*
 * DC_prog.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "DC_priv.h"
#include "DC_config.h"


/*
 * @brief function to initialize the DC motor
 *
 * @return error statues
 */
ES_t DC_enuInit()
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8Iterator;

	/* variable to check the error statues in the loop*/
	u32 Lcoal_u32ErrorCheck = 0;

	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_MOTORS ; Local_u8Iterator++)
	{
		/* set motor pins to be output pins */
		Lcoal_u32ErrorCheck |= ((u32)(DIO_enuSetPinDir(DC_AstrConfig[Local_u8Iterator].DC_u8Port1,DC_AstrConfig[Local_u8Iterator].DC_u8Pin1, DIO_u8OUTPUT)) << 0);
		Lcoal_u32ErrorCheck |= ((u32)(DIO_enuSetPinDir(DC_AstrConfig[Local_u8Iterator].DC_u8Port2,DC_AstrConfig[Local_u8Iterator].DC_u8Pin2, DIO_u8OUTPUT)) << 3);
	}

	for(Local_u8Iterator = 0 ; Local_u8Iterator < 6 ; Local_u8Iterator += 3)
	{
		if( ( ( Lcoal_u32ErrorCheck>>Local_u8Iterator ) & DC_MASK ) != ES_OK )
		{
			return ES_NOK;
		}
	}

	return Local_enuErrorState;
}


/*
 * @brief function to rotate the DC motor in the clock wise direction
 * @return error statues
 */
ES_t DC_enuRotateCW()
{
	ES_t Local_enuErrorState = ES_NOK;

	/* loop iterator */
	u8 Local_u8Iterator;

	/* variable to check the error statues in the loop*/
	u32 Lcoal_u32ErrorCheck = 0;

	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_MOTORS ; Local_u8Iterator++)
	{
		/* set motor pin values to rotate clock wise */
		Lcoal_u32ErrorCheck |= ((u32)(DIO_enuSetPinVal(DC_AstrConfig[Local_u8Iterator].DC_u8Port1,DC_AstrConfig[Local_u8Iterator].DC_u8Pin1, DIO_u8LOW)) << 0);
		Lcoal_u32ErrorCheck |= ((u32)(DIO_enuSetPinVal(DC_AstrConfig[Local_u8Iterator].DC_u8Port2,DC_AstrConfig[Local_u8Iterator].DC_u8Pin2, DIO_u8HIGH)) << 3);
	}

	for(Local_u8Iterator = 0 ; Local_u8Iterator < 6 ; Local_u8Iterator += 3)
	{
		if( ( ( Lcoal_u32ErrorCheck>>Local_u8Iterator ) & DC_MASK ) != ES_OK )
		{
			return ES_NOK;
		}
	}

	return Local_enuErrorState;
}


/*
 * @brief function to rotate the DC motor in the counter clock wise direction
 * @return error statues
 * */
ES_t DC_enuRotateCCW()
{
	ES_t Local_enuErrorState = ES_NOK;

	/* loop iterator */
	u8 Local_u8Iterator;

	/* variable to check the error statues in the loop*/
	u32 Lcoal_u32ErrorCheck = 0;

	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_MOTORS ; Local_u8Iterator++)
	{
		/* set motor pin values to rotate counter clock wise */
		Lcoal_u32ErrorCheck |= ((u32)(DIO_enuSetPinVal(DC_AstrConfig[Local_u8Iterator].DC_u8Port2,DC_AstrConfig[Local_u8Iterator].DC_u8Pin2, DIO_u8LOW)) << 0);
		Lcoal_u32ErrorCheck |= ((u32)(DIO_enuSetPinVal(DC_AstrConfig[Local_u8Iterator].DC_u8Port1,DC_AstrConfig[Local_u8Iterator].DC_u8Pin1, DIO_u8HIGH)) << 3);
	}

	for(Local_u8Iterator = 0 ; Local_u8Iterator < 6 ; Local_u8Iterator += 3)
	{
		if( ( ( Lcoal_u32ErrorCheck>>Local_u8Iterator ) & DC_MASK ) != ES_OK )
		{
			return ES_NOK;
		}
	}

	return Local_enuErrorState;
}
