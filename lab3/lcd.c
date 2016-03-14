/*
 * lcd.c
 *
 *  Created on: 14-03-2016
 *      Author: psm11
 */
#include "lcd.h"

void lcdinit(void)
{
	//init wyświetlacz
	delay_ms_(45);

	lcd_write_instr(3);
	delay_ms_(5);
	lcd_write_instr(3);
	delay_ms_(5);
	lcd_write_instr(3);
	delay_ms_(5);
	lcd_write_instr(2);
	delay_ms_(1);
}


void lcd_write_instr(uint8_t data )
{
	//wyślij pojedynczą instrukcję do wyświetlacza
	LCD_PORT &= ~(1<<LCD_RS);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	delay_ms_(1);
	LCD_PORT &= ~(1<<LCD_E);

	delay_ms_(1);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data<<4);
	delay_ms_(1);
	LCD_PORT &= ~(1<<LCD_E);

	delay_ms_(1);
}


void lcd_clear(void)
{
	//wyczyść wyświetlacz

}


void lcd_write_data(uint8_t data)
{
	//wyślij pojedynczą daną (byte) do wyswietlacza

	LCD_PORT |= (1<<LCD_RS);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	delay_ms_(1);
	LCD_PORT &= ~(1<<LCD_E);

	delay_ms_(1);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data<<4);
	delay_ms_(1);
	LCD_PORT &= ~(1<<LCD_E);

	delay_ms_(1);
}

void lcd_set_xy(uint8_t r, uint8_t k)
{
	//ustaw kursor na pozycję r-rząd, k-kolumna
}
void lcd_write_text_xy(uint8_t r, uint8_t k, char* text)
{
	//wypisz tekst w danym miejscu
}

int main()
{

}
