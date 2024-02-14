/*
 * SERVO_int.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_HAL_SERVO_SERVO_INT_H_
#define ATMEGA32_CTOS_HAL_SERVO_SERVO_INT_H_

/*
 * @brief function to initialize the servo motor
 * @return error state
 */
ES_t SERVO_enuInit();


/*
 * @brief function to set the desired angle for limiting servo
 *
 * @param[in] Copy_u8Angle: the desired angle
 *
 * @return error state
 */
ES_t SERVO_enuSetLimitAngle(u8 Copy_u8Angle);


/*
 * @brief function to set the desired speed for continous servo
 *
 * @param[in] Copy_u8Speed: the desired speed
 *
 * @return error state
 */
ES_t SERVO_enuSetContSpeed(s8 Copy_u8Speed);



#endif /* ATMEGA32_CTOS_HAL_SERVO_SERVO_INT_H_ */
