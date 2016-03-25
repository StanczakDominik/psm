/*
 * main.c
 *
 *  Created on: 25-03-2016
 *      Author: psm11
 */
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

int x = 0;

ISR(TIMER1_COMPA_vect)
{
	if(!(PIND && (1<<PD6)))
		x=1;
	else
		x=0;
}

int main(void)
{
	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);
	TIMSK |= (1<<OCIE1A);
	sei();
	OCR1A=1079;

	DDRD=0x00;   //d wejscie
	PORTD=0xFF;	 //rezystory

	DDRC=0xFF;   //c wyjscie
	while(1)
	{
		if(x==1)
			PORTC = 0xFF; //wlacz diode na c
		else
			PORTC = 0;    //wylacz diode na c
	}
}



