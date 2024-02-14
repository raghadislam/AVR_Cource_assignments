/*
 * USART_prog.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"
#include "../../SERVICE/errorState.h"
#include "USART_priv.h"
#include "USART_config.h"


/* Static pointer to the string to be transmitted using the Asynchronous function */
static u8 *USART_Pu8TransmittedString;

/* Static pointer to the string to be received using the Asynchronous function */
static u8 *USART_Pu8ReceivedString;

/* Index using in asynchronous transmitting and receiving */
static u8 USART_u8Index1;
static u8 USART_u8Index2;

/* Static pointers for callback functions */
static void (*USART_ASychSendCallback)(void) = NULL;
static void (*USART_ASychReceiveCallback)(void) = NULL;


ES_t USART_enuInit()
{
	ES_t Local_enuErrorState = ES_OK;
	u8 Local_u8UCSRCval = 0;

	/* check if the transmitter is enabled */
	if(USART_TX_STATE == USART_ENABLE)
	{
		/* enable the transmitter */
		Set_bit(UCSRB,UCSRB_TXEN);

		/*check the Transmit Complete Interrupt state */
		if(USART_TX_INT_STATE == USART_ENABLE)
		{
			Set_bit(UCSRB,UCSRB_TXCIE);
		}
	}

	/* check if the receiver is enabled */
	if(USART_RX_STATE == USART_ENABLE)
	{
		/* enable the receiver */
		Set_bit(UCSRB,UCSRB_RXEN);

		/*check the Receive Complete Interrupt state */
		if(USART_RX_INT_STATE == USART_ENABLE)
		{
			Set_bit(UCSRB,UCSRB_RXCIE);
		}
	}

	/*check the Data Register Empty Interrupt state */
	if(USART_EMBTY_DR_INT_STATE == USART_ENABLE)
	{
		Set_bit(UCSRB,UCSRB_UDRIE);
	}

	/* Checking the parity type */
	if (USART_PARITY == USART_EVEN_PARITY)
	{
		Set_bit(Local_u8UCSRCval,UCSRC_URSEL);
		Set_bit(Local_u8UCSRCval, UCSRC_UPM1);
		Clr_bit(Local_u8UCSRCval, UCSRC_UPM0);
	}

	else if (USART_PARITY == USART_ODD_PARITY)
	{
		Set_bit(Local_u8UCSRCval,UCSRC_URSEL);
		Set_bit(Local_u8UCSRCval, UCSRC_UPM1);
		Set_bit(Local_u8UCSRCval, UCSRC_UPM0);
	}

	else if (USART_PARITY == USART_NO_PARITY)
	{
		Set_bit(Local_u8UCSRCval,UCSRC_URSEL);
		Clr_bit(Local_u8UCSRCval, UCSRC_UPM1);
		Clr_bit(Local_u8UCSRCval, UCSRC_UPM0);
	}
	else Local_enuErrorState = ES_NOK;

	/* Checking the USART Synchronization Mode */
	if(USART_SYNCHRONIZATION == USART_SYNCH)
	{
		Set_bit(Local_u8UCSRCval,UCSRC_UMSEL);

		/* Check Clock Polarity */
		if(USART_CLK_POLARITY == USART_TRANSMIT_AT_FALLING)
		{
			Set_bit(Local_u8UCSRCval,UCSRC_UCPOL);
		}
	}

	/* Checking the desired number os stop bits */
	if(USART_STOP_BITS == USART_ONE_STOP_BIT)
	{
		Clr_bit(Local_u8UCSRCval,UCSRC_USBS);
	}
	else if(USART_STOP_BITS == USART_ONE_STOP_BIT)
	{
		Set_bit(Local_u8UCSRCval,UCSRC_USBS);
	}
	else Local_enuErrorState = ES_NOK;

	/* Set the desired character size */
	switch(USART_DATA_SIZE)
	{
	case USART_FIVE_BITS:
		Clr_bit(UCSRB,UCSRB_UCSZ2);
		Clr_bit(Local_u8UCSRCval,UCSRC_UCSZ1);
		Clr_bit(Local_u8UCSRCval,UCSRC_UCSZ0);
		break;
	case USART_SIX_BITS:
		Clr_bit(UCSRB,UCSRB_UCSZ2);
		Clr_bit(Local_u8UCSRCval,UCSRC_UCSZ1);
		Set_bit(Local_u8UCSRCval,UCSRC_UCSZ0);
		break;
	case USART_SEVEN_BITS:
		Clr_bit(UCSRB,UCSRB_UCSZ2);
		Set_bit(Local_u8UCSRCval,UCSRC_UCSZ1);
		Clr_bit(Local_u8UCSRCval,UCSRC_UCSZ0);
		break;
	case USART_EIGHT_BITS:
		Clr_bit(UCSRB,UCSRB_UCSZ2);
		Set_bit(Local_u8UCSRCval,UCSRC_UCSZ1);
		Set_bit(Local_u8UCSRCval,UCSRC_UCSZ0);
		break;
	case USART_NINE_BITS:
		Set_bit(UCSRB,UCSRB_UCSZ2);
		Set_bit(Local_u8UCSRCval,UCSRC_UCSZ1);
		Set_bit(Local_u8UCSRCval,UCSRC_UCSZ0);
		break;
	default: Local_enuErrorState = ES_NOK;
	}
	/* srtting the UCSRC register value */
	UCSRC = Local_u8UCSRCval;

	/* set the USART Transmission Speed */

#if (USART_MODE == USART_NORMAL_MODE)

	/* Setting the baud rate */
	UBRRL = UBRR_VAL;
	UBRRH = (UBRR_VAL >> 8);

#elif USART_MODE == USART_DBL_SPEED_MODE

	/* Setting the U2X bit to enable double speed mode */
	Set_bit(UCSRA,UCSRA_U2X);

	/* Setting the baud rate */
	UBRRL = UBRR_DBL_VAL;
	UBRRH = (UBRR_DBL_VAL >> 8);
#else
#error "USART error : unsupported mode"
#endif

	return Local_enuErrorState;
}


ES_t USART_enuSendData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_OK;

	u32 Local_u32TimeOut = 0;

	/* wait until transmit buffer is empty */
	while((Get_bit(UCSRA,UCSRA_UDRE) == 0) && (Local_u32TimeOut < USART_TIMEOUT))
	{
		Local_u32TimeOut++;
	}

	if(Local_u32TimeOut < USART_TIMEOUT)
	{
		/* Put the data into the buffer */
		UDR = Copy_u8Data;
	}
	else
	{
		Local_enuErrorState = ES_TIME_OUT;
	}

	return Local_enuErrorState;
}

ES_t USART_enuReceiveData(u8* Copy_pu8Data)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Local variable for applying the Timeout mechanism */
	u32 Local_u32TimeOut=0;

	if(Copy_pu8Data != NULL)
	{
		/* Wait for data to be received */
		while((Get_bit(UCSRA,UCSRA_RXC) == 0) && (Local_u32TimeOut < USART_TIMEOUT))
		{
			Local_u32TimeOut++;
		}

		if(Local_u32TimeOut < USART_TIMEOUT)
		{
			/* Get and return received data from buffer */
			*Copy_pu8Data = UDR;
		}
		else
		{
			Local_enuErrorState = ES_TIME_OUT;
		}
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}



ES_t USART_enuSendStringSynch(const u8* Copy_u16String)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Local variable for applying the Timeout mechanism */
	u32 Local_u32TimeOut = 0;

	if(Copy_u16String != NULL){

		/* loop until the ebd of the string */
		while(*Copy_u16String)
		{
			/* wait until transmit buffer is empty */
			while(Get_bit(UCSRA,UCSRA_UDRE)==0 && Local_u32TimeOut < USART_TIMEOUT)
			{
				Local_u32TimeOut++;
			}

			if(Local_u32TimeOut < USART_TIMEOUT)
			{
				/* Put the data into the buffer */
				UDR = *Copy_u16String;
			}
			else {
				Local_enuErrorState = ES_TIME_OUT;
				break;
			}

			/* point to the next character*/
			Copy_u16String++;
		}
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}



ES_t USART_enuReceiveStringSynch(char* Copy_u16String)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Local variables */
	u32 Local_u32TimeOut=0;
	u8 Local_u8Iterator = 0;
	char Local_u8Data = 0;


	if(Copy_u16String != NULL)
	{

		while(1)
		{
			/* Wait for data to be received */
			while((Get_bit(UCSRA,UCSRA_RXC) == 0) && (Local_u32TimeOut < USART_TIMEOUT))
			{
				Local_u32TimeOut++;
			}

			if(Local_u32TimeOut < USART_TIMEOUT)
			{
				/* Get and return received data from buffer */
				Local_u8Data = UDR;
			}
			else
			{
				Local_enuErrorState = ES_TIME_OUT;
				break;
			}
			if(( Local_u8Data == '\n'))
			{
				/* put the end of the string */
				Copy_u16String[Local_u8Iterator] = '\0';
				break;
			}
			else {
				Copy_u16String[Local_u8Iterator] = Local_u8Data;

				/* increment the iterator */
				Local_u8Iterator++;
			}
		}
	}
	else Local_enuErrorState = ES_NULL_POINTER;


	return Local_enuErrorState;
}



ES_t USART_enuSendStringAsynch(u8* Copy_u16String, void (*NotificationFunc)(void))
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u16String != NULL && NotificationFunc != NULL)
	{
		/* Set the global CallBack function */
		USART_ASychSendCallback = NotificationFunc;

		/* Set the global string to be transmitted */
		USART_Pu8TransmittedString = Copy_u16String;

		/* reset the global string index */
		USART_u8Index1 = 0;

		/* enable the empty data register interrupt */
		Set_bit(UCSRB,UCSRB_UDRIE);
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}


ES_t USART_enuReceiveStringAsynch(u8* Copy_u16String, void (*NotificationFunc)(void))
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u16String != NULL && NotificationFunc != NULL)
	{
		/* Set the global CallBack function */
		USART_ASychReceiveCallback = NotificationFunc;

		/* Set the global string to be transmitted */
		USART_Pu8ReceivedString = Copy_u16String;

		/* reset the global string index */
		USART_u8Index2 = 0;

		/*enable the Receive Complete Interrupt state */
		Set_bit(UCSRB,UCSRB_RXCIE);
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}

/* USART, Rx Complete */
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void){

	USART_Pu8ReceivedString[USART_u8Index2] = UDR;

	/* check if the string ended */
	if(USART_Pu8ReceivedString[USART_u8Index2] != '\n')
	{
		/* point to the next character */
		USART_u8Index2++;
	}
	else
	{

		/* Disable the Receive Complete interrupt */
		Clr_bit(UCSRB,UCSRB_RXCIE);

		/* reset the global string index */
		USART_u8Index2 = 0;

		/* terminate the string */
		USART_Pu8ReceivedString[USART_u8Index2] = '\0';

		USART_enuSendStringSynch(USART_Pu8ReceivedString);

		/* execute the Notification function */
		USART_ASychReceiveCallback();
	}
}


/* USART Data Register Empty ISR */
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void){

	/* check if the stribg ended */
	if(USART_Pu8TransmittedString[USART_u8Index1] != '\0')
	{
		/* Put the current character into buffer */
		UDR = USART_Pu8TransmittedString[USART_u8Index1];

		/* point to the next character */
		USART_u8Index1++;
	}
	else
	{
		/* Disable the empty data register interrupt */
		Clr_bit(UCSRB,UCSRB_UDRIE);

		/* reset the global string index */
		USART_u8Index1 = 0;

		/* execute the Notification function */
		USART_ASychSendCallback();
	}
}

/* USART, Tx Complete ISR */
void __vector_15 (void) __attribute__((signal));
void __vector_15 (void){

}
