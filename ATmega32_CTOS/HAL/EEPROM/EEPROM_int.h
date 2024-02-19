/********************************
 * EEPROM_int.h					*
 *  Created on: Feb 14, 2024	*
 *      Author: Raghad Islam	*
 *								*
 ********************************/

#ifndef ATMEGA32_CTOS_HAL_EEPROM_EEPROM_INT_H_
#define ATMEGA32_CTOS_HAL_EEPROM_EEPROM_INT_H_

/**
 * @brief function to write one byte of data in the EEPROM.
 *
 * @param[in] Copy_u8Data: data to be written.
 *
 * @param[in] Copy_u16Address : address to be written on in the EEPROM
 *
 * @return the error statues.
 */
ES_t EEPROM_enuWriteByte(u8 Copy_u8Data, u16 Copy_u16Address);


/**
 * @brief function to Read one byte of data from the EEPROM.
 *
 * @param[in] Copy_u8Data: data to be read.
 *
 * @param[in] Copy_u16Address : address to read from the EEPROM
 *
 * @return the error statues.
 */
ES_t EEPROM_enuReadByte(u8 *Copy_Pu8Data, u16 Copy_u16Address);

#endif /* ATMEGA32_CTOS_HAL_EEPROM_EEPROM_INT_H_ */
