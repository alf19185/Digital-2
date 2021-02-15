/* 
 * File:   SPI_Master.h
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:23 AM
 */

#ifndef SPI_MASTER_H
#define	SPI_MASTER_H
#define _XTAL_FREQ 8000000

uint8_t  data;

void CONFIG_SPI_MASTER(void);

void CONFIG_SPI_SLAVE(void);

uint8_t READ_SPI (uint8_t);

void WAIT_SPI (void);

void WRITE_SPI( uint8_t data );

uint8_t CHECK_DATA(void);

#endif	/* SPI_MASTER_H */
