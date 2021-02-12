/* 
 * File:   SPI_Master.h
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:23 AM
 */

#ifndef SPI_MASTER_H
#define	SPI_MASTER_H

unsigned char data;

void CONFIG_SPI_MASTER(void);

void CONFIG_SPI_SLAVE(void);

void READ_SPI (void);

void WAIT_SPI (void);

void WRITE_SPI(char data);

#endif	/* SPI_MASTER_H */

