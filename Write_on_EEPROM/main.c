/********************************
 * main.c						*
 *								*
 *  Created on: Feb 1, 2024		*
 *      Author: Raghad Islam	*
 *      						*
 ********************************/
#include "../ATmega32_CTOS/SERVICE/STDTypes.h"
#include "../ATmega32_CTOS/SERVICE/errorState.h"
#include <util/delay.h>

#include "../ATmega32_CTOS/MCAL/TWI/TWI_int.h"
#include "../ATmega32_CTOS/HAL/EEPROM/EEPROM_int.h"

#include "../ATmega32_CTOS/HAL/seven_segment/Seven_segment_config.h"
#include "../ATmega32_CTOS/HAL/seven_segment/Seven_segment_int.h"

extern SEG_t SEVSEG_AstrConfig[NUM_OF_SEG];


int main() {

	TWI_enuMasterInit(TWI_NO_ADDRESS);

	Seven_segment_enuInit(SEVSEG_AstrConfig);
	Seven_segment_enuEnableCommon(0);
	Seven_segment_enuDisplayNum(0,0);

	/* Write data to EEPROM */

	EEPROM_enuWriteByte(0x00, 8);
	_delay_ms(10);

	EEPROM_enuWriteByte(0x00 + 1, 9);
	_delay_ms(10);

	EEPROM_enuWriteByte(0x00 + 2, 1);
	_delay_ms(10);

	/* Read data from EEPROM */

	u8 Local_u8data;

	EEPROM_enuReadByte(&Local_u8data, 0x00);
	Seven_segment_enuDisplayNum(0,Local_u8data);
	_delay_ms(1000);

	EEPROM_enuReadByte(&Local_u8data, 0x00+1);
	Seven_segment_enuDisplayNum(0,Local_u8data);
	_delay_ms(1000);

	EEPROM_enuReadByte(&Local_u8data, 0x00+2);
	Seven_segment_enuDisplayNum(0,Local_u8data);
	_delay_ms(1000);

	return 0;
}