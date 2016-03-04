/*
 * main.c
 *
 *  Created on: 04-03-2016
 *      Author: psm11
 */


#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	//czy pin z danego portu jest wejście\wyjście?
	DDRC = 0xFF; //data direction register A - 4 jedynki, 4 jedynki
	// ^ pójście na skróty, ustawiamy wszystkie na wyjście
	// 0b11111111 = 0xFF = 255

	//aby ustawić wszystkie na on:
	//PORTA = 0x00; //diody mają z drugiej strony high, trzeba ustawić low by była różnica napięć
	DDRD = 0x00;
	PORTC = 0b01101000;

	while(1)
	{
		if (!(PIND & (1<<PD0))) //pind - odczyt ze switcha
		{
			PORTC = 0b01101000; //zapis na wyjście C
		}
		else
		{
			PORTC = ~0b01101000;
		}
	}
//	while(1)
//	{
//		PORTA = 0xFF;
//        _delay_ms(50);
//        PORTA = 0x00;
//        _delay_ms(50);
//
//	} //czekaj po zakończeniu programu
}
