#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
#include "USART.h"

void CONFIG_USART (void){
    
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    
    TXSTAbits.TX9 = 0;      
    TXSTAbits.SYNC = 0;     //Formula FOSC/[64 (n+1)]
    TXSTAbits.BRGH = 0;
    BAUDCTLbits.BRG16 = 0;
    SPBRG = 51;             //2400
    //SPBRG = 12;             //9600  
    SPBRGH = 0;             
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
}

uint8_t ASCII(uint8_t aconvertir){
    switch(aconvertir){
        case 0:
            return 0x30;
            break;
        case 1:
            return 0x31;
            break;
        case 2:
            return 0x32;
            break;
        case 3:
            return 0x33;
            break;
        case 4:
            return 0x34;
            break;
        case 5:
            return 0x35;
            break;
        case 6:
            return 0x36;
            break;
        case 7:
            return 0x37;
            break;
        case 8:
            return 0x38;
            break;
        case 9:
            return 0x39;
            break;
        case 10:
            return 0x41;
            break;
        case 11:
            return 0x42;
            break;
        case 12:
            return 0x43;
            break;
        case 13:
            return 0x44;
            break;
        case 14:
            return 0x45;
            break;
        case 15:
            return 0x46;
            break;
    }
}
