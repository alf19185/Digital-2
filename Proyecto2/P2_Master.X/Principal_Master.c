/*
 * File:   Principal_Master.c
 * Author: Gaby
 *
 * Created on 22 de febrero de 2021, 06:35 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <pic16f887.h>
#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdint.h>
#include "I2C.h"
#include "USART.h"

//**************************VARIABLES**************************************

void SETUP (void);

//************************PROTOTIPO FUNCIONES*******************************

void main(void) {
    SETUP();
   // CONFIG_USART();
   // I2C_Master_Init(100000);
    PORTA = 255;

//***LOOP****    
    while(1){
        
   
   /*     
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(PORTB);
        I2C_Master_Stop();
        __delay_ms(200);
       
        I2C_Master_Start();
       I2C_Master_Write(0x51);
        PORTD = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        PORTB++;   
  }    
    */
    return;
}
}

//******************************SUBRUTINAS***********************************

void SETUP (void){

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    TRISA = 0;        
    TRISB = 0;
    TRISC = 0b00010000;     // 0x10 RC3 es CLk sale, RC4 es SDA 
    TRISD = 0;
    TRISE = 0;
    
    TRISCbits.TRISC6 = 0;   //TX
    TRISCbits.TRISC7 = 1;   //RX
    
    ANSEL = 0;
    ANSELH = 0;
    
    OSCCONbits.IRCF2 = 1;       //8MHZ
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
}

