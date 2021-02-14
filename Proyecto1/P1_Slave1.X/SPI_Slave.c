#include <pic16f887.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
#include  "SPI_Slave.h"



void CONFIG_SPI_MASTER(void){
    
    SSPCONbits.SSPEN = 0;     
	SSPSTAT = 0b01000000;   
	SSPCON = 0b00100010;   //Master, SPI mode, CLK FOSC/64
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

uint8_t READ_SPI (void){

  WAIT_SPI();      // Wait until all bits receive
  
  return(SSPBUF); // Read the received data from the buffer
}

void WRITE_SPI (uint8_t data){ //Write data to SPI bus
  SSPBUF = data;
}

uint8_t CHECK_DATA(void){
    
 if(SSPSTATbits.BF)
    return (1);
  else
    return (0);
}