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

int j = 0;
int d = 0;
int s = 0;
int t = 0;

int x = 4;

//ustawione "w tyl"
uint8_t cyfra[10] = {~0b00111111, ~0b00000110, ~0b01011011, ~0b01001111, ~0b01100110,
					 ~0b01101101, ~0b01111101, ~0b00000111, ~0b01111111, ~0b01101111};

ISR(TIMER0_COMP_vect)
{
	x++;
	if(x==8) x = 4;
	PORTA = ~(1<<x);
	if(x==4) PORTC = cyfra[j];
	if(x==5) PORTC = cyfra[d];
	if(x==6) PORTC = cyfra[s];
	if(x==7) PORTC = cyfra[t];
}

ISR(TIMER1_COMPA_vect)
{
	j++;
	if(j>9)
	{
		j=0;
		d++;
	}
	if(d>9)
	{
		d=0;
		s++;
	}
	if(s>9)
	{
		s=0;
		t++;
	}
	if(t>9)
	{
		t=0;
	}
}

int main(void)
{
	DDRC=0xFF; //wyjscie
	DDRA=0xFF; //wyjscie

	sei();

	TCCR0  |= (1<<WGM01) | (1<<CS01) | (1<< CS00);
	TCCR0  &=~ (1<<WGM00) | (1<<CS01);


	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);
	TIMSK |= (1<<OCIE1A) | (1<<OCIE0);
	OCR1A = 10;
	OCR0 = 53;

	while(1)
	{
	}
}



