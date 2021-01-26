

#include <xc.h>
// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//******************************************************************************
//VARIABLES
//******************************************************************************

#define  _XTAL_FREQ 8000000

unsigned char BANDERA=1;
unsigned char FLAG1 = 0;
unsigned char FLAG2 = 0;
unsigned char INICIAR = 0;

//******************************************************************************
//PROTOTIPO DE FUNCIONES
//******************************************************************************

void Setup(void);
void Race(void);

//******************************************************************************
// LOOP
//******************************************************************************

void main(void) {
    
    Setup();
    
    while(1){
        
        if (PORTAbits.RA0 == 1){        //Antirebote para pull-down de inicio de carrera
             BANDERA = 0;
        }
        else{
            if (BANDERA == 0){
                BANDERA=1;
                Race();
            }
        }
       
        
        if (PORTAbits.RA1 == 1 && INICIAR== 1){      //Antirebote para avanzar en la carrera
            FLAG1 = 1;
        }
        else{
            if (FLAG1 == 1){
                FLAG1 = 0;
                if (PORTC == 0){
                    //LA DA EL VALOR INICIAL AL PUERTO PARA LA CARRERA
                    PORTC = 1; 
                }
                else if (PORTC == 0b01000000) {
                    //OPCION CUANDO UN JUGADOR GANA:
                    PORTC = PORTC<<1;
                    //BIT PARA INDICAR QUIEN GANA
                    PORTAbits.RA3 = 1;
                    //REINICIA LA VARIABLE DE INICIO PARA LA CARRERA
                    INICIAR= 0;
                }
                else{
                    PORTC = PORTC<<1;
                }
            }
        }
        
        // JUGADOR 2
        
        if (PORTAbits.RA2 == 1 && INICIAR== 1){
            FLAG2 = 1;
        }
        else{
            if (FLAG2 == 1){
                FLAG2 = 0;
                if (PORTD == 0){
                    PORTD = 1;
                }
                else if (PORTD == 0b01000000) {
                    PORTD = PORTD<<1;
                    PORTAbits.RA4 = 1;
                    INICIAR= 0;
                }
                else{
                    PORTD = PORTD<<1;
                }
            }
        }
        
    }
}

//******************************************************************************
//SETUP
//******************************************************************************

void Setup(void) {
    PORTA = 0;  
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;  
    PORTB =0;
    TRISA = 0b00000111;             //inputs 
    TRISC = 0;                      //race 1
    TRISD = 0;                      //race 2
    TRISE = 0;                      //semáforo
    ANSEL = 0;  
    ANSELH = 0;
    
  }

//******************************************************************************
//SUBRUTINAS
//******************************************************************************

void Race(void){
    
    PORTC = 0;
    PORTD = 0;                      //Inicia con jugadores en 0
    PORTAbits.RA3 = 0;              //Si se ha jugado previamente, se quitan la luz del ganador
    PORTAbits.RA4 = 0;
   
    PORTE=1;
    
    for(int i = 0; i < 3; i++){         //Para cambio de luces semaforo se inicia en 0                             
        __delay_ms(50);
        PORTE = PORTE<<1;               //Se incrementa 1 puerto hasta alcanzar 3
    }
    INICIAR=1;                       //Deja que inicie la carrera
}