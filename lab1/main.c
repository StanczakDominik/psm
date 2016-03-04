/*
 * main.c
 *
 *  Created on: 04-03-2016
 *      Author: psm11
 */

#include <stdint.h>
#include <avr/io.h>
#include "longdelay.h"

int main(void)
{
	DDRC = 0xFF;
	DDRD = 0x00;
	PORTD = 0xFF;

	uint8_t status = 0b0011;
	uint8_t state = 0;
	uint16_t speed = 10;
	uint8_t direction = 1;
	while(1)
	{
		if (!(PIND & (1<<PD0)))
		{
			longdelay(100);
			if (!(PIND & (1<<PD0)))
				state = (state + 1)%2;
		}
		if (!(PIND & (1<<PD1)))
		{
			speed = (speed + 2)%50;
		}
		if (!(PIND & (1<<PD2)))
		{
			longdelay(100);
			if (!(PIND & (1<<PD2)))
				direction = (direction + 1)%2;
		}
		if(state)
		{
			if(direction)
			{
				status = (status << 1) | (status >> 3);
			}
			else
			{
				status = (status >> 1) | (status << 3);
			}
			PORTC = status;
			longdelay(speed);
		}
	}
}
