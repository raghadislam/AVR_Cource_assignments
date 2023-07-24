/*
 * Keypad_prog.c
 *
 *  Created on: Jul 24, 2023
 *      Author: Raghad
 */
#include "STDTypes.h"
#include "errorState.h"
#include <util/delay.h>

#include "DIO_int.h"

#include "Keypad_config.h"
#include "Keypad_priv.h"

//ES_t Ketpad_enuInit()
//{
//	ES_t Local_enuErrorState = ES_NOK;
//	u8 Local_u8Iterator;
//
//
//	// set all column to output high
//
//	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_COL ; Local_u8Iterator++)
//	{
//		Local_enuErrorState = DIO_enuSetPinDir(CONC1(Local_u8Iterator) , CONC2(Local_u8Iterator) , DIO_u8OUTPUT);
//		if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//	}
//
//	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_COL ; Local_u8Iterator++)
//	{
//		Local_enuErrorState = DIO_enuSetPinVal(CONC1(Local_u8Iterator) , CONC2(Local_u8Iterator) , DIO_u8HIGH);
//		if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//	}
//
//	// set all rows to input pull up
//
//	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_ROW ; Local_u8Iterator++)
//	{
//		Local_enuErrorState = DIO_enuSetPinDir(CONC3(Local_u8Iterator) , CONC4(Local_u8Iterator) , DIO_u8INPUT);
//		if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//	}
//
//	for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_COL ; Local_u8Iterator++)
//	{
//		Local_enuErrorState = DIO_enuSetPinVal(CONC3(Local_u8Iterator) , CONC4(Local_u8Iterator) , DIO_u8HIGH);
//		if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//	}
//
//
//
//	return Local_enuErrorState;
//}

u8 Keypad_u8Buttons[NUM_OF_ROW][NUM_OF_COL] = KPD_BUTTONS ;

ES_t Ketpad_enuGetPressedKey(u8* Copy_pu8Key)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8Row, Local_u8col, Local_u8pinval;

	Copy_pu8Key =  DEFAULT_KEY;

	u8 Local_Au8ColPort[NUM_OF_COL] = KPD_COL_PORTS;
	u8 Local_Au8ColPins[NUM_OF_COL] = KPD_COL_PINS;

	u8 Local_Au8ROWPort[NUM_OF_ROW] = KPD_ROW_PORTS;
	u8 Local_Au8ROWPins[NUM_OF_ROW] = KPD_ROW_PINS;



	for(Local_u8col = 0; Local_u8col < NUM_OF_COL; ++Local_u8col)
	{

		Local_enuErrorState = DIO_enuSetPinVal(Local_Au8ColPort[Local_u8col], Local_Au8ColPins[Local_u8col], DIO_u8LOW );

		for(Local_u8Row = 0; Local_u8Row < NUM_OF_ROW; ++Local_u8Row)
		{
			Local_enuErrorState = DIO_enuGetPinVal(Local_Au8ROWPort[Local_u8Row], Local_Au8ROWPins[Local_u8Row] ,&Local_u8pinval);

			if(!Local_u8pinval)
			{
				_delay_ms(10);
				if(!Local_u8pinval)
				{

					*Copy_pu8Key = Keypad_u8Buttons[Local_u8Row][Local_u8col];

					while(!Local_u8pinval)
					{
						Local_enuErrorState = DIO_enuGetPinVal(Local_Au8ROWPort[Local_u8Row], Local_Au8ROWPins[Local_u8Row] ,&Local_u8pinval);

					}

				}
			}

			if(Copy_pu8Key != DEFAULT_KEY)  return Local_enuErrorState;
		}

		Local_enuErrorState = DIO_enuSetPinVal(Local_Au8ColPort[Local_u8col], Local_Au8ColPins[Local_u8col], DIO_u8HIGH );

	}


	return Local_enuErrorState;
}
