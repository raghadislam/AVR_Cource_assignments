/*
 * SPI_config.h
 *
 *  Created on: Feb 6, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_SPI_SPI_CONFIG_H_
#define ATMEGA32_CTOS_MCAL_SPI_SPI_CONFIG_H_

/*
 * choose the SPI initial state
 * options:	1- SPI_ENABLED
 * 			2- SPI_DISABLED
 */
#define SPI_STATE		SPI_ENABLED


/*
 * choose the SPI initial mode
 * options:	1- SPI_MASTER
 * 			2- SPI_SLAVE
 */
#define SPI_MODE		SPI_SLAVE


/*
 * choose the SPI master's ss pin mode
 * options:	1- SPI_INPUT
 * 			2- SPI_OUTPUT
 */
#define SPI_MASTER_SS	SPI_INPUT


/*
 * choose the SPI data order
 * options:	1- SPI_LSB_FIRST (the LSB of the data word is transmitted first)
 * 			2- SPI_MSB_FIRST (the MSB of the data word is transmitted first)
 */
#define SPI_DATA_ORDER		SPI_LSB_FIRST


/*
 * choose the SPI clock polarity
 * options:	1- SPI_LOW  (SCK is low when idle, Leading Edge is rising edge )
 * 			2- SPI_HIGH (SCK is HIGH when idle, Leading Edge is falling edge)
 */
#define SPI_CLK_POLARITY	SPI_LOW


/*
 * choose the SPI  clock phase
 * options:	1- SPI_SAMPLE_FIRST	(data is sampled on the leading edge of SCK)
 * 			2- SPI_SETUP_FIRST	(data is sampled on the trailing edge of SCK)
 */
#define SPI_CLK_PHASE		SPI_SAMPLE_FIRST

/*
 * choose the SPI  clock rate
 * options:	1- SPI_DIVISION_BY_2
 * 			2- SPI_DIVISION_BY_4
 * 			3- SPI_DIVISION_BY_8
 * 			4- SPI_DIVISION_BY_16
 * 			5- SPI_DIVISION_BY_32
 * 			6- SPI_DIVISION_BY_64
 * 			7- SPI_DIVISION_BY_128
 */
#define SPI_CLK_RATE		SPI_DIVISION_BY_128


#if (SPI_CLK_RATE == SPI_DIVISION_BY_4)
#define SPI_SPR_BITS 0

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_16)
#define SPI_SPR_BITS 1

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_64)
#define SPI_SPR_BITS 2

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_128)
#define SPI_SPR_BITS 3

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_2)
#define SPI_SPR_BITS 0

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_8)
#define SPI_SPR_BITS 1

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_32)
#define SPI_SPR_BITS 2

#endif

/* Macro to define the timeout which determines the fault time in the SPI upon transmitting or receiving */
#define SPI_TIMEOUT 80000ULL
#endif /* ATMEGA32_CTOS_MCAL_SPI_SPI_CONFIG_H_ */
