/* 
 * File:   ADC.h
 * Author: Gaby
 *
 * Created on 13 de febrero de 2021, 05:30 PM
 */
#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000

#ifndef ADC_H
#define	ADC_H

uint8_t ADC_READ( uint8_t JUSTIFICACION );

void ADC_C (unsigned int CH);

void ADC_CONVCLK(uint8_t CONV);

void ADC_JUST (uint8_t JUST);

void ADC_CONTINUE(void);

#endif	/* ADC_H */

