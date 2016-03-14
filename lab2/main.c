/*
 * main.c
 *
 *  Created on: 14-03-2016
 *      Author: psm11
 */

#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>

uint8_t x = 0;

ISR(INT0_vect)
{
	x++;
}


/* macro sei(); - set interrupts
 *    ekwiwalent: SREG |= (1<<1);
 * macro cli(); - close interrupts

ALBO POOLING
ALBO PRZERWANIA
 */

int main(void)
{
	sei();

	MCUCR |= (1<< ISC01);
	GICR |= (1<<INT0); //wlaczamy, wylaczamy mozliwosci roznych przerwan

	DDRC = 0xFF;

	DDRD = 0x00;
	PORTD = 0xFF;

	while(1)
	{
		PORTC = ~x;
	}
}
