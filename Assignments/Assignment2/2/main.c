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
	DDRC  = 0xff;
	Set_bit(DDRD,0);
	Set_bit(DDRD,1);
	Set_bit(PORTD,0); // disable seg 1
	Set_bit(PORTD,1); // disable seg 2
	u8 SEVEN_SEG [] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

	while(1)
	{
		Set_bit(PORTD,0); // disable seg 1
		PORTC = SEVEN_SEG[3];
		Clr_bit(PORTD,1); // enable seg 2
		_delay_ms(15);
		Set_bit(PORTD,1);
		PORTC = SEVEN_SEG[5];
		Clr_bit(PORTD,0);
		_delay_ms(15);

	}
}


