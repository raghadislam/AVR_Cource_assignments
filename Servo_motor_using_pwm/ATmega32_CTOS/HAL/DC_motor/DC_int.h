/*
 * DC_int.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_HAL_DC_MOTOR_DC_INT_H_
#define ATMEGA32_CTOS_HAL_DC_MOTOR_DC_INT_H_

/*
 * @brief function to initialize the DC motor
 *
 * @return error statues
 */
ES_t DC_enuInit();


/*
 * @brief function to rotate the DC motor in the clock wise direction
 *
 * @return error statues
 */
ES_t DC_enuRotateCW();


/*
 * @brief function to rotate the DC motor in the counter clock wise direction
 *
 * @return error statues
 */
ES_t DC_enuRotateCCW();



#endif /* ATMEGA32_CTOS_HAL_DC_MOTOR_DC_INT_H_ */
