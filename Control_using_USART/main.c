/*
 * main.c
 *
 *  Created on: Jan 30, 2024
 *      Author: DeLL
 */
#include "../ATmega32_CTOS/SERVICE/STDTypes.h"
#include "../ATmega32_CTOS/SERVICE/errorState.h"
#include "../ATmega32_CTOS/SERVICE/BIT_MATH.h"

#include "../ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "../ATmega32_CTOS/MCAL/USART/USART_int.h"
#include "../ATmega32_CTOS/HAL/LCD/LCD_int.h"

int compareStrings(const char *str1, const char *str2);

u8 data[30];
int main()
{
	LCD_enuInit();
	DIO_enuSetPinDir(DIO_u8PORTD,DIO_u8PIN0,DIO_u8INPUT);
	DIO_enuSetPinDir(DIO_u8PORTD,DIO_u8PIN1,DIO_u8OUTPUT);
	USART_enuInit();

	//LCD_enuWriteNumber(14);
	DIO_enuSetPinDir(DIO_u8PORTA,DIO_u8PIN6,DIO_u8OUTPUT);
	DIO_enuSetPinVal(DIO_u8PORTA,DIO_u8PIN6,DIO_u8HIGH);

	while(1){

		USART_enuReceiveStringSynch(data);
		if(compareStrings(data,"ledon"))
		{
			DIO_enuSetPinVal(DIO_u8PORTA,DIO_u8PIN6,DIO_u8HIGH);
			USART_enuSendStringSynch(data);

		}
		else if(compareStrings(data,"ledoff")){
			DIO_enuSetPinVal(DIO_u8PORTA,DIO_u8PIN6,DIO_u8LOW);
			USART_enuSendStringSynch(data);

		}
		else{
			USART_enuSendStringSynch("\nwrong choice\n");
		}

	}
	return 0;
}
int compareStrings(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
            return 0;
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0')
        return 1;
    return 0;
}
