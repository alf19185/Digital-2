/* 
 * File:   LCD.h
 * Author: Tomado de electrosome - https://electrosome.com/interfacing-lcd-with-pic-microcontroller-hi-tech-c/
 *
 * Created on 4 de febrero de 2021, 10:26 AM
 */

#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  


void LCD_Cmd(uint8_t comando);
void LCD_clear(void);
void LCD_home(void);
void LCD_init(void);
void LCD_Write_Character(char caracter);
void LCD_Write_String(char *a);
void LCD_Set_Cursor(uint8_t linea, uint8_t columna);
void LCD_Shift_links();
void LCD_Shift_rechts();
void LCD_Cursor_rechts(uint8_t espacios);
void LCD_Cursor_links(uint8_t espacios);
char uint_to_char(uint8_t numero);
uint16_t * uint_to_array(uint8_t numero);

#endif	