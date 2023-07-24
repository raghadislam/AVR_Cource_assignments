/*
 * Switch_config.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Raghad Islam
 */

#include "STDTypes.h"
#include "DIO_priv.h"
#include "errorState.h"
#include "Switch_config.h"
#include "DIO_int.h"

SW_t Switch_ArrStrSwitchState[3] = {

		{DIO_u8PORTC, DIO_u8PIN1, DIO_u8PULL_UP},
		{DIO_u8PORTC, DIO_u8PIN0, DIO_u8PULL_UP  },
		{DIO_u8PORTC, DIO_u8PIN2, DIO_u8PULL_UP}
};
