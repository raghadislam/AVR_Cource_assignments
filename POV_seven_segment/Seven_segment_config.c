/*
 * Seven_segment_config.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Raghad Islam
 */


#include "errorState.h"
#include "STDTypes.h"

#include "DIO_int.h"

#include "Seven_segment_config.h"
#include "Seven_segment_priv.h"

SEG_t SEVSEG_AstrConfig[NUM_OF_SEG] =
{
		{
				DIO_u8PORTA, DIO_u8PIN1,
				DIO_u8PORTA, DIO_u8PIN2,
				DIO_u8PORTA, DIO_u8PIN3,
				DIO_u8PORTA, DIO_u8PIN4,
				DIO_u8PORTA, DIO_u8PIN5,
				DIO_u8PORTA, DIO_u8PIN6,
				DIO_u8PORTA, DIO_u8PIN7,
				DIO_u8PORTC, DIO_u8PIN6,
				NOT_CONNECTED, NOT_CONNECTED,
				COMMON_CATHODE
		},

		{
				DIO_u8PORTA, DIO_u8PIN1,
				DIO_u8PORTA, DIO_u8PIN2,
				DIO_u8PORTA, DIO_u8PIN3,
				DIO_u8PORTA, DIO_u8PIN4,
				DIO_u8PORTA, DIO_u8PIN5,
				DIO_u8PORTA, DIO_u8PIN6,
				DIO_u8PORTA, DIO_u8PIN7,
				DIO_u8PORTC, DIO_u8PIN7,
				NOT_CONNECTED, NOT_CONNECTED,
				COMMON_CATHODE
		},
};

