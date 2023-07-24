/*
 * Seven_segment_int.h
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#ifndef SEVEN_SEGMENT_INT_H_
#define SEVEN_SEGMENT_INT_H_

ES_t Seven_segment_enuInit(void);

ES_t Seven_segment_enuDisplayNum(u8 Copy_u8Num);

ES_t Seven_segment_enuEnableCommon(void);

ES_t Seven_segment_enuDisableCommon(void);

ES_t Seven_segment_enuEnableDot(void);

ES_t Seven_segment_enuDisableDot(void);

ES_t Seven_segment_enuClearDisplay(void);




#endif /* SEVEN_SEGMENT_INT_H_ */
