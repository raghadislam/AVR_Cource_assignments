/*
 * main.c
 *
 *  Created on: Jul 13, 2023
 *      Author: DeLL
 */
#include <util/delay.h>
#include "../../STDTypes.h"
#include <math.h>
#define DDRA  *(( volatile u8*)0x3A)
#define PORTA *(( volatile u8*)0x3B)
#define PINA  *(( volatile u8*)0x39)

int main(void)
{
	DDRA = ~(0);

	s64 u =0 ,m=0,n=6,b=6,v=3,c=2,e=4,w=4,q,a,s,d,z,l;

	u8 x,y=9;
	x = tan(y);


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

