/*
 * SERVO_prog.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"
#include "../../SERVICE/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TIMER/timer_int.h"

#include "SERVO_priv.h"
#include "SERVO_config.h"

/* global variable to hold the period value needed for the servo motor */
u16 Global_u16PeriodTime = 0;



ES_t SERVO_enuInit()
{
	ES_t Local_enuErrorState = ES_NOK;

	/* set the pwm pin as output */
	DIO_enuSetPinDir(DIO_u8PORTD,SERVO_PIN,DIO_u8OUTPUT);

	/* set the period as 20 ms to communicate with the servo */
	Global_u16PeriodTime = (20ULL * (SYSTEM_CLK/1000ULL)) / SERVO_TIMER_PRESCALER ;
	ICR1 = Global_u16PeriodTime - 1;

	return Local_enuErrorState;
}


/*
 * @brief function to set the desired angle for limiting servo
 * @param[in] Copy_u8Angle: the desired angle
 * @return error state
 */
ES_t SERVO_enuSetLimitAngle(u8 Copy_u8Angle)
{
	ES_t Local_enuErrorState = ES_NOK;
	u16 Local_u8ONTime = 0;
	u16 Local_u8Duty = 0;

	if((Copy_u8Angle >= 0) && (Copy_u8Angle <= 180))
	{
		Local_enuErrorState = ES_OK;
		/* Convert from the angle to on time */
		Local_u8ONTime = map(Copy_u8Angle,0,180,1000,2000);

		/* Calculate the duty cycle */
		Local_u8Duty = (100ULL * Local_u8ONTime) / 20000ULL;

		/* set the duty cycle */
#if(SERVO_PIN == SERVO_OC1A)

		OCR1A = ((Local_u8Duty * (Global_u16PeriodTime - 1ULL)) / 100ULL);

#elif(SERVO_PIN == SERVO_OC1B)

		OCR1B = ((Local_u8Duty * (Global_u16PeriodTime - 1ULL)) / 100ULL);

#else
#error "wrong servo pin"
#endif
	}
	else Local_enuErrorState = ES_OUT_OF_RANGE;

	return Local_enuErrorState;
}


/*
 * @brief function to set the desired speed for continous servo
 * @param[in] Copy_u8Speed: the desired speed
 * @return error state
 */
ES_t SERVO_enuSetContSpeed(s8 Copy_u8Speed)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8ONTime = 0;
	u8 Local_u8Duty = 0;

	if(Copy_u8Speed >= -100 && Copy_u8Speed <=100)
	{
		Local_enuErrorState = ES_OK;
		/* Convert from the angle to on time */
		Local_u8ONTime = map(Copy_u8Speed,-100,100,750,2500);

		/* Calculate the duty cycle */
		Local_u8Duty = (100ULL * Local_u8ONTime)/ 20000ULL;

		/* set the duty cycle */
#if(SERVO_PIN == SERVO_OC1A)

		OCR1A = ((Local_u8Duty * (Global_u16PeriodTime - 1ULL)) / 100ULL);

#elif(SERVO_PIN == SERVO_OC1B)

		OCR1B = ((Local_u8Duty * (Global_u16PeriodTime - 1ULL)) / 100ULL);

#else
#error "wrong servo pin"
#endif
	}
	else Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}


/* ================= static function for mapping =================*/

static long long map(long long val, long long in_min, long long in_max, long long out_min, long long out_max)
{
	return ((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
