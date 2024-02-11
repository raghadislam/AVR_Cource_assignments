/*
 * GIE_prog.c
 *
 *  Created on: Sep 7, 2023
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"

#include "GIE_priv.h"


/**
 * @brief: void function to enable the global interrupt
 */
void GIE_viodEnable(void){

	Set_bit(SREG,SREG_I);
}


/**
 * @brief: void function to disable the global interrupt
 */
void GIE_viodDisable(void){

	Clr_bit(SREG,SREG_I);

}
