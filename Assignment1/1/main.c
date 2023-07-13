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
		// ----------------Snake effect--------------

		for(int i = 0 ; i < 8 ; ++i){
			PORTA |= (1<<i);
		    _delay_ms(100);
		}

		for(int i = 0 ; i < 8 ; ++i){
			PORTA &= ~(1<<i);
			_delay_ms(100);
		}
	}
	return 0;
}

