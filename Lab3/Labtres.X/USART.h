/* 
 * File:   USART.h
 * Author: Gaby
 *
 * Created on 4 de febrero de 2021, 04:53 PM
 */


  
#ifndef __USART_H
#define	__USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


uint8_t usart_init(void);
char usartRC_Read();

void enviar (uint8_t valor1 ,uint8_t valor2 );



#endif