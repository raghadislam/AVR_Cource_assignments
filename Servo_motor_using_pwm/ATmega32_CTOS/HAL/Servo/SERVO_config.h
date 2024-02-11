/*
 * SERVO_config.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_HAL_SERVO_SERVO_CONFIG_H_
#define ATMEGA32_CTOS_HAL_SERVO_SERVO_CONFIG_H_


/*
 * specify the servo pin for connection
 * options: 1- SERVO_OC1A
 * 			2- SERVO_OC1B
 */
#define SERVO_PIN				SERVO_OC1A


/* choose prescaler
 * options:
 * 1- TIMER_CLK_STOP
 * 2- TIMER_NO_PRESCALER
 * 3- TIMER_PRESCALER_8
 * 4- TIMER_PRESCALER_64
 * 5- TIMER_PRESCALER_128 (timer2 only)
 * 5- TIMER_PRESCALER_256
 * 6- TIMER_PRESCALER_1024
 * 7- TIMER_EXT_PRESCALER_RISING  (timer0 and timer1 only)
 * 8- TIMER_EXT_PRESCALER_FALLING (timer0 and timer1 only) */
#define SERVO_TIMER_PRESCALER	TIMER_PRESCALER_8

#endif /* ATMEGA32_CTOS_HAL_SERVO_SERVO_CONFIG_H_ */
