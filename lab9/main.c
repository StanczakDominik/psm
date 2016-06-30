/*
 * main.c
 *
 *  Created on: 03-05-2016
 *      Author: psm11
 */
#include "ow.h"
#include "lcd.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
FILE lcd_stream = FDEV_SETUP_STREAM (lcd_putc, NULL, _FDEV_SETUP_WRITE);

//termometr
//1. inicjalizacja: reset, termometr odpowiada present pulse
//2. read rom - wlasciwie u nas skip rom bo jeden termometr
//wyslac bajt CC
//3. komenda funkcyjna termometru
//convert T: czytaj temperature, bajt 44

void thermo_init()
{

}

int main()
{
	lcd_init();

	while(1)
	{
		if(!OW_reset())
		{
			OW_send_byte(0xCC);
			OW_send_byte(0x44);
			_delay_ms(750);
			if(!OW_reset())
			{
				OW_send_byte(0xCC);
				OW_send_byte(0xBE); //chcemy odczytac zawartosc pamieci
				uint8_t x = OW_read_byte();
				uint8_t y = OW_read_byte();
				//sklejamy x, y
				uint16_t z = (y<<8) | x;
				lcd_set_xy(0, 0);
				fprintf(&lcd_stream, "%d.%04d deg C", z>>4, (z&0x0F)*625);
				lcd_set_xy(0, 1);
				fprintf(&lcd_stream, "dbg %d %d", x, y);


			}
		}
	}
}
