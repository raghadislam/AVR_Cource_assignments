/********************************
 * main.c						*
 *	lab: S/W ICU				*
 *  Created on: Dec 18, 2023	*
 *      Author: Raghad Islam	*	
 *								*
 ********************************/
 
 /* -------- includes -------- */
#include <util/delay.h>
#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/GIE/GIE_int.h"
#include "ATmega32_CTOS/MCAL/EXTI/EXTI_config.h"
#include "ATmega32_CTOS/MCAL/EXTI/EXTI_int.h"
#include "ATmega32_CTOS/MCAL/TIMER/timer_int.h"

#include "ATmega32_CTOS/HAL/LCD/LCD_int.h"

extern EXTI_t EXTI_AstrEXTIConfig[3];
u16 Global_u8PeriodTicks=0;
u16 Global_u8ONTicks=0;

void ICU_SW();

int main()
{
	
	/* initialize I/O pins */
	DIO_enuInit();
	/* initialize external interrupt to analyze the pwm signal */
	EXTI_enuInit(EXTI_AstrEXTIConfig);
	/* initialize Timer0 to generate the pwm signal */
	TIMER0_enuInit();
	/* initialize Timer1 to act as a tick counter */
	TIMER1_enuInit();
	/* initialize the LCD to To display the analyzed signal */
	LCD_enuInit();
	

	/* Set the CallBack function of the external interrupt */
	EXIT_enuINT0SetCallBack(&ICU_SW);


	TIMER_enuSetDutyCycle(TIMER0,50);

	/* enable global interrupt */
	GIE_viodEnable();

	while(1)
	{
		/* print results */
		LCD_enuGoto(1,0);
		LCD_enuWriteNumber(Global_u8PeriodTicks);
		LCD_enuGoto(2,0);
		LCD_enuWriteNumber(Global_u8ONTicks);
	}
	return 0;
}

void ICU_SW()
{
	static u8 local_u8Counter = 0;
	local_u8Counter++;
	if(local_u8Counter == 1)
	{
		/* clear the timer counter register */
		Timer_enuSetTimerVal(TIMER1,0);
	}
	else if(local_u8Counter == 2)
	{
		/* Read the timer counter register */
		Timer_enuGetTimerVal(TIMER1,&Global_u8PeriodTicks);
		
		/* change the sense of the eexternal interrupt 0 */
		EXTI_enuSetSenseCtrl(EXTI_INT0,FALLING_EDGE);
	}
	else if(local_u8Counter == 3)
	{
		/* Read the timer counter register */
		Timer_enuGetTimerVal(TIMER1,&Global_u8ONTicks);

		/* subtract the previous reading to get the on tiks only */
		Global_u8ONTicks -= Global_u8PeriodTicks;

		EXTI_enuIntDisable(EXTI_INT0);
	}
}

