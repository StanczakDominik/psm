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
float v_in;

int main()
{
	lcdinit();
	InitSPI();
	while(1)
	{
		TransferSPI(1);
		uint16_t high = TransferSPI(0xA0);
		uint16_t low = TransferSPI(0);
		liczba = (high<<8) | low;
		v_in = liczba * 5.0 / 4096.0;

		//lcd fprintf
	}
}
