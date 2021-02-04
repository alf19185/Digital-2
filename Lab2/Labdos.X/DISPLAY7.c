#include <xc.h>
#include <stdint.h>
#include "DISPLAY7.h"

uint8_t valorTMR0 = 131;
//int16 numerosDisplay[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};     

void config2Display(uint16_t FreqOsc){
    
     TRport = 0;
     PUERTOdisplay = 0;
     TRpin1 = 0;
     TRpin2 = 0;
     Tr1 = 0;
     Tr2 =0;
    
    //Frecuencias Oscilador 
    
    switch (FreqOsc){
        
        case 31:
            OSCCONbits.IRCF = 0b000;        //31khz
            break;
        case 125:
            OSCCONbits.IRCF = 0b001;        //125khz
            break;
        case 250:
            OSCCONbits.IRCF = 0b010;        //250khz
            break;    
        case 500:
            OSCCONbits.IRCF = 0b011;        //500khz
            break;  
        case 1000:
            OSCCONbits.IRCF = 0b100;        //1Mhz
            break;  
        case 2000:
            OSCCONbits.IRCF = 0b101;        //2Mhz
            break;
        case 4000:
            OSCCONbits.IRCF = 0b110;        //4Mhz
            OPTION_REGbits.PS = 0b110;      //prescale 1:128
            valorTMR0 = 177;                
            break;
        case 8000:
            OSCCONbits.IRCF = 0b111;        //8Mhz
            OPTION_REGbits.PS = 0b110;      //Prescale 1:128
            valorTMR0 = 98;
            break;
        default:
            OSCCONbits.IRCF = 0b110;        //4Mhz
    }
 
    OPTION_REGbits.T0CS = 0;                //Configuraciones para TIMR0
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    TMR0 = valorTMR0;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;    
}


void cambioDisplay(uint8_t valUni, uint8_t valDec, uint8_t bandera){
    TMR0 = valorTMR0;
    
    //Cambio de displays dependiendo de la bandera 0 o 255
    
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
