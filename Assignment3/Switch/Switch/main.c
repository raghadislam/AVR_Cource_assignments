/*
 * main.c
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#include "STDTypes.h"
#include "errorState.h"

#include "DIO_int.h"

#include "Switch_config.h"
#include "Switch_int.h"


extern SW_t Switch_ArrStrSwitchState[NUM_OF_SW] ;

int main()
{

	DIO_enuInit();

	Switch_enuInit(Switch_ArrStrSwitchState);
	u8 SwState;
	while(1)
	{
		Switch_enuGetState(Switch_ArrStrSwitchState , &SwState );

		if(SwState == 1){
			DIO_enuSetPinVal(DIO_u8PORTA , DIO_u8PIN0 , DIO_u8HIGH );
		}
		else
		{
			DIO_enuSetPinVal(DIO_u8PORTA , DIO_u8PIN0 , DIO_u8LOW );

		}
	}

	return 0;
}

