/*
 * main.c
 *
 *  Created on: Jul 22, 2023
 *      Author: DeLL
 */
#include "STDTypes.h"
#include "errorState.h"

#include "DIO_int.h"

#include "LCD_int.h"
#include <util/delay.h>

int main ()
{

	u8 Raghad[] = {

			0x04,0x02,0x01,0x01,0x01,0x02,0x1C, 0x00,
			0x02,0x00,0x0F,0x08,0x08,0x1F,0x00,0x00,
			0x00,0x00,0x01,0x01,0x01,0x0F,0x00,0x00
	};


	DIO_enuInit();

if(LCD_enuInit() == ES_OK)
{

	if(LCD_enuCreatChar(Raghad,3,0) == ES_OK)
	{
		if(LCD_enuSendChar(0) == ES_OK)
		{
			LCD_enuSendChar(1);
			LCD_enuSendChar(2);
		}
	}
	if(LCD_enuGoto(2,0) == ES_OK)
	{
		if(LCD_enuSendCommand(RIGHT_TO_LEFT) == ES_OK)
		{
			if( LCD_enuDisplayString("HELLO! ") == ES_OK )
				_delay_ms(1000);

		}
	}


	LCD_enuClearDisplay();
	_delay_ms(600);

	if(LCD_enuWriteNumber(-5550) == ES_OK)
	{
		_delay_ms(600);
		LCD_enuDisplayString("Noo ");
		LCD_enuClearDisplay();


	}

	if(LCD_enuDisplayString("Raghad islam ") == ES_OK)
	{
		_delay_ms(1000);
		if(LCD_enuClearDisplay() == ES_OK)
			LCD_enuDisplayString("Raghad");
	}
	}

	return 0;
}
