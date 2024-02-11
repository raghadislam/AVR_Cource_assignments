/*
 * DC_priv.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_HAL_DC_MOTOR_DC_PRIV_H_
#define ATMEGA32_CTOS_HAL_DC_MOTOR_DC_PRIV_H_

/* struct type for all motor configurations */
typedef struct {

	u8 DC_u8Port1;
	u8 DC_u8Pin1;

    u8 DC_u8Port2;
	u8 DC_u8Pin2;

}DC_t;

#define DC_MASK	7

#endif /* ATMEGA32_CTOS_HAL_DC_MOTOR_DC_PRIV_H_ */
