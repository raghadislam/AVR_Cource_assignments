/*
 * main.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Raghad Islam
 */
#include "STDTypes.h"
#include "errorState.h"
#include <util/delay.h>

#include "DIO_int.h"

#include"Seven_segment_config.h"
#include "Seven_segment_int.h"

extern SEG_t SEVSEG_AstrConfig[NUM_OF_SEG];


int main()
{
	/* initialize 7 seg */

	Seven_segment_enuInit(SEVSEG_AstrConfig);
	Seven_segment_enuDisableCommon(0);
	Seven_segment_enuDisableCommon(1);

	while(1)
	{
		/* disable seg 1 */
		Seven_segment_enuDisableCommon(0);

		/* put number */
		Seven_segment_enuDisplayNum(0,3);

		/* enable seg 2 */
		Seven_segment_enuEnableCommon(1);

		_delay_ms(15);

		/* disable seg 2*/
		Seven_segment_enuDisableCommon(1);


		/* put number */
		Seven_segment_enuDisplayNum(1,7);

		/* enable seg 1 */
		Seven_segment_enuEnableCommon(0);

		_delay_ms(15);


	}
	return 0;
}
