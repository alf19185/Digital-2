#include <pic16f887.h>
#include <stdint.h>
#include <xc.h>
#define _XTAL_FREQ 8000000
#include  "SPI_Master.h"

//VALORES CORRECTOS MASTER Y SLAVE    
void CONFIG_SPI_MASTER(void){
    
    SSPCONbits.SSPEN = 0;  
    SSPSTAT = 0X00;
    SSPCON= 0X11;
    SSPCONbits.SSPEN = 1;   
                
    }

void CONFIG_SPI_SLAVE(void){
    
    SSPCONbits.SSPEN = 0;
    SSPSTAT = 0X00;
    SSPCON= 0X14;
    SSPCONbits.SSPEN = 1;
        
    
    }

void WAIT_SPI(void){
    
  while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
  
}

uint8_t  READ_SPI (uint8_t data){
   
    uint8_t dummy = SSPBUF;
    SSPBUF = data;   //dummy
     while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
   
  return(SSPBUF); // Read the received data from the buffer
}

void WRITE_SPI (uint8_t data) //Write data to SPI bus
{
  SSPBUF = data;
}

uint8_t CHECK_DATA(void){
    
 if(SSPSTATbits.BF)
    return (1);
  else
    return (0);
}