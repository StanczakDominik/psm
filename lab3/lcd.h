/*
 * lcd.h
 *
 *  Created on: 14-03-2016
 *      Author: psm11
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

#define LCD_PORT PORTA
#define LCD_RS 2
#define LCD_E 3

void lcdinit(void);
void lcd_write_instr(uint8_t);
void lcd_clear(void);
void lcd_write_data(uint8_t);
void lcd_write_text_xy(uint8_t, uint8_t, char*);
#endif /* LCD_H_ */
