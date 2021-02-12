#include <pic16f887.h>
#include  "SPI_Master.h"
    
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

void WAIT_SPI(void){
  while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
  
}
void READ_SPI (void){


}

void WRITE_SPI (char data) //Write data to SPI bus
{
  SSPBUF = data;
}