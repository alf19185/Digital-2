/* 
 * File:   
 * Author: Gabriela Alfaro
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>

void ADConfig(uint8_t oscFreq,uint8_t canal, unsigned char justificado);

uint8_t AnalogRead_8(unsigned char just);

void ADCinit();

#endif	/* XC_HEADER_TEMPLATE_H */
