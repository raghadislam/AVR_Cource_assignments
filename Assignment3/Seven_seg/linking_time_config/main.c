/*
 * main.c
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#include "STDTypes.h"
#include "errorState.h"

#include "DIO_int.h"

#include "Seven_segment_config.h"
#include "Seven_segment_int.h"

#include <util/delay.h>

extern SEG_t SEVSEG_AstrConfig[NUM_OF_SEG];
int main()
{
	DIO_enuInit();
	if(Seven_segment_enuInit(SEVSEG_AstrConfig)==ES_OK)
	{
	while(1)
	{
		for(u8 i=0 ; i<10 ; i++)
		{
			Seven_segment_enuDisableCommon(0);
			Seven_segment_enuDisplayNum(0,7);
			Seven_segment_enuEnableCommon(1);
			_delay_ms(15);
			Seven_segment_enuDisableCommon(1);
			Seven_segment_enuDisplayNum(0,7);
			Seven_segment_enuEnableCommon(0);
			_delay_ms(15);
		}
	}
}

	return 0;
}
