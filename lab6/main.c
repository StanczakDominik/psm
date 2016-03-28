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

#define MOSI PB5
#define SCK PB7
#define SS PB4

uint16_t liczba;

void InitSPI (void)
{
	//kierunek wyjscia na MOSI (na MISO nie trzeba bo default)
	DDRB |= (1<<MOSI) | (1<<SCK)|(1<<SS);
	// aktywacja SPI, tryb Master, predkosc zegara Fosc/64
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR1);
}

uint8_t TransferSPI(uint8_t bajt)
{
	SPDR = bajt;

	// czekamy na ustawienie flagi SPIF po zakończeniu transmisji
	while( !(SPSR & (1<<SPIF)));

	return SPDR;
}

int main()
{

}
