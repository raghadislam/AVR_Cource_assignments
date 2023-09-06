/*
 * main.c
 *
 *  Created on: Jul 14, 2023
 *      Author: DeLL
 */
/*
 * main.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Raghad islam
 *
 */
#include "STDTypes.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#define DDRA  *(( volatile u8*)0x3A)
#define DDRB  *(( volatile u8*)0x37)
#define DDRC  *(( volatile u8*)0x34)
#define DDRD  *(( volatile u8*)0x31)




#define PORTA *(( volatile u8*)0x3B)
#define PORTB *(( volatile u8*)0x38)
#define PORTC *(( volatile u8*)0x35)
#define PORTD *(( volatile u8*)0x32)



#define PINA  *(( volatile u8*)0x39)
#define PINB  *(( volatile u8*)0x36)
#define PINC  *(( volatile u8*)0x33)
#define PIND  *(( volatile u8*)0x30)




int main(void)
{
	DDRA  = 0x00;
	PORTA = 0xff;
	DDRB  = 0xff;
	DDRC  = 0xff;
	DDRD  = 0xff;
	u8 x = 0;
	u8 SEVEN_SEG [] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	PORTD = 0;
	PORTB = 0;

	while(1)
	{
		    x= ~PINA;
			PORTC= SEVEN_SEG[(x)/100];
			PORTD = SEVEN_SEG[((x)%100)/10];
			PORTB = SEVEN_SEG[(x)%10];

	}
}


