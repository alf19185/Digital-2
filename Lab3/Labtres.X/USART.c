
#include <xc.h>
#include "USART.h"
#define _XTAL_FREQ 4000000

 uint16_t str[3];
 uint8_t contador = 0;
 char valorSerial = 'E';
 
uint8_t usart_init(){
    
    TXSTAbits.TX9 = 0;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 0;
    SPBRG = 25;
    SPBRGH = 0;
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;  
}


char usartRC_Read(){
    
    uint8_t lectura = RCREG;
    __delay_ms(5);
    lectura = RCREG;
    
    switch (lectura){
                case 43:
                    contador ++;
                   // valorSerial = 0;
                    break;
                case 45:
                    contador --;
                    //valorSerial = 0;
                    break;
                default:
                    contador = contador;
            }
    }

      
void enviar (uint8_t valor1, uint8_t valor2){
    
     valor1 = valor1 - 30;
     TXREG= valor1;
     while(TXSTAbits.TRMT == 0){
            __delay_us(500);
        }
     
     TXREG = ','; 
     while(TXSTAbits.TRMT == 0){
            __delay_us(500);
        }
     
     valor2 = valor2 - 30;
     TXREG= valor2;
     while(TXSTAbits.TRMT == 0){
            __delay_us(500);
        }      
     TXREG = '/n';
     while(TXSTAbits.TRMT == 0){
            __delay_us(500);
        }
        
}

