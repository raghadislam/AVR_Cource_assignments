/*
 * LM35_int.h
 *
 *  Created on: Jan 26, 2024
 *      Author: DeLL
 */

#ifndef ATMEGA32_CTOS_HAL_LM35_LM35_INT_H_
#define ATMEGA32_CTOS_HAL_LM35_LM35_INT_H_

u16 LM35_enuGetTempReadingBlocking(u16* Copy_pu16Reading);
u16 LM35_enuGetTempReadingNonBlocking(u16* Copy_pu16Reading, void (*Copy_pvNotficationFunc)(u16 Copy_u16reading));

#endif /* ATMEGA32_CTOS_HAL_LM35_LM35_INT_H_ */
