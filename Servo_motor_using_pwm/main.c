/********************************
 * main.c						*
 *	lab: Servo Motor Control	*
 *  Created on: Dec 18, 2023	*
 *      Author: Raghad Islam	*	
 *								*
 ********************************/
 
 /* -------- includes -------- */
#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"
#include <util/delay.h>

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/TIMER/timer_int.h"

#include "ATmega32_CTOS/HAL/Servo/SERVO_int.h"


int main()
{
	/* initializations */
	TIMER1_enuInit();
	SERVO_enuInit();

	while(1){
		
		/*Set desired angle */
		SERVO_enuSetLimitAngle(180); // any angle between 0 and 180 is valid
	}
	return 0;
}