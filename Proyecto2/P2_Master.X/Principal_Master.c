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

uint8_t LECTURA = 0;
uint8_t BANDERA_T = 0;
uint8_t WRITE = 0xA6; //Para escribir en sensor
uint8_t READ = 0xA7; //Para leer en sensor
uint8_t P_CTL = 0X2D; //Power-saving features control 
uint8_t D_FRMT = 0X31; //D format control 
uint8_t DX0 = 0X32; //Direccion X-Axis Data 0 
uint8_t DX1 = 0X33; //Direccion X-Axis Data 1
uint8_t DY0 = 0X34; //Direccion Y-Axis Data 0
uint8_t DY1 = 0X35; //Direccion Y-Axis Data 1
uint8_t DZ0 = 0X36; //Direccion Z-Axis Data 0
uint8_t DZ1 = 0X37; //Direccion Z-Axis Data 1

int EJEX = 0;
int EJEY = 0;
int EJEZ = 0;

uint8_t XL = 0;
uint8_t XH = 0;

uint8_t YL = 0;
uint8_t YH = 0;
uint8_t ZL = 0;
uint8_t ZH = 0;

uint8_t X0 = 0;
uint8_t X1 = 0;
uint8_t X2 = 0;
uint8_t X3 = 0;
uint8_t Y0 = 0;
uint8_t Y1 = 0;
uint8_t Y2 = 0;
uint8_t Y3 = 0;
uint8_t Z0 = 0;

uint8_t Z1 = 0;
uint8_t Z2 = 0;
uint8_t Z3 = 0;
uint8_t X_1 = 0;
uint8_t Z_1 = 0;
uint8_t Y_1 = 0;
uint8_t X_U = 0;
uint8_t X_D = 0;
uint8_t Y_U = 0;
uint8_t Y_D = 0;
uint8_t Z_U = 0;
uint8_t Z_D = 0;
uint8_t variable = 0;

uint8_t a = 0;
uint8_t b = 0;
uint8_t c = 0;
uint16_t contador=0;
uint8_t LED1=0;
uint8_t LED2=0;
uint8_t ENTER=0;
uint8_t FLAG_RC;

//************************PROTOTIPO FUNCIONES*******************************

void SETUP(void);

void ACELEROMETRO_CONFIG(void);

void ACELEROMETRO_W(uint8_t num, uint8_t data);

unsigned short ACELEROMETRO_R(uint8_t num);

void LEER_VALORES(void);

uint8_t TX(void);

void LUCES (void);


void EJEX_TO_CHARS(void);

void EJEY_TO_CHARS(void);

void EJEZ_TO_CHARS(void);

void EJEs_TO_CHARS(void);

float ACELEROMETRO_AX(void);

//Definiendo puerto serial para terminal debug
void putch(char data){

    
    while (TXIF == 0) {}
    TXREG = data;
   
    
}

//****************************INTERRUPCIONES*********************************

void __interrupt() isr(void) {
    di();

    
    if (PIR1bits.RCIF == 1) { 
        
        c =RCREG;
        
        if (c & 0x30)  {
            
            if (c & 0x01) {
                PORTAbits.RA0= 1;  
            }
            else {
            PORTAbits.RA0= 0; 
            }
            
            if (c & 0x02) {
                PORTAbits.RA1= 1;  
            }
            else {
            PORTAbits.RA1= 0; 
            }     
            
        }
          
         
    }
         
       /*   switch (FLAG_RC){
            case 0:
            FLAG_RC++;  
            PORTAbits.RA2 =1;
            PORTA=RCREG;
            break;
            
            case 1:
            FLAG_RC++;
            PORTB=RCREG;
            break;
            
            case 2: 
            PORTAbits.RA2 =0;    
            FLAG_RC= 0;
            ENTER =RCREG;
            
            break;
       }
      if (ENTER == 10){
               if (LED1 == 1){
        
               PORTAbits.RA0 = 1;
            }
                else {
                PORTAbits.RA0 =0;
            }
    
                if (LED2 == 1){
        
                PORTAbits.RA1 = 1;
            }
                else {
                PORTAbits.RA1 =0;
            }
    
           
        }else{
            LED1 = 0;
            LED2 = 0;
            ENTER = 0;
        } */ 
        
    ei();
}
//****************************MAIN*******************************************

void main(void) {
    SETUP();
    printf("Buenos dias \r");
    I2C_Master_Init(100000);
    
    ACELEROMETRO_CONFIG();
     
    while (1){
        
    LEER_VALORES();    
    contador++;
    
   printf("%d, %d, %d\r\n", EJEX, EJEY, EJEZ);

   
    __delay_ms (2000);
    
    printf("c=%x ",c);
    
    }
    
  
    //***LOOP****    
    while (1) {

        if (a > 10) {
            a = 0;
            PIE1bits.TXIE = 1;
        } 
        
       
        LEER_VALORES();
        EJEX_TO_CHARS();

    }

}

//******************************SUBRUTINAS***********************************

//Configuraciones Generales

void SETUP(void) {


    OPTION_REG = 0b11010111; //configuracion para activar las PULL - UPS del puerto B y timer 0

    /*OSCCONbits.IRCF2 = 1;       //8MHZ
        OSCCONbits.IRCF1 = 1;
        OSCCONbits.IRCF0 = 1;*/

    OSCCONbits.IRCF2 = 1; //4MHZ
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;

    PORTA = 0; //LEDS
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    TRISA = 0;
    TRISB = 0;
    TRISC = 0; // 0x10 RC3 es CLk sale, RC4 es SDA 
    TRISD = 0;
    TRISE = 0;
    
  //  TRISC = 0b10011000;
   
    ANSEL = 0;
    ANSELH = 0;
    
    CONFIG_USART();

     
    
  //  PIE1bits.TXIE = 1;
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF =0; 
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1; //Interrupcion TX
    
//    INTCONbits.TMR0IE = 1; //se activan las interrupciones del timer 0
//    INTCONbits.T0IF = 0; //limpiar bandera del timer0


}

void ACELEROMETRO_CONFIG(void) {

    ACELEROMETRO_W(D_FRMT, 0x0B);
    __delay_ms(5);

    ACELEROMETRO_W(P_CTL, 0x08);
    __delay_ms(5);
}

unsigned short ACELEROMETRO_R(uint8_t num) {

    unsigned short LECTURA;

    I2C_Master_Start();
    I2C_Master_Write(WRITE);
    I2C_Master_Write(num);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(READ);
    LECTURA = I2C_Master_Read(0);
    I2C_Master_Stop();

    return LECTURA;
}

void ACELEROMETRO_W(uint8_t num, uint8_t data) {

    I2C_Master_Start();
    I2C_Master_Write(WRITE);
    I2C_Master_Write(num);
    I2C_Master_Write(data);
    I2C_Master_Stop();
    
}

uint8_t TX(void) {

    switch (BANDERA_T) {

        case 0:
            BANDERA_T++;
            return X0;
            break;
        case 1:
           
            BANDERA_T++;
            return X1;

            break;
        case 2:
            
            BANDERA_T++;
            return X2;

            break;
        case 3:
            
            BANDERA_T++;
            return X3;
            break;

            /*   case 4:
                  PORTAbits.RA0 =1;
                  BANDERA_T++;
                  return X1 ;
              
                   break;      
               case 2:
                     PORTAbits.RA0 =1;
                   BANDERA_T++;
                   return 44;
                   break;
               case 3:
                    PORTAbits.RA0 =1;
                   BANDERA_T++;
                   return Y_U ;
                   break;
               case 4:
                     PORTAbits.RA0 =1;
                   BANDERA_T++;
                   return Y_D ;
                   break;  
               case 5:
                     PORTAbits.RA0 =1;
                   BANDERA_T++;
                   return 44;
                   break;
               case 6:
                     PORTAbits.RA0 =1;
                   BANDERA_T++;
                   return Z_U ;
                   break;     
               case 7:
                     PORTAbits.RA0 =1;
                   BANDERA_T++;
                   return Z_D;
                   break;      */
        case 4:
            PORTAbits.RA0 = 0;
            BANDERA_T = 0;
            b++;
            return 10;
            break;
    }
}

void LEER_VALORES(void) {
    int tempx =0;
    int tempy =0;
    int tempz =0;
    
    XL = ACELEROMETRO_R(DX0);
   // printf("XL = %x ", XL);
    
    XH = ACELEROMETRO_R(DX1);
  //  printf("XH = %x ", XH);
    
    tempx= XH;
   // printf("tempx = %d ", tempx);
    
    tempx = tempx<<8;
   // printf("tempx Shift = %d ", tempx);
    
    EJEX = tempx + XL;
   // printf("EJEX = %d ", EJEX);
    
   

    YL = ACELEROMETRO_R(DY0);
    YH = ACELEROMETRO_R(DY1);
    
    tempy= YH;
   // printf("tempx = %d ", tempx);
    
    tempy = tempy<<8;
   // printf("tempx Shift = %d ", tempx);
    
    EJEY = tempy + YL;

    ZL = ACELEROMETRO_R(DZ0);
    ZH = ACELEROMETRO_R(DZ1);
    
    tempz= ZH;
   // printf("tempx = %d ", tempx);
    
    tempz = tempz<<8;
   // printf("tempx Shift = %d ", tempx);
    
    EJEZ = tempz + ZL;
}

void EJEX_TO_CHARS(void) {

    X0 = ASCII(XH & 0b00001111);
    X1 = ASCII((XH & 0b11110000) >> 4);
    X2 = ASCII(XL & 0b00001111);
    X3 = ASCII((XL & 0b11110000) >> 4);

}
/*
void EJEY_TO_CHARS (void){
    
    Y_U = ASCII(Y & 0b00001111);
    Y_D =ASCII((Y & 0b11110000)>>4);
    
    }

void EJEZ_TO_CHARS (void){
    
    Z_U = ASCII((Z & 0b00001111));
    Z_D = ASCII((Z & 0b00110000)>>4);
    
    }

void EJEs_TO_CHARS (void){
    
    X_1 = ASCII(X);
    Y_1 = ASCII(Y);
    Z_1 = ASCII(Z);  
  
    }*/

