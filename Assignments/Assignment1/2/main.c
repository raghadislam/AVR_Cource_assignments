/*
 * main.c
 *
 *  Created on: Jul 13, 2023
 *      Author: DeLL
 */
#include <util/delay.h>
#include "../../STDTypes.h"
#define DDRA  *(( volatile u8*)0x3A)
#define PORTA *(( volatile u8*)0x3B)
#define PINA  *(( volatile u8*)0x39)

int main(void)
{
	DDRA = ~(0);

	while(1)
	{
		for(int i = 0 ; i < 4 ; ++i){
		PORTA |= (1<<(3-i));
		PORTA |= (1<<(i+4));
		_delay_ms(200);
		}


		for(int i = 0 ; i < 4 ; ++i){
		PORTA &= ~(1<<(i));
		PORTA &= ~(1<<(7-i));
		_delay_ms(200);
		}
	}
	return 0;
}

