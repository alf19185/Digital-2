/*
 * File:   Principal_Slave2.c
 * Author: Gaby
 *
 * Created on 12 de febrero de 2021, 11:28 AM
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
#define _XTAL_FREQ 8000000

//******************************Variables**************************************

uint8_t FLAG_PUSH = 0;
uint8_t FLAG_UP = 0;
uint8_t FLAG_DOWN = 0;

//***************************Prototipo Funciones*******************************

void UP(void);
void DOWN (void);
void SETUP (void);

//******************************ISR*******************************************
void __interrupt() 

    ISR(void){
        
    if (INTCONbits.RBIF == 1 && INTCONbits.RBIE == 1){  
        
        //INTCONbits.RBIF = 0;
        if (FLAG_PUSH == 0){                
            FLAG_PUSH = 1;
            INTCONbits.RBIE = 0;
        }
    }
}
//*****************************Main Loop***************************************
void main(void) {  
    
    SETUP();
    
    while(1){
                 
        UP();
        DOWN();
        
        }
    return;
}

//*****************************Subrutinas**************************************

void SETUP (void){

    TRISD = 0;
    TRISC = 0;
    TRISA = 0;
    TRISB = 0b00000101;         // 2 Push
    TRISE = 0;
    PORTE = 0;
    PORTA = 0; 
    PORTB = 0; 
    PORTC = 0; 
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0; 
    //WPUB = 0b00000101;          
    OPTION_REGbits.nRBPU = 1;
    INTCONbits.GIE = 1;         //Global interrupts enabled
    INTCONbits.PEIE = 1; 
    INTCONbits.RBIE = 1;        //Interrupcion PORTB
    INTCONbits.RBIF = 1; 
    
    return;
}

//***Contador sube y tiene antirebote push
void UP (void){
    
    if (FLAG_PUSH == 1){
        if (FLAG_UP == 0){
            if (PORTBbits.RB0 == 0){
                __delay_ms(10);
                
                PORTD = PORTD + 1;
                FLAG_PUSH = 0;
                FLAG_UP = 1;
                INTCONbits.RBIE = 1;
            }  
        }  
    }
    
    if (FLAG_UP == 1){
        if (PORTBbits.RB0 == 1){
        __delay_ms(10);
        FLAG_UP = 0;
        }
    }    
}


//****Contador baja y tiene antirebote
void DOWN(void){
    
    if (FLAG_PUSH == 1){
        if (FLAG_DOWN == 0){
            if (PORTBbits.RB2 == 0){
                __delay_ms(10);
                PORTD = PORTD - 1;
                FLAG_PUSH = 0;
                FLAG_DOWN = 1;
                INTCONbits.RBIE = 1;
            }  
        }  
    }
    
    if (FLAG_DOWN == 1){
        if (PORTBbits.RB2 == 1){
        __delay_ms(10);
        FLAG_DOWN = 0;
        }
    }    
}