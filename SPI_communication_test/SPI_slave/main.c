/*
 * main.c
 *
 *  Created on: Jan 30, 2024
 *      Author: DeLL
 */
#include <util/delay.h>
#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"
#include "ATmega32_CTOS/SERVICE/BIT_MATH.h"

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/SPI/SPI_int.h"

/* slave */
int main()
{
	DIO_enuInit();
	SPI_enuInit();
	u8 x;
	while(1){
		SPI_enuTranceiveByte('c',&x);
		if(x == 'A')
		{
			DIO_enuSetPinVal(DIO_u8PORTA,DIO_u8PIN6,DIO_u8HIGH);
			_delay_ms(100);
		}
		else
		{
			DIO_enuSetPinVal(DIO_u8PORTA,DIO_u8PIN6,DIO_u8LOW);
			_delay_ms(100);

		}
	}

	return 0;
}
