/*
 * SPI_prog.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Raghad Islam
 */
#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"
#include "../../SERVICE/BIT_MATH.h"

#include "SPI_priv.h"
#include "SPI_config.h"


/* global varianles used in the SPI ISR function */
static u8 *SPI_Pu8TransmittedString = NULL;
static u8 *SPI_Pu8ReceivedString = NULL;
static u8 SPI_u8Index = 0;
static void (*SPI_Callback)(void) = NULL;

/*==================================== SPI APIs ====================================*/

ES_t SPI_enuInit()
{
	ES_t Local_enuErrorState = ES_OK;
#if SPI_MODE == SPI_MASTER

	/* Set MOSI and SCK output, all others input */
	Set_bit(SPI_DDR,SPI_SCK);
	Set_bit(SPI_DDR,SPI_MOSI);
	Clr_bit(SPI_DDR,SPI_MISO);

	/* check the master ss pin mode */
	if(SPI_MASTER_SS == SPI_INPUT)
	{
		Clr_bit(SPI_DDR,SPI_SS);
	}
	else Set_bit(SPI_DDR,SPI_SS);

	/* Enable SPI, Master */
	Set_bit(SPCR,SPCR_MSTR);

	/* set the desired data order */
	if(SPI_DATA_ORDER == SPI_LSB_FIRST)
	{
		Set_bit(SPCR,SPCR_DORD);
	}
	else if(SPI_DATA_ORDER == SPI_MSB_FIRST)
	{
		Clr_bit(SPCR,SPCR_DORD);
	}
	else
	{
		Local_enuErrorState = ES_NOK;
	}

	/* set the desired clock polarity */
	if(SPI_CLK_POLARITY == SPI_LOW)
	{
		Clr_bit(SPCR,SPCR_CPOL);
	}
	else if(SPI_CLK_POLARITY == SPI_HIGH)
	{
		Set_bit(SPCR,SPCR_CPOL);
	}
	else
	{
		Local_enuErrorState = ES_NOK;
	}

	/* set the desired clock phase */
	if(SPI_CLK_PHASE == SPI_SAMPLE_FIRST)
	{
		Clr_bit(SPCR,SPCR_CPHA);
	}
	else if(SPI_CLK_PHASE == SPI_SETUP_FIRST)
	{
		Set_bit(SPCR,SPCR_CPHA);
	}
	else
	{
		Local_enuErrorState = ES_NOK;
	}

	/* select the SPI Clock Rate */
	SPCR |= SPI_SPR_BITS;

	if(SPI_CLK_RATE > SPI_DIVISION_BY_128)
	{
		Set_bit(SPSR,SPSR_SPI2X);

	}

	/* enable the SPI */
	Set_bit(SPCR,SPCR_SPE);


#elif SPI_MODE == SPI_SLAVE

	/* Set MISO output, all others input */
	Set_bit(SPI_DDR,SPI_MISO);
	Clr_bit(SPI_DDR,SPI_MOSI);
	Clr_bit(SPI_DDR,SPI_SCK);
	Clr_bit(SPI_DDR,SPI_SS);

	/* clear master bit */
	Clr_bit(SPCR,SPCR_MSTR);

	/* set the desired data order */
		if(SPI_DATA_ORDER == SPI_LSB_FIRST)
		{
			Set_bit(SPCR,SPCR_DORD);
		}
		else if(SPI_DATA_ORDER == SPI_MSB_FIRST)
		{
			Clr_bit(SPCR,SPCR_DORD);
		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}

		/* set the desired clock polarity */
		if(SPI_CLK_POLARITY == SPI_LOW)
		{
			Clr_bit(SPCR,SPCR_CPOL);
		}
		else if(SPI_CLK_POLARITY == SPI_HIGH)
		{
			Set_bit(SPCR,SPCR_CPOL);
		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}

		/* set the desired clock phase */
		if(SPI_CLK_PHASE == SPI_SAMPLE_FIRST)
		{
			Clr_bit(SPCR,SPCR_CPHA);
		}
		else if(SPI_CLK_PHASE == SPI_SETUP_FIRST)
		{
			Set_bit(SPCR,SPCR_CPHA);
		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}

	/* enable the SPI */
	Set_bit(SPCR,SPCR_SPE);


#else
#error "unsupported SPI mode"
#endif

	return Local_enuErrorState;
}



ES_t SPI_enuTranceiveByte(u8 Copy_u8SentData, u8* Copy_pu8ReceivedData)
{
	/* Local variable to hold the error state */
	ES_t Local_enuErrorState = ES_OK;

	/* local variable to apply time out mechanism*/
	u32 Local_u8TimeOut = 0;

	if(Copy_pu8ReceivedData != NULL)
	{
		/* Start transmission */
		SPDR = Copy_u8SentData;

		/* Wait for transfere complete */
		while((Get_bit(SPSR,SPSR_SPIF) == 0) && (Local_u8TimeOut < SPI_TIMEOUT))
		{
			Local_u8TimeOut++;
		}
        /* Check if the transmission is complete */
		if(Local_u8TimeOut >= SPI_TIMEOUT )
		{
			Local_enuErrorState = ES_TIME_OUT;
		}
		else *Copy_pu8ReceivedData = SPDR;
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}


/**
 * @brief A function to send and receive a string using SPI.
 * @param Copy_Pu8SentString The string needed to be sent.
 * @param Copy_Pu8ReceivedString A pointer to the array needed to be filled with the received data.
 * @param CallBack A pointer to the function needed to be called after finishing transmission the buffer.
 * @return u8 The error state.
 */
ES_t SPI_u8TranceiveStringAsynch(u8 *Copy_Pu8SentData, u8 *Copy_pu8ReceivedData, void (*CallBack)(void))
{
    /* Local variable to hold the error state */
    ES_t Local_u8ErrorState = ES_OK;

    if (Copy_Pu8SentData != NULL && Copy_pu8ReceivedData != NULL && CallBack != NULL)
    {
        /* Initialize the global static variables */
        SPI_Pu8TransmittedString = Copy_Pu8SentData;
        SPI_Pu8ReceivedString = Copy_pu8ReceivedData;
        SPI_u8Index = 0;

        /* Initialize the global callback function */
        SPI_Callback = CallBack;

        /* Enable the SPI interrupt */
        Set_bit(SPCR, SPCR_SPIE);
    }
    else Local_u8ErrorState = ES_NULL_POINTER;

    return Local_u8ErrorState;
}

/*========================== Functions ==========================*/

void __vector_12(void)
{
    /* Receive the data */
    SPI_Pu8ReceivedString[SPI_u8Index] = SPDR;

    /* Check if the transmission is complete */
    if (SPI_Pu8TransmittedString[SPI_u8Index] == '\0')
    {
        /* Disable the SPI interrupt */
        Clr_bit(SPCR, SPCR_SPIE);

        /* Call the callback function */
        SPI_Callback();
    }
    else
    {
        /* Increment the index */
        SPI_u8Index++;

        /* Send the data */
        SPDR = SPI_Pu8TransmittedString[SPI_u8Index];
    }
}

