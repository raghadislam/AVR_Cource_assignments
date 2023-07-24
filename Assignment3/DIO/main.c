/*
 * main.c
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */
#include "STDTypes.h"
#include "DIO_config.h"
#include "DIO_priv.h"
#include "errorState.h"
#include "DIO_int.h"
#include <util/delay.h>

int main(){
	DIO_enuInit();
	u8 _7SegNo[10] = { 0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6F};
	while(1){
		for (int i =0; i<=9; i++) {
			DIO_enuSetPortVal(DIO_u8PORTB, _7SegNo[i]);
			_delay_ms(500);
		}
	}
	return 0;
}
