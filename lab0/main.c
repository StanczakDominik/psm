/*
 * main.c
 *
 *  Created on: 29-02-2016
 *      Author: psm11
 */


#include <avr/io.h>

int main(void)
{
	//czy pin z danego portu jest wejście\wyjście?
	DDRA = 0xFF; //data direction register A - 4 jedynki, 4 jedynki
	// ^ pójście na skróty, ustawiamy wszystkie na wyjście
	// 0b11111111 = 0xFF = 255

	PORTA = 0x00; //diody mają z drugiej strony high, trzeba ustawić low by była różnica napięć

	while(1){} //czekaj po zakończeniu programu
}
