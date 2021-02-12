/*
 * File:   Principal_Master.c
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:24 AM
 */


// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <pic16f887.h>
#include <xc.h>
#include "SPI_Master.h"

//******************************Variables**************************************
unsigned temp; 
//***************************Prototipo Funciones*******************************

void SETUP(void);


//*****************************Main Loop***************************************
void main(void) {
     
	SETUP();
	CONFIG_SPI_MASTER();
    
	while(1)
	{
		while(!SSPIF);
		temp=SSPBUF;
		PORTD=temp;
		//SSPBUF = 0x14;
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
        
        TRISA= 0;
        TRISC = 0b10010100;  // RC3 es CLk sale a slaves, RC4 es MISO, RC5 es MOSI
        TRISE = 4;           // Chip select entre slaves en 1 para no leer ninguno
        
        ANSEL = 0;
        ANSELH = 0;      
        
    }
    
    
    

