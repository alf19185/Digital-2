

#include <xc.h>
#include <stdint.h>
#include "ADC.h"

#define _XTAL_FREQ 4000000


void ADConfig(uint8_t oscFreq, uint8_t canal, unsigned char justificado){
    switch(oscFreq){
        case 1:
            ADCON0bits.ADCS = 0b00;  // FOSC/2
            break;
        case 4:
            ADCON0bits.ADCS = 0b01;  // FOSC/8
            break;
        case 8:
            ADCON0bits.ADCS = 0b10;  // FOSC/32
            break;
        case 20:
            ADCON0bits.ADCS = 0b11;    // FRC
            break;
        default:
            ADCON0bits.ADCS = 0b01;  //Caso 1
    }
    switch(justificado){
        case 'H':
            ADCON1bits.ADFM = 0;    // Izquierda
            break;
        case 'L':
            ADCON1bits.ADFM = 1;    // Derecha
            break;
        default:
            ADCON1bits.ADFM = 0;    //Caso H
    }
    switch (canal){
        case 0:
            TRISAbits.TRISA0 = 1;   //Canal 0
            ANSELbits.ANS0 = 1;
            ADCON0bits.CHS = 0;
            break;
        case 1:
            TRISAbits.TRISA1 = 1;   //Canal 1
            ANSELbits.ANS1 = 1;
            ADCON0bits.CHS = 1;
            break;    
        case 2:
            TRISAbits.TRISA2 = 1;    //Canal 2
            ANSELbits.ANS2 = 1;
            ADCON0bits.CHS = 2;
            break;    
        case 3:
            TRISAbits.TRISA3 = 1;      //Canal 3
            ANSELbits.ANS3 = 1;
            ADCON0bits.CHS = 3;
            break;
        case 4:
            TRISAbits.TRISA5 = 1;      //Canal 4
            ANSELbits.ANS4 = 1;
            ADCON0bits.CHS = 3;
            break;
        case 5:
            TRISEbits.TRISE0 = 1;       //Canal 5
            ANSELbits.ANS5 = 1;
            ADCON0bits.CHS = 5;
            break;
        case 6:
            TRISEbits.TRISE1 = 1;       //Canal 6
            ANSELbits.ANS6 = 1;
            ADCON0bits.CHS = 6;
            break;
        case 7:
            TRISEbits.TRISE2 = 1;       //Canal 7
            ANSELbits.ANS7 = 1;
            ADCON0bits.CHS = 7;
            break;       
                                        // Faltan los de ANSELH         
    }
    
    ADCON0bits.ADON = 1;                //Configuraciones para funcione ADC
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    INTCONbits.PEIE = 1;
    __delay_ms(30);
    ADCON0bits.GO_nDONE = 1;
}

uint8_t AnalogRead_8(unsigned char just){       
    uint8_t conversion = 0;
    switch (just){
        case 'H':
            conversion = ADRESH;
            break;
        case 'L':
            conversion = ADRESL;
            break;
        default:
            conversion = ADRESH;
    }
    return (conversion);
}

void ADCinit(){                      //Configuraciones para continuar ADC
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    __delay_ms(20);
    ADCON0bits.GO_nDONE = 1;
    return;
}
