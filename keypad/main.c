/*
 * main.c
 *
 *  Created on: Jul 24, 2023
 *      Author: Raghad
 */

#include "STDTypes.h"
#include "errorState.h"
#include <util/delay.h>

#include "DIO_int.h"

#include "Keypad_int.h"
#include "LCD_int.h"


int main()
{
	//DIO_enuInit();
	LCD_enuInit();
	Keypad_enuInit();
	u8 Local_u8PressedKey = NOT_PRESSED;
while(1)
{
	Local_u8PressedKey = NOT_PRESSED;
	while(Local_u8PressedKey == NOT_PRESSED){
	Keypad_enuGetPressedKey(&Local_u8PressedKey);
	}
	LCD_enuSendChar(Local_u8PressedKey);
}
return 0;

}

