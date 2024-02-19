/*
 * main.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Raghad Islam
 */

#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/EXTI/EXTI_config.h"
#include "ATmega32_CTOS/MCAL/EXTI/EXTI_int.h"
#include "ATmega32_CTOS/MCAL/GIE/GIE_int.h"
#include "ATmega32_CTOS/MCAL/ADC/ADC_int.h"

#include "ATmega32_CTOS/HAL/LCD/LCD_int.h"
#include "ATmega32_CTOS/HAL/LM35/LM35_int.h"

#include <util/delay.h>


void NotficationFunc(u16 Copy_u16Reading)
{
	LCD_enuGoto(1,13);
	LCD_enuWriteNumber(Copy_u16Reading);
	LCD_enuDisplayString("C     ");
}
int main()
{
	DIO_enuInit();
	ADC_enuInit();
	LCD_enuInit();

	LCD_enuDisplayString("temperature: ");
	GIE_viodEnable();

	while(1)
	{
		u16 Local_u16Reading;

		LM35_enuGetTempReadingNonBlocking(&Local_u16Reading,&NotficationFunc);

	}
	return 0;
}



u32 map(u32 x, u32 in_min, u32 in_max, u32 out_min, u32 out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

