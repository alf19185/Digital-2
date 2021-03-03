/*
 * File:   Principal_Slave3.c
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:31 AM
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

uint8_t TEMPERATURA_0 = 0;
uint8_t TEMPERATURA_1 = 0;
uint8_t TEMPERATURA = 0;
uint8_t TEMPORAL = 0;
uint8_t ENVIAR = 0;
uint8_t rxByteMaster =0;
uint16_t TEMP = 0;
uint16_t TEMPH= 0;
uint16_t TEMPL= 0;
float TEMP_R;


//***************************Prototipo Funciones*******************************

void SETUP(void);
void MAP(void);

//*****************************Main Loop***************************************
void main(void) {
     
	SETUP();
	__delay_ms(10);
    ADC_C(0);
    ADC_CONVCLK(1);
    
	while(1)
	{
    TEMPERATURA_0 = ADC_READ (0);
    TEMPERATURA_1 = ADC_READ (1);
    TEMPH = TEMPERATURA_0;
    TEMPH = TEMPH << 2;
    TEMPL = TEMPERATURA_1;
    TEMPL = TEMPL >> 6;
              
    TEMP = TEMPH + TEMPL;
    
    TEMP_R = TEMP*140.0/286.0;
    
   TEMPERATURA = (uint8_t) TEMP_R;
   
 
   //PORTD = TEMPERATURA;
   // MAP();
    ADC_CONTINUE();
    
    if(TEMPERATURA < 25) {  
     //Menor a 25, VERDE
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB2 = 1;       
        }
    else if (TEMPERATURA >= 25 && TEMPERATURA <=36 ){    
    //ENTRE 25 Y 36, AMARILLO
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 1;
        PORTBbits.RB2 = 0;
        }
    
    else if (TEMPERATURA > 36){
    //MAYOR 36, ROJO    
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 0;
        PORTBbits.RB2 = 0;
        }
 
      if (SSPSTATbits.BF == 0) {
        SSPBUF = TEMPERATURA;
    
    }
    
    if (SSPSTATbits.BF ) {
          //llego un byte del MASTER
          rxByteMaster = SSPBUF; //leemos byte del master
         // PORTD = rxByteMaster;
          //volvemos a colocar una info en SSPBUF
          SSPBUF = TEMPERATURA;
          
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
        
        TRISA = 0b00100001;
        TRISB = 0;
        TRISD = 0;
        TRISC = 0b00011000;  // RC3 es CLk que recibe, RC4 es MISO, RC5 es MOSI
        TRISE = 0;           // Chip select entre slaves en 1 para no leer ninguno 
    
        
        ANSEL = 0;
        ANSELbits.ANS0 = 1;
        ANSELH = 0;   
        
        SSPCONbits.SSPEN = 0;
        SSPSTAT = 0X00;
        SSPCON= 0X14;
        SSPCONbits.SSPEN = 1;
      
    }
//**Mapeo de la temperatura a 255
void MAP(void){

    if(TEMPERATURA < 0){
        ENVIAR=0;
        PORTD = ENVIAR;
    } 
    if (TEMPERATURA >= 0 ){
        ENVIAR = ((TEMPERATURA *500)/1024);      //Por cada 10mV hay un C° 
        PORTD = ENVIAR;
    }
    
    
    
}   