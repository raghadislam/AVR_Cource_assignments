/*
 * SPI_int.h
 *
 *  Created on: Feb 6, 2024
 *      Author: DeLL
 */

#ifndef ATMEGA32_CTOS_MCAL_SPI_SPI_INT_H_
#define ATMEGA32_CTOS_MCAL_SPI_SPI_INT_H_

/**
 * @brief function to initialize the SPI.
 */
ES_t SPI_enuInit();


/**
 * @brief function to transmit and receive one byte.
 *
 * @param[in] Copy_u8SentData: data to be transmitted
 *
 * @param[out] Copy_pu8ReceivedData: data to be received
 *
 * @return the error statues.
 */
ES_t SPI_enuTranceiveByte(u8 Copy_u8SentData, u8* Copy_pu8ReceivedData);


/**
 * @brief function to transmit and receive one byte.
 *
 * @param[in] Copy_Pu8SentData: string to be transmitted
 *
 * @param[out] Copy_pu8ReceivedData: string to be received
 *
 * @param[in] CallBack: the callback function
 *
 * @return the error statues.
 */
ES_t SPI_u8TranceiveStringAsynch(u8 *Copy_Pu8SentData, u8 *Copy_pu8ReceivedData, void (*CallBack)(void));

#endif /* ATMEGA32_CTOS_MCAL_SPI_SPI_INT_H_ */
