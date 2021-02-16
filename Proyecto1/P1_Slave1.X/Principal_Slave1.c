/*
 * File:   Principal_Slave1.c
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:26 AM
 */
// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>
#include  "SPI_Slave.h"
#include  "ADC.h"
#define _XTAL_FREQ 8000000


//******************************Variables**************************************

uint8_t POTENCIOMETRO = 0; 
uint8_t rxByteMaster = 0;
uint8_t dummy;
//***************************Prototipo Funciones*******************************

void SETUP(void);

//*****************************Main Loop***************************************
void main(void) {
     
	SETUP();
    ADC_C(0);
    ADC_CONVCLK(1);
    dummy=SSPBUF; //limpiar rx 
    
    
	while(1)
	{ 
    POTENCIOMETRO = ADC_READ (0);
    ADC_CONTINUE();
    PORTB= POTENCIOMETRO;
    
    
    if (SSPSTATbits.BF == 0) {
        SSPBUF = POTENCIOMETRO;
    
    }
    
    if (SSPSTATbits.BF ) {
          //llego un byte del MASTER
          rxByteMaster = SSPBUF; //leemos byte del master
          PORTD = rxByteMaster;
          //volvemos a colocar una info en SSPBUF
          SSPBUF = POTENCIOMETRO;
          
      }
    
      }
  
    return;
}
//*******************************Subrutinas************************************    
    
//**Configuración general   
   void SETUP(void){
       
        PORTA = 0;
        PORTB = 0;
        PORTC = 0;
        PORTD = 0;
        PORTE = 0;
        
        TRISA = 0b00100001;  //0x20 = RA5 (SS) como entrada
        TRISB = 0;
        TRISD = 0;           //<-- para que esclavo muestre lo que recibe del master
        TRISC = 0b00011000;  // 0x18 = RC3 es CLk que recibe, RC4 es MISO, RC5 es MOSI
        TRISE = 0;           // Chip select entre slaves en 1 para no leer ninguno
        
        ANSEL = 0;
        ANSELbits.ANS0 = 1;
        ANSELH = 0;    
        
        SSPCONbits.SSPEN = 0;
        SSPSTAT = 0X00;
        SSPCON= 0X14;
        SSPCONbits.SSPEN = 1;
        
    }
    