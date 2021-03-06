/* 
 * File:   I2C.h
 * Author: Gaby
 *
 * Created on 22 de febrero de 2021, 06:53 PM
 */

#ifndef I2C_H
#define	I2C_H

unsigned short I2C_Master_Read(unsigned short a);
void I2C_Master_Write(unsigned d);
void I2C_Master_RepeatedStart();
void I2C_Master_Start();
void I2C_Master_Wait();
void I2C_Master_Init(const unsigned long c);
void I2C_Master_Stop(void);

#endif	/* I2C_H */

