/*
 * main.c
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#include "STDTypes.h"
#include "errorState.h"

#include "DIO_int.h"

#include "Seven_segment_int.h"

#include <util/delay.h>

int main()
{
	DIO_enuInit();
    if(Seven_segment_enuInit() == ES_OK){
    while(1)
    {
    for(u8 i =0 ; i<10 ; ++i )
    {
    	Seven_segment_enuDisplayNum(i);
    	_delay_ms(500);
    	Seven_segment_enuClearDisplay();
    	_delay_ms(500);

    }
    }
    }
	return 0;
}
