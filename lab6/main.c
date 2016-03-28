/*
 * main.c
 *
 *  Created on: 28-03-2016
 *      Author: psm11
 */

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "lcd.h"
#include "spi.h"

uint16_t liczba;
double v_in;
FILE lcd_stream=FDEV_SETUP_STREAM (lcd_putc, NULL, _FDEV_SETUP_WRITE);

int main()
{
	lcdinit();
	InitSPI();
	while(1)
	{
		PORTB &=~ (1<<PB4);
		TransferSPI(1);
		uint16_t high = 0b00001111 & TransferSPI(0xA0);
		uint16_t low = TransferSPI(0);
		liczba = (high<<8) | low;
		v_in = (liczba * 5.0 / 4096.0);

		lcd_set_xy(0,0);
		fprintf(&lcd_stream, "U: %f V", v_in);
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "%d %d %d", liczba, high, low);
		PORTB |= (1<<PB4);
	}
}
