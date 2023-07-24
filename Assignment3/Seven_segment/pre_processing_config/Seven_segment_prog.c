/*
 * Seven_segment_prog.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Raghad Islam
 */
#include "STDTypes.h"
#include "errorState.h"

#include "DIO_int.h"

#include "Seven_segment_config.h"
#include "Seven_segment_priv.h"

ES_t Seven_segment_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	u32 Local_u32Check = 0;

	Local_u32Check |= ((DIO_enuSetPinDir(SEG_APORT, SEG_APIN, DIO_u8OUTPUT))<<0 );
	Local_u32Check |= ((DIO_enuSetPinDir(SEG_BPORT, SEG_BPIN, DIO_u8OUTPUT))<<3 );
	Local_u32Check |= ((DIO_enuSetPinDir(SEG_CPORT, SEG_CPIN, DIO_u8OUTPUT))<<6 );
	Local_u32Check |= ((u32)(DIO_enuSetPinDir(SEG_DPORT, SEG_DPIN, DIO_u8OUTPUT))<<9 );
	Local_u32Check |= ((u32)(DIO_enuSetPinDir(SEG_EPORT, SEG_EPIN, DIO_u8OUTPUT))<<12);
	Local_u32Check |= ((u32)(DIO_enuSetPinDir(SEG_FPORT, SEG_FPIN, DIO_u8OUTPUT))<<15);
	Local_u32Check |= ((u32)(DIO_enuSetPinDir(SEG_GPORT, SEG_GPIN, DIO_u8OUTPUT))<<18);

#if SEG_CMN_PORT <= DIO_u8PORTD && SEG_CMN_PIN <= DIO_u8PIN7
		DIO_enuSetPinDir(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8OUTPUT);
#elif SEG_CMN_PORT == NOT_CONNECTED || SEG_CMN_PIN == NOT_CONNECTED

#else
#error "wrong selection for common "
#endif


#if SEG_DOT_PORT <= DIO_u8PORTD && SEG_DOT_PIN <= DIO_u8PIN7
		DIO_enuSetPinDir(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8OUTPUT);
#elif SEG_DOT_PORT == NOT_CONNECTED || SEG_DOT_PIN == NOT_CONNECTED

#else
#error "wrong selection for DOT "
#endif
		u8 Local_u8Iterator;
		for(Local_u8Iterator = 0 ; Local_u8Iterator < 21 ; Local_u8Iterator += 3)
		{
			if( ( ( Local_u32Check>>Local_u8Iterator ) &7 ) != ES_OK )
			{
				return Local_enuErrorState;
			}
		}
		Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}



ES_t Seven_segment_enuDisplayNum( u8 Copy_u8Num)
{
	ES_t Local_enuErrorState = ES_NOK;
	u16 Local_u32Check = 0;

	if(Copy_u8Num < 10)

	{
#if SEG_TYPE == COMMON_CATHODE
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_APORT, SEG_APIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>0)&1 ))<<0 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_BPORT, SEG_BPIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>1)&1 ))<<3 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_CPORT, SEG_CPIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>2)&1 ))<<6 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_DPORT, SEG_DPIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>3)&1 ))<<9 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_EPORT, SEG_EPIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>4)&1 ))<<12);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_FPORT, SEG_FPIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>5)&1 ))<<15);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_GPORT, SEG_GPIN, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>6)&1 ))<<18);

#elif SEG_TYPE == COMMON_ANODE
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_APORT, SEG_APIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>0)&1) ))<<0 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_BPORT, SEG_BPIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>1)&1) ))<<3 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_CPORT, SEG_CPIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>2)&1) ))<<6 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_DPORT, SEG_DPIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>3)&1) ))<<9 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_EPORT, SEG_EPIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>4)&1) ))<<12);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_FPORT, SEG_FPIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>5)&1) ))<<15);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_GPORT, SEG_GPIN, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>6)&1) ))<<18);
#else
#error "SEG type has wrong selection"

#endif

}
	else return ES_OUT_OF_RANGE;

	u8 Local_u8Iterator;
	for(Local_u8Iterator = 0 ; Local_u8Iterator < 21 ; Local_u8Iterator += 3)
	{
		if( ( ( Local_u32Check>>Local_u8Iterator ) &7 ) != ES_OK )
		{
			return Local_enuErrorState;
		}
	}
	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;

}

ES_t Seven_segment_enuEnableCommon()
{

	ES_t Local_enuErrorState = ES_NOK;

#if SEG_CMN_PORT <= DIO_u8PORTD && SEG_CMN_PIN <= DIO_u8PIN7

	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8LOW);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8HIGH);
	#else
	#error "SEG type has wrong selection"

	#endif

#elif SEG_CMN_PORT == NOT_CONNECTED || SEG_CMN_PIN == NOT_CONNECTED
	Local_enuErrorState = ES_OK;
#else
#error "wrong selection for common "
#endif

	return Local_enuErrorState;


}

ES_t Seven_segment_enuDisableCommon()
{

	ES_t Local_enuErrorState = ES_NOK;

#if SEG_CMN_PORT <= DIO_u8PORTD && SEG_CMN_PIN <= DIO_u8PIN7

	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8HIGH);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8LOW);
	#else
	#error "SEG type has wrong selection"

	#endif

#elif SEG_CMN_PORT == NOT_CONNECTED || SEG_CMN_PIN == NOT_CONNECTED
	Local_enuErrorState = ES_OK;
#else
#error "wrong selection for common "
#endif

	return Local_enuErrorState;

}

ES_t Seven_segment_enuEnableDot()
{

	ES_t Local_enuErrorState = ES_NOK;

#if SEG_DOT_PORT <= DIO_u8PORTD && SEG_DOT_PIN <= DIO_u8PIN7

	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8HIGH);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8LOW);
	#else
	#error "SEG type has wrong selection"

	#endif

#elif SEG_DOT_PORT == NOT_CONNECTED || SEG_DOT_PIN == NOT_CONNECTED
	Local_enuErrorState = ES_OK;
#else
#error "wrong selection for common "
#endif

	return Local_enuErrorState;


}

ES_t Seven_segment_enuDisableDot()
{

	ES_t Local_enuErrorState = ES_NOK;

#if SEG_DOT_PORT <= DIO_u8PORTD && SEG_DOT_PIN <= DIO_u8PIN7

	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8LOW);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinVal(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8HIGH);
	#else
	#error "SEG type has wrong selection"

	#endif

#elif SEG_DOT_PORT == NOT_CONNECTED || SEG_DOT_PIN == NOT_CONNECTED
	Local_enuErrorState = ES_OK;
#else
#error "wrong selection for common "
#endif

	return Local_enuErrorState;

}

ES_t Seven_segment_enuClearDisplay()
{
	ES_t Local_enuErrorState = ES_NOK;
	u16 Local_u32Check = 0;
#if SEG_TYPE == COMMON_CATHODE
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_APORT, SEG_APIN, DIO_u8LOW ))<<0 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_BPORT, SEG_BPIN, DIO_u8LOW ))<<3 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_CPORT, SEG_CPIN, DIO_u8LOW ))<<6 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_DPORT, SEG_DPIN, DIO_u8LOW ))<<9 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_EPORT, SEG_EPIN, DIO_u8LOW ))<<12);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_FPORT, SEG_FPIN, DIO_u8LOW ))<<15);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_GPORT, SEG_GPIN, DIO_u8LOW ))<<18);
#elif SEG_TYPE == COMMON_ANODE
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_APORT, SEG_APIN, (DIO_u8HIGH) ))<<0 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_BPORT, SEG_BPIN, (DIO_u8HIGH) ))<<3 );
		Local_u32Check |= ((DIO_enuSetPinVal(SEG_CPORT, SEG_CPIN, (DIO_u8HIGH) ))<<6 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_DPORT, SEG_DPIN, (DIO_u8HIGH) ))<<9 );
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_EPORT, SEG_EPIN, (DIO_u8HIGH) ))<<12);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_FPORT, SEG_FPIN, (DIO_u8HIGH) ))<<15);
		Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEG_GPORT, SEG_GPIN, (DIO_u8HIGH) ))<<18);
#else
#error "SEG type has wrong selection"

#endif


		u8 Local_u8Iterator;
		for(Local_u8Iterator = 0 ; Local_u8Iterator < 21 ; Local_u8Iterator += 3)
		{
			if( ( ( Local_u32Check>>Local_u8Iterator ) &7 ) != ES_OK )
			{
				return Local_enuErrorState;
			}
		}
		Local_enuErrorState = Seven_segment_enuDisableDot();
return  Local_enuErrorState;
}

