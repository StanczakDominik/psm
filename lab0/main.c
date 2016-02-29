/*
 * main.c
 *
 *  Created on: 29-02-2016
 *      Author: psm11
 */


#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	//czy pin z danego portu jest wejście\wyjście?
	DDRA = 0xFF; //data direction register A - 4 jedynki, 4 jedynki
	// ^ pójście na skróty, ustawiamy wszystkie na wyjście
	// 0b11111111 = 0xFF = 255

	//aby ustawić wszystkie na on:
	//PORTA = 0x00; //diody mają z drugiej strony high, trzeba ustawić low by była różnica napięć

	while(1)
	{
		PORTA = 0xFF;
        _delay_ms(50);
        PORTA = 0x00;
        _delay_ms(50);

	} //czekaj po zakończeniu programu
}
