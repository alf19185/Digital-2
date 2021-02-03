/* 
 * File:   Display7.h
 * Author: Gaby
*/

#ifndef DISPLAY7_H
#define	DISPLAY7_H

#include <xc.h> 
#include <stdint.h>

// se debe cambiar esto de acuerdo a lo que se tenga
#define TRport        TRISD             
#define PUERTOdisplay PORTD
#define Tr1           PORTCbits.RC2
#define Tr2           PORTCbits.RC0
#define TRpin1        TRISCbits.TRISC2
#define TRpin2        TRISCbits.TRISC0

uint8_t numerosDisplay[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void config2Display(uint16_t FreqOsc);

void cambioDisplay(uint8_t valDec, uint8_t valUni, uint8_t bandera);

#endif