/*
 * main.c
 *
 *  Created on: 04-03-2016
 *      Author: psm11
 */


#include <avr/io.h>
#include "longdelay.h"

int main(void)
{
	DDRC = 0xFF;

	while(1)
	{
		longdelay(1000);
		PORTC = 0b01101000;
		longdelay(1000);
		PORTC = ~0b01101000;
	}
}
