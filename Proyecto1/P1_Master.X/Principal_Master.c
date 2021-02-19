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
#include "LCD.h"
#include "USART.h"

//******************************Variables**************************************
uint8_t temp; 
uint8_t POTENCIOMETRO;
uint8_t contador =0;
uint8_t CONT;
uint8_t TEMPERATURA;
const char* POT_r ;
const char* CONT_r ;
const char* TEMP_r ;


//***************************Prototipo Funciones*******************************

void SETUP(void);
void LEER_S1 (void);
void LEER_S2 (void);
void LEER_S3 (void);
void LCD(void);
uint8_t TRANSMITIR_INFO(void);


//****************************Interrupciones**********************************

void __interrupt() isr(void) { 
 di(); 
 
    if(PIR1bits.TXIF == 1){                      //Interrupción para transmitir
        TXREG = TRANSMITIR_INFO();
        PIE1bits.TXIE = 0;
    }
 
  ei();
}

//*****************************Main Loop***************************************
void main(void) {
     
	SETUP();
	    
	while(1)
	{
        
    LEER_S1();
    __delay_ms(100);
    POT_r = CONV(POTENCIOMETRO);
    
    LEER_S2();
    __delay_ms(100);
    CONT_r = CONV(CONT);
    
     LEER_S3();
    __delay_ms(100);
    TEMP_r = CONV(TEMPERATURA);
    
    LCD();
  
	
        }
    
    return;
}
//*******************************Subrutinas************************************    
    
//**Configuración general   
void SETUP(void){
        
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;              //LCD
    PORTE = 0x07;

    TRISA = 0;
    TRISD = 0;
    TRISB = 0;
    TRISC = 0b00010000;     // 0x10 RC3 es CLk sale a slaves, RC4 es MISO, RC5 es MOSI
    TRISCbits.TRISC6 = 0;   //TX
    TRISCbits.TRISC7 = 1;   //RX
    TRISE = 0;              // Chip select entre slaves en 1 para no leer ninguno

    ANSEL = 0;
    ANSELH = 0;      

    SPBRG = 25;             //configuraciones velocidad rx/tx
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 0;
    SPBRGH = 0;
    
    TXSTAbits.SYNC = 0;     //Configuraciones tx
    RCSTAbits.SPEN = 1;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    
    PIE1bits.RCIE = 1;      //Configuraciones rx
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    
    SSPCONbits.SSPEN = 0;   //Configuraciones spi funcionen
    SSPSTAT = 0X00;
    SSPCON= 0X11;
    SSPCONbits.SSPEN = 1;   
    
    Lcd_Init();
    
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("POT");
 
    Lcd_Set_Cursor(1,7);
    Lcd_Write_String("CONT");

    Lcd_Set_Cursor(1,13);
    Lcd_Write_String("TEMP");
             
    }

void LCD(void){
    
    
    Lcd_Set_Cursor(2,13);
    Lcd_Write_String(TEMP_r);
    
    Lcd_Set_Cursor(2,7);
    Lcd_Write_String(CONT_r);
    
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String(POT_r);  

}
   
//**Lectura slave 1   
void LEER_S1 (void){
    
    PORTEbits.RE0 =0;   //chip select a esclavo 1

     POTENCIOMETRO = READ_SPI (contador);
      __delay_ms(2);
      
     PORTEbits.RE0 =1; 
     
     //PORTB = POTENCIOMETRO  ;  
}

//**Lectura slave 2
void LEER_S2 (void){
    
    PORTEbits.RE1 =0;   //chip select a esclavo 2

    CONT = READ_SPI (contador);
      __delay_ms(2);
      
    PORTEbits.RE1 =1; 
  //   PORTB = CONT  ; 
}

//**Lectura slave 3
void LEER_S3 (void){
    
    PORTEbits.RE2 =0;   //chip select a esclavo 3

    TEMPERATURA = READ_SPI (contador);
    __delay_ms(2);
    
    PORTEbits.RE2 =1; 
 //   PORTB = TEMPERATURA  ;     
}

//Envio de los datos 
uint8_t  TRANSMITIR_INFO(void){
    


}

    
    
    

