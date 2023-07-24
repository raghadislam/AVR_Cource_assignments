/*
 * main.c
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#include "STDTypes.h"
#include "errorState.h"

#include "DIO_int.h"


#include "LED_config.h"
#include "LED_int.h"

#include "Switch_config.h"
#include "Switch_int.h"



#include <util/delay.h>

extern LED_t LED_AstrLedConfig[NUM_OF_LED];
extern SW_t Switch_ArrStrSwitchState[3];

int main()
{
	DIO_enuInit();
	LED_enuInit(LED_AstrLedConfig);
	Switch_enuInit(Switch_ArrStrSwitchState);
	u8 SWstate;

	while(1){

		Switch_enuGetState(Switch_ArrStrSwitchState, &SWstate);
		if(SWstate==0)
		{
		LED_enuLedTurnON(&LED_AstrLedConfig[1]);
		LED_enuLedTurnON(&LED_AstrLedConfig[0]);

		}
		else
		{
		LED_enuLedTurnOFF(&LED_AstrLedConfig[1]);
		LED_enuLedTurnOFF(&LED_AstrLedConfig[0]);

		}


	}
	return 0;
}

