/* 
 * File:   LCD.h
 * Author: Gaby
 *
 */

#ifndef LCD_H
#define	LCD_H

#include <xc.h> 
#include <stdint.h>

#define  _XTAL_FREQ 8000000


void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();
const char* CONV(uint8_t numero);

#endif	/* LCD_H */

