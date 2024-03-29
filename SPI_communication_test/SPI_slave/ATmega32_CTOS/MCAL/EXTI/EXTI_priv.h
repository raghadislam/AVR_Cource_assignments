/*
 * EXTI_priv.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Raghad Islam
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

/*======================= private macros ======================= */

/* external interrupt pins */

#define EXTI_INT0 		 33
#define EXTI_INT1 		 34
#define EXTI_INT2 		 35

/* external interrupt sense control levels */

#define FALLING_EDGE	 66
#define RISING_EDGE 	 36
#define ON_CHANGE		 56
#define LOW_LEVEL 		 86

/* external interrupt initial state */

#define TIMER_ENABLED			 9
#define DISABLED		 7

/* general interrupt control register */

#define GICR 			 *((volatile u8*)0x5B)
#define GICR_INT0   	 6
#define GICR_INT1		 7
#define GICR_INT2    	 5

/* general interrupt flag register */

#define GIFR 			 *((volatile u8*)0x5A)

/* MCU control register */

#define MCUCR 			 *((volatile u8*)0x55)
#define MCUCR_ISC00		 0
#define MCUCR_ISC01		 1
#define MCUCR_ISC10		 2
#define MCUCR_ISC11		 3


/* MCU control and statues register */

#define MCUCSR 			 *((volatile u8*)0x54)
#define MCUCSR_ISC2		 6


#endif /* EXTI_PRIV_H_ */
