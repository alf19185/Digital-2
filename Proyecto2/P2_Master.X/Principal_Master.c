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
uint8_t BANDERA_T = 0;
uint8_t WRITE = 0xA6;      //Para escribir en sensor
uint8_t READ = 0xA7;        //Para leer en sensor
uint8_t P_CTL = 0X2D;       //Power-saving features control 
uint8_t D_FRMT = 0X31;      //Data format control 
uint8_t DX0 = 0X32;         //Direccion X-Axis Data 0 
uint8_t DX1 = 0X33;         //Direccion X-Axis Data 1
uint8_t DY0= 0X34;          //Direccion Y-Axis Data 0
uint8_t DY1 = 0X35;         //Direccion Y-Axis Data 1
uint8_t DZ0 = 0X36;         //Direccion Z-Axis Data 0
uint8_t DZ1 = 0X37;         //Direccion Z-Axis Data 1
uint8_t XL = 0; 
uint8_t XH = 0; 
uint8_t YL = 0; 
uint8_t YH = 0; 
uint8_t ZL = 0; 
uint8_t ZH = 0; 
uint8_t X = 0; 
uint8_t Z = 0; 
uint8_t Y = 0; 
uint8_t X_units = 0;
uint8_t X_decs = 0;
uint8_t X_cents = 0;
uint8_t Y_units = 0;
uint8_t Y_decs = 0;
uint8_t Y_cents = 0;
uint8_t Z_units = 0;
uint8_t Z_decs = 0;
uint8_t Z_cents = 0;

//************************PROTOTIPO FUNCIONES*******************************

void SETUP (void);

void ACELEROMETRO_CONFIG(void);

void ACELEROMETRO_W(uint8_t num, uint8_t data);

unsigned short ACELEROMETRO_R(uint8_t num);

void LEER_VALORES (void);

uint8_t TX (void);

void EJEX_TO_CHARS(void);

void EJEY_TO_CHARS(void);

void EJEZ_TO_CHARS(void);

float ACELEROMETRO_AX(void);
//****************************INTERRUPCIONES*********************************
void __interrupt() isr(void) { 
 di(); 
 
    if(PIR1bits.TXIF == 1){                      //Interrupción para transmitir
        PIR1bits.TXIF = 0;
        TXREG = TX();  
    }
 
  ei();
}
//****************************MAIN*******************************************

void main(void) {
    SETUP();
    CONFIG_USART();
    
    I2C_Master_Init(100000);
    ACELEROMETRO_CONFIG();
    PORTA = 255;

//***LOOP****    
    while(1){
        
       LEER_VALORES();               
  }    
    
    return;
}

//******************************SUBRUTINAS***********************************

//Configuraciones Generales
void SETUP (void){

    OSCCONbits.IRCF2 = 1;       //8MHZ
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    
    PORTA = 0;                  //LEDS
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
    
    INTCONbits.GIE = 1;     //Interrupcion TX 
    INTCONbits.PEIE = 1;
    PIE1bits.TXIE = 1; 
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

uint8_t TX(void){
               
    switch(BANDERA_T){
  
        case 0:
        //    EJEX_TO_CHARS(); 
            BANDERA_T++;
            return "1";
         //   return X_cents + 48;
            break;
        case 1:
            BANDERA_T++;
        //    return X_decs + 48;
         return ",";    
            break;  
    /*    case 2:
            BANDERA_T++;
            return X_units + 48;
            break;    
        case 3:
            BANDERA_T++;
            return ',';
            break;
        case 4:
            EJEY_TO_CHARS();
            BANDERA_T++;
            return Y_cents + 48;
            break;
        case 5:
            BANDERA_T++;
            return Y_decs + 48;
            break;  
        case 6:
            BANDERA_T++;
            return Y_units + 48;
            break;
         case 7:
            BANDERA_T++;
            return ',';
            break;
        case 8:
            EJEZ_TO_CHARS();
            BANDERA_T++;
            return Z_cents + 48;
            break;  
        case 9:
            BANDERA_T++;
            return Z_decs + 48;
            break;
        case 10:
            BANDERA_T++;
            return Z_units + 48;
            break;  
        case 11:
            BANDERA_T = 0;
            return '\r';
            break; */    
    }
}

void LEER_VALORES (void){
   
    XL =  ACELEROMETRO_R(DX0);
    XH =  ACELEROMETRO_R(DX1);
    X = ((YH<<8) | YL) ;
    
    YL =  ACELEROMETRO_R(DY0);
    YH =  ACELEROMETRO_R(DY1);
    Y = ((YH<<8) | YL) ;
    
    ZL =  ACELEROMETRO_R(DZ0);
    ZH =  ACELEROMETRO_R(DZ1);
    Z = ((ZH<<8) | ZL) ;
}

void EJEX_TO_CHARS (void){
    
    uint8_t valor = X;
    X_units = valor %10 ;
    valor = valor/10;
    X_decs = valor %10 ;
    X_cents = valor /10 ; 
    
    }

void EJEY_TO_CHARS (void){
    
    uint8_t valor = X;
    Y_units = valor %10 ;
    valor = valor/10;
    Y_decs = valor %10 ;
    Y_cents = valor /10 ; 
    
    }

void EJEZ_TO_CHARS (void){
    
    uint8_t valor = X;
    Z_units = valor %10 ;
    valor = valor/10;
    Z_decs = valor %10 ;
    Z_cents = valor /10 ; 
    
    }

