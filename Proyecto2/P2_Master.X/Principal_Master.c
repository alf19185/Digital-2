/*
 * File:   Principal_Master.c
 * Author: Gaby
 *
 * Created on 22 de febrero de 2021, 06:35 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
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
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "I2C.h"
#include "USART.h"

//**************************VARIABLES**************************************

//Constantes para lectura I2C
uint8_t LECTURA = 0;
uint8_t BANDERA_T = 0;
uint8_t WRITE = 0xA6;        //Para escribir en sensor
uint8_t READ = 0xA7;         //Para leer en sensor
uint8_t P_CTL = 0X2D;        //Power-saving features control 
uint8_t D_FRMT = 0X31;       //D format control 
uint8_t DX0 = 0X32;          //Direccion X-Axis Data 0 
uint8_t DX1 = 0X33;          //Direccion X-Axis Data 1
uint8_t DY0 = 0X34;          //Direccion Y-Axis Data 0
uint8_t DY1 = 0X35;          //Direccion Y-Axis Data 1
uint8_t DZ0 = 0X36;          //Direccion Z-Axis Data 0
uint8_t DZ1 = 0X37;          //Direccion Z-Axis Data 1


// Variables
int EJEX = 0;       //Valor Eje x que se envía en UART
int EJEY = 0;       //Valor Eje y que se envía en UART
int EJEZ = 0;       //Valor Eje z que se envía en UART
uint8_t XL = 0;
uint8_t XH = 0;
uint8_t YL = 0;
uint8_t YH = 0;
uint8_t ZL = 0;
uint8_t ZH = 0;
uint8_t c = 0;
uint8_t LED1=0;
uint8_t LED2=0;



//************************PROTOTIPO FUNCIONES*******************************

void SETUP(void);

void ACELEROMETRO_CONFIG(void);

void ACELEROMETRO_W(uint8_t num, uint8_t data);

unsigned short ACELEROMETRO_R(uint8_t num);

void LEER_VALORES(void);

float ACELEROMETRO_AX(void);


void putch(char data){      //Definiendo puerto serial para terminal
    
    while (TXIF == 0) {}
    TXREG = data; 
    
}

//****************************INTERRUPCIONES*********************************

void __interrupt() isr(void) {
    di();

    
    if (PIR1bits.RCIF == 1) {           //Interrupción para recepción
        
        c =RCREG;               
        
        if (c & 0x30)  {                //Puerto serial recibe 0,1,2 o 3
            
            if (c & 0x01) {             //Si bit 1 se encuentra encendido, enciende LED1 
                PORTAbits.RA0= 1;  
            }
            else {
            PORTAbits.RA0= 0;           //De lo contrario permanece apagado
            }
            
            if (c & 0x02) {
                PORTAbits.RA1= 1;       //Si bit 2 se encuentra encendido, enciende LED2 
            }
            else {
            PORTAbits.RA1= 0;           //De lo contrario se encuentra apagado 
            }     
            
        }
          
         
    }
                
    ei();
}
//****************************MAIN*******************************************

void main(void) {
    SETUP();                        //Configuraciones generales
    I2C_Master_Init(100000);        //Configuraciones del I2C
    ACELEROMETRO_CONFIG();          //Configuraciones del sensor para envio de datos
     
    //***LOOP****    
    while (1){
        
    LEER_VALORES();       
    printf("%d, %d, %d\r\n", EJEX, EJEY, EJEZ);   
    __delay_ms (2000);
    
    }
}


//******************************SUBRUTINAS***********************************

//Configuraciones Generales

void SETUP(void) {

    OSCCONbits.IRCF2 = 1;  //4MHZ
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;

    PORTA = 0;              //LEDS   
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    TRISA = 0;
    TRISB = 0;
    TRISC = 0;              // Para I2C RC3 es CLk , RC4 es SDA 
    TRISD = 0;
    TRISE = 0;
     
    ANSEL = 0;
    ANSELH = 0;
    
    CONFIG_USART();         //9600 baud rate

    PIE1bits.RCIE = 1;
    PIR1bits.RCIF =0; 
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;     //Interrupciones
    
}

void ACELEROMETRO_CONFIG(void) {

    ACELEROMETRO_W(D_FRMT, 0x0B);       //Se envía al sensor el formato en el que se obtienen los datos
    __delay_ms(5);

    ACELEROMETRO_W(P_CTL, 0x08);        //Se envía la forma de energizar y controlar sensor
    __delay_ms(5);
}

unsigned short ACELEROMETRO_R(uint8_t num) {

    unsigned short LECTURA;

    I2C_Master_Start();
    I2C_Master_Write(WRITE);        //Envia dato indicador de escritura
    I2C_Master_Write(num);          //Envia dirección del dato que se desea obtener
    I2C_Master_RepeatedStart();
    I2C_Master_Write(READ);         //Envia dato indicador de lectura
    LECTURA = I2C_Master_Read(0);
    I2C_Master_Stop();

    return LECTURA;                 //Se obtiene valor que se desea 
}

void ACELEROMETRO_W(uint8_t num, uint8_t data) {

    I2C_Master_Start();
    I2C_Master_Write(WRITE);        //Envia dato indicador de escritura
    I2C_Master_Write(num);          //Se envia la dirección del registro a configurar
    I2C_Master_Write(data);         //Se envía dato de configuracion
    I2C_Master_Stop();
    
}

void LEER_VALORES(void) {
    
    int tempx =0;
    int tempy =0;
    int tempz =0;
    
    XL = ACELEROMETRO_R(DX0);       //Lectura de los 2 valores para eje x
    XH = ACELEROMETRO_R(DX1);
    tempx= XH;                      //Datos se encuentra en complemento a 2
    tempx = tempx<<8;               //Por ello se hace el shift y se suman 
    EJEX = tempx + XL;              //los bits menos significativos para unificarlos
  
    YL = ACELEROMETRO_R(DY0);       //Lectura de los 2 valores para eje y
    YH = ACELEROMETRO_R(DY1);    
    tempy= YH;                      //Misma transformacion del eje X en Y y Z
    tempy = tempy<<8;
    EJEY = tempy + YL;

    ZL = ACELEROMETRO_R(DZ0);
    ZH = ACELEROMETRO_R(DZ1);
    tempz= ZH;  
    tempz = tempz<<8;  
    EJEZ = tempz + ZL;
}



