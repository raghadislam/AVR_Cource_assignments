/*
 * LM35_prog.c
 *
 *  Created on: Jan 26, 2024
 *      Author: DeLL
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"

#include "../../MCAL/ADC/ADC_int.h"

#include "LM35_config.h"
#include "LM35_priv.h"

void (*Global_pvNotficationFunc)(u16 Copy_u16reading);

static void LM35_NotficationFunc(u16 Copy_u16Reading)
{
	u16 Local_u16MilliVolt = ((u32)Copy_u16Reading*5000ULL)/256ULL;
	u16 Local_u16Temp =Local_u16MilliVolt/10ULL;

	Global_pvNotficationFunc(Local_u16Temp);
}

u16 LM35_enuGetTempReadingBlocking(u16* Copy_pu16Reading)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_pu16Reading != NULL)
	{


		u16 Local_u8Reading=0;
		u16 Local_u16MilliVolt=0;
		u16 Local_u16Temp=0;

		/* get the ADC reading */
		ADC_enuBlockingRead(ADC_SINGLE_ENDED_ADC0,&Local_u8Reading);

		/* convert the digital value to analog value in millivolt */
		Local_u16MilliVolt = ((u32)Local_u8Reading*5000ULL)/256ULL;

		/* convert change in volt to change in temperature */
		Local_u16Temp =Local_u16MilliVolt/10ULL;

		return Local_u16Temp;
		*Copy_pu16Reading = Local_u16Temp;

	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}

u16 LM35_enuGetTempReadingNonBlocking(u16* Copy_pu16Reading, void (*Copy_pvNotficationFunc)(u16 Copy_u16reading))
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_pu16Reading != NULL) && (Copy_pvNotficationFunc != NULL))
	{
		Global_pvNotficationFunc = Copy_pvNotficationFunc;
		/* get the ADC reading */
		ADC_enuReadNonBlocking(ADC_SINGLE_ENDED_ADC0,Copy_pu16Reading,&LM35_NotficationFunc);

	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}
