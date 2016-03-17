/*
 * lcd.c
 *
 *  Created on: 14-03-2016
 *      Author: psm11
 */
#include "lcd.h"

void lcdinit(void)
{
	LCD_DDR = 0xFF;
	//init wyświetlacz
	_delay_ms(45);

//	lcd_write_instr(3);
//	_delay_ms(5);
//	lcd_write_instr(3);
//	_delay_ms(5);
//	lcd_write_instr(3);
//	_delay_ms(5);
//	lcd_write_instr(2);
//	_delay_ms(1);
	lcd_write_instr(0x33);
	_delay_ms(1);
	lcd_write_instr(0x32);
	_delay_ms(1);

	lcd_write_instr(0x28);
	lcd_write_instr(0x08);   //0b00001010 - migający kursor
	lcd_write_instr(0x01);	 //czyść i przenieś na początek, jak lcd_clear
	lcd_write_instr(0x06);	 //co sie stanie jak 0b00000111?
	lcd_write_instr(0x0F);   //włącz all
	_delay_ms(1);
}


void lcd_write_instr(uint8_t data )
{
	//wyślij pojedynczą instrukcję do wyświetlacza
	LCD_PORT &= ~(1<<LCD_RS);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);

	_delay_ms(1);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data<<4);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);

	_delay_ms(1);
}


void lcd_clear(void)
{
	lcd_write_instr(0x01);
}


void lcd_write_data(uint8_t data)
{
	//wyślij pojedynczą daną (byte) do wyswietlacza

	LCD_PORT |= (1<<LCD_RS);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);

	_delay_ms(1);

	LCD_PORT |= (1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0F) | (data<<4);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);

	_delay_us(500);
}

void lcd_set_xy(uint8_t r, uint8_t k)
{
	lcd_write_instr(0x80 + 0x40*r + k);
}
void lcd_write_text_xy(uint8_t r, uint8_t k, char* text)
{
	lcd_set_xy(r,k);
	while(*text)
	{
		lcd_write_data(*text);
		text++;
	}
}

int main()
{
	lcdinit();
	lcd_write_text_xy(0,0,"konstantynopolitanczykowianeczka");
	int i = 0;
	while(1)
	{
	}

}
