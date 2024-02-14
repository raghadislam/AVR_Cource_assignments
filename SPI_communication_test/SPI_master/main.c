/*
 * main.c
 *
 *  Created on: Jan 30, 2024
 *      Author: DeLL
 */
#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"
#include "ATmega32_CTOS/SERVICE/BIT_MATH.h"

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/SPI/SPI_int.h"
/* master */
int main()
{
	DIO_enuInit();
	SPI_enuInit();
	u8 x;
	u8 f = 1;
	while(1)
	{
		if(f)
		{
			SPI_enuTranceiveByte('A',&x);
			f=0;
		}
		else{
			SPI_enuTranceiveByte('B',&x);
			f=1;
		}
	}
	return 0;
}
