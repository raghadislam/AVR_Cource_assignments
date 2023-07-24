/*
 * Keypad_priv.h
 *
 *  Created on: Jul 24, 2023
 *      Author: Raghad
 */

#ifndef KEYPAD_PRIV_H_
#define KEYPAD_PRIV_H_



#define CONC_HELP1(i)	 KPD_COL##i##_PORT
#define CONC1(i)		 CONC_HELP1(i)

#define CONC_HELP2(i)	 KPD_COL##i##_PIN
#define CONC2(i)		 CONC_HELP2(i)



#define CONC_HELP3(i)	 KPD_ROW##i##_PORT
#define CONC3(i) 		 CONC_HELP3(i)

#define CONC_HELP4(i) 	 KPD_ROW##i##_PIN
#define CONC4(i)		 CONC_HELP4(i)


#endif /* KEYPAD_PRIV_H_ */
