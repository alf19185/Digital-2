/*
 * File:   Principal2.c
 * Author: Gaby
 *
 * Created on 28 de enero de 2021, 04:41 PM
 */


#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>

#include "ADC.h"

void config_PUERTOS(void);
void press_Subir(void);
void press_Bajar(void);
uint8_t banderaBoton = 0;
uint8_t banderaUP = 0;
uint8_t banderaDO = 0;
uint8_t banderaTMR0 = 0;
uint8_t banderaADC = 0;
uint8_t valorDisplay_Dec;
uint8_t valorDisplay_Uni;


void __interrupt() ISR(void){
    
    if (PIR1bits.ADIF && PIE1bits.ADIE){
        PIE1bits.ADIE = 0;
        banderaADC = 1;
    }
    
    if (INTCONbits.RBIF == 1 && INTCONbits.RBIE == 1){   //atencion IOCB
        INTCONbits.RBIF = 0;
        if (banderaBoton == 0){
            banderaBoton = 1;
            INTCONbits.RBIE = 0;
        }
    }
    
    if (INTCONbits.T0IF == 1 && INTCONbits.T0IE == 1){
        banderaTMR0 = ~banderaTMR0;
        cambioDisplay(valorDisplay_Uni, valorDisplay_Dec, banderaTMR0);
        INTCONbits.T0IF = 0;
    }
      return;  
    }



void main(void) {
    return;
}

void config_PUERTOS(void){
    //PUERTOS
    TRISD = 255;
    TRISC = 255;
    TRISA = 0;
    TRISB = 0b00000101;
    TRISE = 0;
    PORTE = 0;
    PORTA = 0; 
    PORTB = 0; 
    PORTC = 0; 
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0; 
    WPUB = 0b00000101;
    OPTION_REGbits.nRBPU = 0;
    
    //Interrupciones
    IOCB = 0b00000101;;  //RB0 y RB2 tiene interrupcion
    INTCONbits.RBIE = 1;
    return;
}