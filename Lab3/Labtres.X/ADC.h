/* 
 * File:   ADC.h
 * Author: Gaby
 *
 * Created on 7 de febrero de 2021, 12:23 PM
 */

#ifndef ADC_H
#define	ADC_H



#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>

void ADConfig(uint8_t oscFreq,uint8_t canal, unsigned char justificado);

uint8_t AnalogRead_8(unsigned char just);

void ADCinit();

void ADC_CHselect(uint8_t canal);


#endif	/* XC_HEADER_TEMPLATE_H */



