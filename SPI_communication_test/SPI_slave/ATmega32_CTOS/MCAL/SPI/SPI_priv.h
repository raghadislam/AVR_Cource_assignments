/*
 * Spi_priv.h
 *
 *  Created on: Feb 6, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_SPI_SPI_PRIV_H_
#define ATMEGA32_CTOS_MCAL_SPI_SPI_PRIV_H_

/* SPI Control Register */
#define SPCR		*((volatile u8*)0x2D)

/* SPI Clock Rate Select Bit 0 */
#define SPCR_SPR0	0

/* SPI Clock Rate Select Bit 1 */
#define SPCR_SPR1	1

/* Clock Phase Bit */
#define SPCR_CPHA	2

/*  Clock Polarity Bit */
#define SPCR_CPOL	3

/*  Master/Slave Select Bit */
#define SPCR_MSTR	4

/* Data Order Bit */
#define SPCR_DORD	5

/*  SPI Enable Bit*/
#define SPCR_SPE	6

/* SPI Interrupt Enable Bit */
#define SPCR_SPIE	7



/* SPI pins data direction register */
#define SPI_DDR			*(( volatile u8*)0x37)

/* SPI slave select pin */
#define SPI_SS			4

/* SPI master output/ slave input pin */
#define SPI_MOSI		5

/* SPI master input/slave output pin */
#define SPI_MISO		6

/* SPI serial clock pin */
#define SPI_SCK			7


/* SPI Status Register */
#define SPSR			*((volatile u8*)0x2E)

/*  Double SPI Speed Bit */
#define SPSR_SPI2X		0

/*  Write COLlision Flag Bit */
#define SPSR_WCOL		6

/* SPI Interrupt Flag Bit */
#define SPSR_SPIF		7


/* SPI Data Register */
#define SPDR			*((volatile u8*)0x2F)



/*=========================== private macros ===========================*/
#define SPI_INPUT			99
#define SPI_OUTPUT			88

#define SPI_LSB_FIRST		76
#define SPI_MSB_FIRST		59

#define SPI_LOW				23
#define SPI_HIGH			22

#define SPI_SAMPLE_FIRST    11
#define SPI_SETUP_FIRST     10

#define SPI_DIVISION_BY_4	1
#define SPI_DIVISION_BY_16	2
#define SPI_DIVISION_BY_64	3
#define SPI_DIVISION_BY_128	4

#define SPI_DIVISION_BY_2	5
#define SPI_DIVISION_BY_8	6
#define SPI_DIVISION_BY_32	7




#define SPI_ENABLED		7
#define	SPI_DISABLED	8

#define SPI_MASTER		11
#define	SPI_SLAVE		22


#endif /* ATMEGA32_CTOS_MCAL_SPI_SPI_PRIV_H_ */
