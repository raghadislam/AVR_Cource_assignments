/*
 * USART_int.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_USART_USART_INT_H_
#define ATMEGA32_CTOS_MCAL_USART_USART_INT_H_

/*
 * @brief Function to Initialize the USART
 * @return Error statues
 */
ES_t USART_enuInit();


/*
 * @brief Function to send the data sunchronously
 *
 * @param[In] Copy_u16Data data to put into the buffer
 *
 * @return Error statues
 */
ES_t USART_enuSendData(u8 Copy_u8Data);


/*
 * @brief Function to receive the data sunchronously
 *
 * @param[Out] Copy_u16Data data that has been read from the buffer
 *
 * @return Error statues
 */
ES_t USART_enuReceiveData(u8* Copy_pu8Data);


/*
 * @brief Function to send the string sunchronously
 *
 * @param[In] Copy_u16String the string to be sent to the buffer
 *
 * @return Error statues
 */
ES_t USART_enuSendStringSynch(u8* Copy_u16String);


/*
 * @brief Function to send the string Asunchronously
 *
 * @param[In] Copy_u16String the string to be sent to the buffer
 *
 * @param[In] NotificationFunc the notfication function to be excuted after the sending is done
 *
 * @return Error statues
 */
ES_t USART_enuSendStringAsynch(u8* Copy_u16String, void (*NotificationFunc)(void));


/*
 * @brief Function to Receive the string sunchronously
 *
 * @param[Out] Copy_u16String the string that has been read from the buffer
 *
 * @return Error statues
 */
ES_t USART_enuReceiveStringSynch(u8* Copy_u16String);


/*
 * @brief Function to receive the string Asunchronously
 *
 * @param[Out] Copy_u16String the string that has been read from the buffer
 *
 * @param[In] NotificationFunc the notfication function to be excuted after the sending is done
 *
 * @return Error statues
 */
ES_t USART_enuReceiveStringAsynch(u8* Copy_u16String, void (*NotificationFunc)(void));


#endif /* ATMEGA32_CTOS_MCAL_USART_USART_INT_H_ */
