#include <xc.h>
#include <stdint.h>
#include "DISPLAY7.h"

uint8_t valorTMR0 = 131;
void config2Display(uint16_t FreqOsc){
    TRport = 0;
    PUERTOdisplay = 0;
    TRpin1 = 0;
    TRpin2 = 0;
    Tr1 = 0;
    Tr2 =0;
    
    //----FreqOsc---
    
    switch (FreqOsc){
        
        case 31:
            OSCCONbits.IRCF = 0b000;
            break;
        case 125:
            OSCCONbits.IRCF = 0b001;
            break;
        case 250:
            OSCCONbits.IRCF = 0b010;
            break;    
        case 500:
            OSCCONbits.IRCF = 0b011;
            break;  
        case 1000:
            OSCCONbits.IRCF = 0b100;
            break;  
        case 2000:
            OSCCONbits.IRCF = 0b101;
            break;
        case 4000:
            OSCCONbits.IRCF = 0b110;
            OPTION_REGbits.PS = 0b110;  //prescale 1:128
            valorTMR0 = 177;
            break;
        case 8000:
            OSCCONbits.IRCF = 0b111;
            OPTION_REGbits.PS = 0b110;
            valorTMR0 = 98;
            break;
        default:
            OSCCONbits.IRCF = 0b110;
    }
    //---------------Config interrupcion TMR0-------------
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    TMR0 = valorTMR0;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    
    
}

void cambioDisplay(uint8_t valUni, uint8_t valDec, uint8_t bandera){
    TMR0 = valorTMR0;
    switch (bandera){
        case 0:
            Tr2 = 0;
            PUERTOdisplay = numerosDisplay[valUni];
            Tr1 = 1;
            break;
        case 255:
            Tr1 = 0;
            PUERTOdisplay = numerosDisplay[valDec];
            Tr2 = 1;
            break;
        default:
            PUERTOdisplay = PUERTOdisplay;
    }
}
