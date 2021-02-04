/* 
 * File:   Display7.h
 * Author: Gaby
*/

#ifndef DISPLAY7_H
#define	DISPLAY7_H

#include <xc.h> 
#include <stdint.h>

// Puerto D para display y C0 y C2 para multiplexar
#define TRport        TRISD             
#define PUERTOdisplay PORTD
#define Tr1           PORTCbits.RC2
#define Tr2           PORTCbits.RC0
#define TRpin1        TRISCbits.TRISC2
#define TRpin2        TRISCbits.TRISC0

//Ánodo 
 int numerosDisplay[16] = { 0x88, 0xEB, 0x4C, 0x49, 0x2B, 0x19, 0x18, 0xCB, 0x8,0xB, 0x2, 0x30, 0x94, 0x60, 0x14, 0x16 }; 

void config2Display(uint16_t FreqOsc);

void cambioDisplay(uint8_t valDec, uint8_t valUni, uint8_t bandera);

#endif
