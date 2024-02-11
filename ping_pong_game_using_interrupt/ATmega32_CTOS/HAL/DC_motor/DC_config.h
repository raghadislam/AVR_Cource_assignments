/*
 * DC_config.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_HAL_DC_MOTOR_DC_CONFIG_H_
#define ATMEGA32_CTOS_HAL_DC_MOTOR_DC_CONFIG_H_

/* determine the number of used motors */
#define NUM_OF_MOTORS 	1


DC_t DC_AstrConfig[NUM_OF_MOTORS] =
{
		{
				DIO_u8PORTC, DIO_u8PIN0,
				DIO_u8PORTC, DIO_u8PIN1
		} /* first motor */
};

#endif /* ATMEGA32_CTOS_HAL_DC_MOTOR_DC_CONFIG_H_ */
