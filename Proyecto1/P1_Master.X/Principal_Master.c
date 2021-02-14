/*
 * File:   Principal_Master.c
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:24 AM
 */
// CONFIG1
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
#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdint.h>
#include "SPI_Master.h"

//******************************Variables**************************************
uint8_t temp; 
uint8_t Esclavo1;
//***************************Prototipo Funciones*******************************

void SETUP(void);


//*****************************Main Loop***************************************
void main(void) {
     
	SETUP();
	CONFIG_SPI_MASTER();
     __delay_ms(10);
     
	while(1)
	{
        
       PORTEbits.RE0 =0;
       Esclavo1 = READ_SPI ();
       PORTD = Esclavo1  ;   
       PORTEbits.RE0 =1; 
       PORTBbits.RB1 = !PORTBbits.RB1; 
        __delay_ms(100);
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
        
        TRISA = 0;
        TRISD = 0;
        TRISB = 0;
        TRISC = 0b00010000;  // RC3 es CLk sale a slaves, RC4 es MISO, RC5 es MOSI
        TRISE = 0;           // Chip select entre slaves en 1 para no leer ninguno
        
        ANSEL = 0;
        ANSELH = 0;      
        
    }
    
    
    

