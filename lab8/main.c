/*
 * main.c
 *
 *  Created on: 01-05-2016
 *      Author: psm11
 */

#include "lcd.h"
#include "i2c.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

volatile uint8_t time_data[7] = {56, 59, 23, 6, 31, 12, 16};
volatile uint8_t init_time_data[7] = {56, 59, 23, 6, 31, 12, 16};
char* dni_tygodnia[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

uint8_t bcd2dec(uint8_t x)
{
	return (x >> 4) * 10 + (x & 0x0F);
}

uint8_t dec2bcd(uint8_t x)
{
	return ((x/10) << 4) | (x % 10);
}

void set_time(uint8_t *time_data)
{
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0);
	for (int i = 0; i<7; i++)
	{
		i2c_write(dec2bcd(time_data[i]));
	}
	i2c_stop();
}

void get_time(uint8_t *time_data)
{
	i2c_start();
	i2c_write(0b11010000); //adres slave'a + zapisujemy
	i2c_write(0); //adres w pamięci zegara
	i2c_start();
	i2c_write(0b11010001); //adres slave + odczytujemy
	for (int i = 0; i<6; i++)
	{
		time_data[i] = bcd2dec(i2c_read(1));
	}
	time_data[6] = bcd2dec(i2c_read(0));
	i2c_stop();
}
ISR(INT0_vect)
{
	get_time(time_data);
//	get_time_vars(&s, &m, &h, &weekday, &mday, &month, &year);
	lcd_set_xy(0, 0);
	fprintf(&lcd_stream, "%02d:%02d:%02d", time_data[2], time_data[1], time_data[0]);
	lcd_set_xy(0, 1);
	fprintf(&lcd_stream, "%02d/%02d/%02d ", time_data[4], time_data[5], time_data[6]);//, dni_tygodnia[time_data[3]]);
	fprintf(&lcd_stream, dni_tygodnia[time_data[3]-1]);
}

void set_interrupt()
{
	sei();
	MCUCR |= (1<< ISC01);
	GICR |= (1<<INT0); //wlaczamy, wylaczamy mozliwosci roznych przerwan

}

int main()
{
	set_interrupt();
	i2c_init();
	lcd_init();
	set_time(init_time_data);
//	set_time_vars(s, m, h, weekday, mday, month, year);
	while(1){}
}
