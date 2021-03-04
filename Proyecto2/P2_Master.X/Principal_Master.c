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
uint8_t LECTURA = 0;
uint8_t WRITE = 0xA6;       
uint8_t READ = 0xA7;
uint8_t P_CTL = 0X2D;       //Power-saving features control 
uint8_t D_FRMT = 0X31; //Data format control 
uint8_t DX0 = 0X32;         //X-Axis Data 0
uint8_t DX1 = 0X33;         //X-Axis Data 1
uint8_t DY0= 0X34;          //Y-Axis Data 0
uint8_t DY1 = 0X35;         //Y-Axis Data 1
uint8_t DZ0 = 0X36;         //Z-Axis Data 0
uint8_t DZ1 = 0X37;         //Z-Axis Data 1

//************************PROTOTIPO FUNCIONES*******************************

void SETUP (void);

void ACELEROMETRO_CONFIG(void);

void ACELEROMETRO_W(uint8_t num, uint8_t data);

unsigned short ACELEROMETRO_R(uint8_t num);

//**************************************************************************
void main(void) {
    SETUP();
    CONFIG_USART();
    I2C_Master_Init(100000);
    PORTA = 255;

//***LOOP****    
    while(1){
          
  }    
    
    return;
}

//******************************SUBRUTINAS***********************************

//Configuraciones Generales
void SETUP (void){

    OSCCONbits.IRCF2 = 1;       //8MHZ
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    
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
}


void ACELEROMETRO_CONFIG(void){
    
    ACELEROMETRO_W(D_FRMT, 0x0B);
    __delay_ms(5);
    
    ACELEROMETRO_W(P_CTL, 0x08);
    __delay_ms(5);
}

unsigned short ACELEROMETRO_R(uint8_t num){
    unsigned short LECTURA;
    
    I2C_Master_Start();
    I2C_Master_Write(WRITE);
    I2C_Master_Write(num);
    I2C_Master_Start();
    I2C_Master_Write(READ);
    LECTURA = I2C_Master_Read(0);
    I2C_Master_Stop();
    
    return LECTURA;
}
void ACELEROMETRO_W(uint8_t num, uint8_t data){
    
    I2C_Master_Start();
    I2C_Master_Write(WRITE);
    I2C_Master_Write(num);
    I2C_Master_Write(data);
    I2C_Master_Stop();
}


