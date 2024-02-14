/*
 * SERVO_priv.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_HAL_SERVO_SERVO_PRIV_H_
#define ATMEGA32_CTOS_HAL_SERVO_SERVO_PRIV_H_

/* private macros for servo pins */
#define SERVO_OC1A		DIO_u8PIN5
#define SERVO_OC1B		DIO_u8PIN4


/* private macros for timer registers needed in servo calculations */
#define ICR1			*((volatile u16*)0x46) 			/*input capture register*/
#define OCR1A			*((volatile u16*)0x4a)
#define OCR1B			*((volatile u16*)0x48)


/* private macros for timer prescalers needed in servo calculations */
#define TIMER_CLK_STOP			0
#define TIMER_NO_PRESCALER		1ULL
#define TIMER_PRESCALER_8		8ULL
#define TIMER_PRESCALER_64		64ULL
#define TIMER_PRESCALER_128		128ULL
#define TIMER_PRESCALER_256		256ULL
#define TIMER_PRESCALER_1024	1024ULL


/* prototupe for static mapping functions */
static long long map(long long val, long long in_min, long long in_max, long long out_min, long long out_max);

#endif /* ATMEGA32_CTOS_HAL_SERVO_SERVO_PRIV_H_ */
