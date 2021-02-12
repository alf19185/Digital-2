#include <pic16f887.h>
#include  "SPI_Slave.h"
    
void CONFIG_SPI_MASTER(void){
    
    SSPCONbits.SSPEN = 0;     
	SSPSTAT = 0b01000000;   
	SSPCON = 0b00100100;   //Master, SPI mode, CLK FOSC/64
	SSPCONbits.SSPEN = 1;
    
    }

void CONFIG_SPI_SLAVE(void){
    
    SSPCONbits.SSPEN = 0;
	SSPSTAT = 0b01000000;   
	SSPCON = 0b00100100;   //Slave, Write Collision Detect bit disabled; no overflow, habilita pines SCK, SDO, SDI, SS; SPI SLAVE MODE INCLUYE PIN SS 
	SSPCONbits.SSPEN = 1;  
    
    }