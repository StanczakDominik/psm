/*
 * spi.c
 *
 *  Created on: 28-03-2016
 *      Author: psm11
 */
#include "spi.h"

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
