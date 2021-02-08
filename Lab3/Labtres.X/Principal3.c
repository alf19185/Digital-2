/*
 * File:   Principal3.c
 * Author: comandos de LCD tomados de : Electrosome - https://electrosome.com/interfacing-lcd-with-pic-microcontroller-hi-tech-c/
 *
 * Created on 4 de febrero de 2021, 10:20 AM
 */


#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "ADC.h"
#include "USART.h"

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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


#define _XTAL_FREQ 4000000
char linea2[12];

uint8_t valorADC_CH5 = 0;
uint8_t banderaADC = 1;
uint8_t valorADC_CH0 = 0;
uint16_t *num1;
uint16_t *num2;
uint16_t *num3;
uint8_t pot1 = 0;
uint8_t pot2 = 0;
uint8_t banderaSerial = 0;
uint8_t contador = 0;
char valorSerial = 'E';

uint16_t * mapear(uint8_t valor, uint8_t limReal, uint8_t limSup);


void __interrupt() ISR_ADC(void){
    if (PIR1bits.ADIF && PIE1bits.ADIE){
        PIE1bits.ADIE = 0;
        banderaADC = 1;
    }
}

void main(void) {
    TRISD = 0;
    TRISC = 0b10000000;
   // TRISCbits.TRISC7 = 1;
    PORTD = 0;
    PORTC = 0;
    LCD_init();
    ADConfig(4, 5, 'H');
    LCD_Set_Cursor(1,1);
    LCD_Write_String("S1    S2    S3");
    usart_init();
    
    
    while(1){
        if(PIR1bits.RCIF == 1){
            usartRC_Read();
            __delay_ms(5);           
        }
        
        if(PIR1bits.TXIF == 1){
            enviar(valorADC_CH5,valorADC_CH0);
        }
        
        if (banderaADC == 1){
            switch (ADCON0bits.CHS){
                case 5:
                    valorADC_CH5 = AnalogRead_8('H');
                    ADC_CHselect(0);
                    num1 = mapear(valorADC_CH5, 255, 5);
                    LCD_Set_Cursor(2, 0);
                    LCD_Write_Character(uint_to_char(num1[0]));
                    LCD_Write_Character('.');
                    LCD_Write_Character(uint_to_char(num1[1]));
                    LCD_Write_Character(uint_to_char(num1[2]));
                    LCD_Write_Character('V');
                   
                    
                   
                    break;
                case 0:
                    valorADC_CH0 = AnalogRead_8('H');
                    ADC_CHselect(1);
                    num2 = mapear(valorADC_CH0, 255, 5);
                    LCD_Set_Cursor(2, 6);
                    LCD_Write_Character(uint_to_char(num2[0]));
                    LCD_Write_Character('.');
                    LCD_Write_Character(uint_to_char(num2[1]));
                    LCD_Write_Character(uint_to_char(num2[2]));
                    LCD_Write_Character('V');
                   
                    //usartTX_Write_Str(valorADC_CH0);
                    
                    break;
                    
                default:
                    valorADC_CH0 = 0;
                    valorADC_CH5 = 0; 
            }
            
            banderaADC = 0;
            PIR1bits.ADIF = 0;
            PIE1bits.ADIE = 1;
            ADCON0bits.GO_nDONE = 1;
        }
           
            
            num3 = uint_to_array(contador);
            LCD_Set_Cursor(2,13);
            LCD_Write_Character(uint_to_char(num3[0]));
            LCD_Write_Character(uint_to_char(num3[1]));
            LCD_Write_Character(uint_to_char(num3[2]));
            enviar (valorADC_CH0,valorADC_CH5);
            //LCD_Set_Cursor(1,11);
            //LCD_Write_Character(valorSerial);
            
           // uint16_t str[3] = {valorADC_CH5, valorADC_CH0, '\n'};
            //uSartTX_Write_Str(str);
            
        //  pot1=  ASCII(valorADC_CH5);
        //  pot2 =  ASCII(valorADC_CH0);
           
         // enviar(pot1);
         // enviar(pot2);
            

    }
    return;
}


uint16_t * mapear(uint8_t valor, uint8_t limReal, uint8_t limSup){
    uint16_t resultado[3] = {0,0,0};  // u.d1.d2  [u, d1, d2]
    uint16_t dividendo = valor*limSup;
    while (limReal <= dividendo){
        resultado[0] = resultado[0] + 1;
        dividendo = dividendo - limReal;
    }
    dividendo = dividendo *10;
    while (limReal <= dividendo){
        resultado[1] = resultado[1] +1;
        dividendo = dividendo - limReal;
    }
    dividendo = dividendo *10;
    while (limReal <= dividendo){
        resultado[2] = resultado[2] +1;
        dividendo = dividendo - limReal;
    }
    
    return resultado;
}