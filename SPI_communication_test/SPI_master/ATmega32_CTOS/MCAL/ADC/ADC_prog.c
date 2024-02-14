/*
 * ADC_prog.c
 *
 *  Created on: Sep 21, 2023
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_ADC_ADC_PROG_C_
#define ATMEGA32_CTOS_MCAL_ADC_ADC_PROG_C_

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"
#include "../../SERVICE/errorState.h"
#include "ADC_int.h"
#include "ADC_priv.h"
#include "ADC_config.h"

/* pointer to the callback function which will run as ISR on ADC conversion complete */
static void (*Global_pvCallBack)(u16 x) = NULL;

/* static variable to hold the ADC value pointer */
static u16 *Global_pu16ADCValue = 0;

/* Global flag for the ADC Busy State*/
static u8 Global_u8ADCState = IDLE;

/* Flag to indicate the interrupt source */
static u8 Global_u8InterruptFlag = 0;

/* Global variable to carry chain channels array */
static u8* Global_pu8ChaniChannelArr = NULL;

/* Global variable to carry chain results array */
static u16* Global_pu16ChainResultsArr = NULL;

/* Global variable to carry the chain size */
static u8 Global_u8ChainSize;

/* Global variable to carry the current chain conversion index */
static u8 Global_u8ChainIndex = 0;


/**
 * @brief initialization function
 * @return the Error state of the function
 */
ES_t ADC_enuInit(){

	ES_t Local_u8ErrorState = ES_OK;


#if (ADC_INITIAL_STATE == ADC_ENABLED)

	/*--------------- specify the reference voltage ---------------*/

#if (ADC_REFERENCE_VOLTAGE == ADC_AREF)
	Clr_bit(ADMUX,ADMUX_REFS0); Clr_bit(ADMUX,ADMUX_REFS1);

#elif (ADC_REFERENCE_VOLTAGE == ADC_VCC)
	Set_bit(ADMUX,ADMUX_REFS0); Clr_bit(ADMUX,ADMUX_REFS1);

#elif (ADC_REFERENCE_VOLTAGE == ADC_INTERNAL_VREF)
	Set_bit(ADMUX,ADMUX_REFS0); Set_bit(ADMUX,ADMUX_REFS1);

#else
#error "invalid ADC reference voltage selection"
#endif

	/*--------------- specify the ADC right or left adjust ---------------*/

#if ADC_ADJUST_RESULT == ADC_RIGHT_ADJUST
	Clr_bit(ADMUX,ADMUX_ADLAR);

#elif ADC_ADJUST_RESULT == ADC_LEFT_ADJUST
	Set_bit(ADMUX,ADMUX_ADLAR);

#else
#error "invalid ADC adjust selection"
#endif

	/*---------------------- specify the ADC Prescaler ----------------------*/

#if ( IS_VALID_PRESCALER(ADC_PRESCALER) )
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= ADC_PRESCALER;
#else
#error "invalid ADC prescaler selection"
#endif

	/*----------------- enable/disable the ADC Auto trigger -----------------*/

#if   (ADC_AUTO_TRIGGER_STATE == ADC_AUTO_TRIGGER_ENABLED)
	Set_bit(ADCSRA,ADCSRA_ADATE);

#elif (ADC_AUTO_TRIGGER_STATE == ADC_AUTO_TRIGGER_DISABLED)
	Clr_bit(ADCSRA,ADCSRA_ADATE);

#else
#error "invalid ADC auto trigger mode selection"
#endif

	/*----------------- enable/disable the ADC interrupt -----------------*/

#if   (ADC_INTERRUPT_STATE == ADC_INT_ENABLED)
	Set_bit(ADCSRA,ADCSRA_ADIE);

#elif (ADC_INTERRUPT_STATE == ADC_INT_DISABLED)
	Clr_bit(ADCSRA,ADCSRA_ADIE);

#else
#error "invalid ADC interrupt mode selection"
#endif


	/*------------------- specify the auto trigger source -------------------*/

#if ( IS_VALID_AUTO_TRIGGER_SOURCE(ADC_AUTO_TRIGGER_SOURCE) )
	SFIOR &= AUTO_TRIGGER_SOURCE_MASK;
	SFIOR |= ADC_AUTO_TRIGGER_SOURCE;

#else
#error "invalid ADC auto trigger source selection"
#endif


	/*----------------------- enable the ADC peripheral----------------------*/

	Set_bit(ADCSRA,ADCSRA_ADEN);

#elif (ADC_INITIAL_STATE == ADC_DISABLED)
	Clr_bit(ADCSRA,ADCSRA_ADEN);

#else
#error "invalid ADC enable/disable selection"
#endif

	return Local_u8ErrorState;
}


/**
 * @brief Synchronous function to get the reading using busy waiting
 *
 * @param Copy_u8Channel: the selected ADC channel
 * @param Copy_pu16Reading: variable in which we return the reading
 *
 * @return the Error state of the function
 */
ES_t ADC_enuBlockingRead(u8 Copy_u8Channel, u16* Copy_pu16Reading){

	ES_t Local_u8ErrorState = ES_OK;
	u32 Local_u32TimeCount = 0;

	if(Copy_pu16Reading != NULL){

		if(Global_u8ADCState == IDLE) {

			/* ADC now is busy */
			Global_u8ADCState = BUSY;

			/* Set the required channel to the MUX bits */

			if(IS_VALID_CHANNEL(Copy_u8Channel))
			{
				ADMUX = (ADMUX & CHANNEL_SELECTION_MASK) | Copy_u8Channel;
			}
			else Local_u8ErrorState = ES_OUT_OF_RANGE;

			/* start conversion */
			Set_bit(ADCSRA,ADCSRA_ADSC);

			/* turn off ADC interrupt */
			Clr_bit(ADCSRA, ADCSRA_ADIE);

			/* Polling (busy waiting) until the conversion complete flag is set */
			while((Get_bit(ADCSRA,ADCSRA_ADIF) == LOW) && (Local_u32TimeCount < ADC_u32TIMOUT)){
				Local_u32TimeCount++;
			}

			if(Local_u32TimeCount == ADC_u32TIMOUT)
			{
				/* loop is broken because timeout is reached*/
				Local_u8ErrorState = ES_TIME_OUT;
			}
			else
			{
				/* loop is broken because flag is raised
				 * Clear the conversion complete flag
				 */
				Set_bit(ADCSRA,ADCSRA_ADIF);

#if (ADC_INTERRUPT_STATE == ADC_INT_ENABLED)
				/* Re-enable ADC interrupt */
				Set_bit(ADCSRA, ADCSRA_ADIE);
#endif


#if (ADC_RESOLUTION == ADC_8BIT)
				*Copy_pu16Reading = ADCH;

#elif (ADC_RESOLUTION == ADC_10BIT)
				*Copy_pu16Reading = ADCVAL_10BITS;

#else
#error "Wrong ADC adjust"
#endif
			}

			/* ADC is now IDLE */
			Global_u8ADCState = IDLE;
		}
		else {
			Local_u8ErrorState = ES_BUSY_STATE;
		}
	}
	else Local_u8ErrorState = ES_NULL_POINTER;

	return Local_u8ErrorState;
}


/**
 * @brief Asynchronous function to get the reading without waiting by only starting the conversion
 *        and then execute the notification function as ISR on ADC conversion complete
 *
 * @param Copy_u8Channel: the selected ADC channel
 * @param Copy_pu16Reading: variable in which we return the reading
 * @param Copy_pvNotficationFunc: the pointer to the callback function which will run as ISR on ADC conversion complete
 *
 * @return the Error state of the function
 */
ES_t ADC_enuReadNonBlocking(u8 Copy_u8Channel, u16* Copy_pu16Reading, void (*Copy_pvNotficationFunc)(u16 Copy_u16reading))
{
	ES_t Local_u8ErrorState = ES_OK;

	if(Copy_pu16Reading != NULL && Copy_pvNotficationFunc != NULL)
	{

		if(Global_u8ADCState == IDLE)
		{
			/* set the interrupt source to single channel conversion */
			Global_u8InterruptFlag = SINGLE_CHANNEL;

			/* ADC is now Busy */
			Global_u8ADCState = BUSY;

			if (IS_VALID_CHANNEL(Copy_u8Channel))
			{
				/* Copy pointer to global variable for use in ISR */
				Global_pu16ADCValue = Copy_pu16Reading;

				/* assign address of the Call Back function in a global variable */
				Global_pvCallBack = Copy_pvNotficationFunc;

				/* Select the required channel by setting the four LSBs in ADMUX */
				ADMUX = (ADMUX & 0xF0) | (Copy_u8Channel);

				/* Start Conversion by setting ADSC bit */
				Set_bit(ADCSRA, ADCSRA_ADSC);

				/* ADC Conversion Complete Interrupt Enable */
				Set_bit(ADCSRA , ADCSRA_ADIE) ;
			}
			else
			{
				Local_u8ErrorState = ES_OUT_OF_RANGE;
			}

		}
		else
		{
			Local_u8ErrorState = ES_BUSY_STATE;
		}
	}
	else Local_u8ErrorState = ES_NULL_POINTER;
	return Local_u8ErrorState;
}



ES_t ADC_enuReadChain(Chain_t* Copy_Chain)
{
	ES_t Local_u8ErrorState = ES_OK;
	if(Copy_Chain != NULL)
	{
		if(Global_u8ADCState == IDLE)
		{
			/* ADC is now Busy */
			Global_u8ADCState = BUSY;

			/* set the interrupt source to chain conversion */
			Global_u8InterruptFlag = CHAIN_CONVERSION;

			/* initialize Chain channel array */
			Global_pu8ChaniChannelArr = Copy_Chain->Channels;

			/* initialize Chain result array */
			Global_pu16ChainResultsArr = Copy_Chain->Results;

			/* initialize Chain size */
			Global_u8ChainSize = Copy_Chain->Size;

			/* initialize Chain notfication function */
			Global_pvCallBack = Copy_Chain->NotificationFunc;

			/* initialize current conversion index */
			Global_u8ChainIndex = 0;

			/* set the required initial channel */
			ADMUX = (ADMUX & 0xF0) | (Global_pu8ChaniChannelArr[Global_u8ChainIndex]);

			/* Start Conversion by setting ADSC bit */
			Set_bit(ADCSRA, ADCSRA_ADSC);

			/* ADC Conversion Complete Interrupt Enable */
			Set_bit(ADCSRA , ADCSRA_ADIE) ;

		}
		else Local_u8ErrorState = ES_BUSY_STATE;

	}
	else Local_u8ErrorState = ES_NULL_POINTER;


	return Local_u8ErrorState;
}



/*========================== ADC ISR ==========================*/


void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	/* check  the interrupt source */
	if (Global_u8InterruptFlag == SINGLE_CHANNEL)
	{
		/* Read the ADC value from the ADC Data Register */
#if (ADC_RESOLUTION == ADC_8BIT)
			*Global_pu16ADCValue = ADCH;
#elif (ADC_RESOLUTION == ADC_8BIT)
			*Global_pu16ADCValue = ADCVAL_10BITS;
#else
#error " Unsupported ADC resolution "
#endif

		/* Call the Callback function in the application after completion of the ADC conversion */
		if (Global_pvCallBack != NULL)
		{
			//*Global_pu16ADCValue = ((u32)(*Global_pu16ADCValue)*5000ULL)/256ULL;
			Global_pvCallBack(*Global_pu16ADCValue);
		}

		/* ADC is now IDLE */
		Global_u8ADCState = IDLE;

		/* disable ADC conversion complete interrupt*/
		Clr_bit(ADCSRA , ADCSRA_ADIE);
	}
	else if(Global_u8InterruptFlag == CHAIN_CONVERSION)
	{
		/* read current conversion */
#if (ADC_RESOLUTION == ADC_8BIT)
		Global_pu16ChainResultsArr[Global_u8ChainIndex] = ADCH;
#elif (ADC_RESOLUTION == ADC_10BIT)
		Global_pu16ChainResultsArr[Global_u8ChainIndex] = ADCVAL_10BITS;
#else
#error " Unsupported ADC resolution "
#endif
		/* increment chain index */
		Global_u8ChainIndex++;

		/* check if chain finished */
		if(Global_u8ChainIndex == Global_u8ChainSize)
		{
			/* chain is finished */

			/* ADC is now idle*/
			Global_u8ADCState = IDLE;

			/* call notificaion function */
			Global_pvCallBack(Global_pu16ChainResultsArr[Global_u8ChainIndex]);

			/* disable ADC conversion complete interrupt*/
			Clr_bit(ADCSRA , ADCSRA_ADIE);
		}
		else
		{
			/* chain is not finished */

			/* set the new required channel */
			ADMUX = (ADMUX & 0xF0) | (Global_pu8ChaniChannelArr[Global_u8ChainIndex]);

			/* Start Conversion by setting ADSC bit */
			Set_bit(ADCSRA, ADCSRA_ADSC);
		}
	}
}

#endif /* ATMEGA32_CTOS_MCAL_ADC_ADC_PROG_C_ */
