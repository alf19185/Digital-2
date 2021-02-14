#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
#include  "ADC.h"

void ADC_C (unsigned int CH){
   
  switch(CH){
        
         case 0: 
            ADCON0bits.CHS3 = 0;  //ANS0
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 1: 
            ADCON0bits.CHS3 = 0;   //AN1
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;   
            
        case 2: 
            ADCON0bits.CHS3 = 0;   //AN2
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;   
            
        case 3: 
            ADCON0bits.CHS3 = 0;  //AN3
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;   
            
        case 4: 
            ADCON0bits.CHS3 = 0;  //AN4
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;   
            
        case 5: 
            ADCON0bits.CHS3 = 0;  //AN5
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;  
            
        case 6: 
            ADCON0bits.CHS3 = 0;  //AN6
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;   
            
        case 7: 
            ADCON0bits.CHS3 = 0;  //AN7
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;   
            
        case 8: 
            ADCON0bits.CHS3 = 1;  //AN8
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;   
            
        case 9: 
            ADCON0bits.CHS3 = 1;  //AN9
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;   
            
        case 10: 
            ADCON0bits.CHS3 = 1;  //AN10
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;  
            
        case 11: 
            ADCON0bits.CHS3 = 1;  //AN11
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;   
            
        case 12: 
            ADCON0bits.CHS3 = 1;   //AN12
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;   
        case 13: 
            ADCON0bits.CHS3 = 1;  //AN13
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;   
        
        default: 
            ADCON0bits.CHS3 = 0;  //AN0
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
    }
}

void ADC_CONVCLK(uint8_t CONV){
    
      switch(CONV){
          
        case 0: 
            ADCON0bits.ADCS0 = 0;       //FOSC/2
            ADCON0bits.ADCS0 = 0;
            break;
            
        case 1: 
            ADCON0bits.ADCS0 = 0;       //FOSC/8
            ADCON0bits.ADCS0 = 1;
            break;
            
        case 2: 
            ADCON0bits.ADCS0 = 1;       //FOSC/32
            ADCON0bits.ADCS0 = 0;
            break;
            
        case 3: 
            ADCON0bits.ADCS0 = 1;       //FRC
            ADCON0bits.ADCS0 = 1;
            break;
            
        default: 
            ADCON0bits.ADCS0 = 0;       //FOSC/2
            ADCON0bits.ADCS0 = 0;
            break;
    }
      
    ADCON0bits.ADON = 1;                //Configuraciones para funcione ADC
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    INTCONbits.PEIE = 1;
    __delay_ms(30);
    ADCON0bits.GO_nDONE = 1;  

}

void ADC_CONTINUE(){                      //Configuraciones para continuar ADC
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    __delay_ms(20);
    ADCON0bits.GO_nDONE = 1;
    return;
}

uint8_t ADC_READ (uint8_t JUSTIFICACION){ 
    
    uint8_t VALOR_ADC = 0;
    
    switch (JUSTIFICACION){
        case 0:
            VALOR_ADC  = ADRESH;    //Justificado a la izquierda
            break;
        case 1:
            VALOR_ADC  = ADRESL;    //Justificado a la derecha
            break;
        default:
            VALOR_ADC  = ADRESH;
    }
    return (VALOR_ADC );
}

