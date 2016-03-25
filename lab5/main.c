/*
 * main.c
 *
 *  Created on: 25-03-2016
 *      Author: psm11
 */

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

// udr - odczyt/zapis danych
// ucsra - usart contral and status register a
	//7. rxc - flaga, gdy dana przychodzi w rxc pojawia się jedynka
		//trzeba coś przeczytać z udr
	//5. udre - data register empty - gdy jedynka, pusty i można pisać
	//4. frame error - obsługa błędów
	//3. dataoverrun - nadpisanie
	//2. parity error
//ucsrb
	//przerwania - jedynkami włączyć
	//rxcie	- gdy pojawiła się jedynka
	//udrie - ustawia się kiedy jest pusty (
	//rxen - receiver enable
	//txen - transmitter enable
	//ucsz2 - character size 2 (konfiguracja rozmiaru ramki)
	//rxb8 - słowo 9bitowe
//ucsrc
	//ursel - register select - dostęp do ucsrc i jeszcze drugiego
	//upm1, upm0 - parzystość - musimy się dostosować do urządzenia
	//usbs - ile jes bitów stopu? 1, 2?

//ubrrL, ubrrH - dane, 2bajt
//165 przykłady ustawień
//146 przyklady kod

void USART_Init( unsigned int baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN) | (1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
		;
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
		;			//ale może czekać i ruski rok na tą daną, lepiej przerwaniem
	/* Get and return received data from buffer */
	return UDR;
}

int led_status = 0;
ISR(INT0_vect)
{
	led_status = 1 - led_status;
}

char bufor[20];
int i = 0;
ISR(USART_RXC_vect)
{
	bufor[i] = UDR;
	if(bufor[i]==0x0A)
	{
		if(!strncmp((char*)bufor, "off", 3))
		{
			USART_Transmit('-');
			USART_Transmit('\n');
			led_status = 0;
		}
		if(!strncmp((char*)bufor, "on", 2))
		{
			USART_Transmit('+');
			USART_Transmit('\n');
			led_status = 1;
		}
		i=0;
	}
	else
	{
		i++;
	}
}

int main()
{
	sei();
//	GICR |= (1<<INT0);
//	MCUCR |= (1<<ISC01);
	DDRC |= (1<<PC0);
	DDRC &=~ (1<<PC1);
	USART_Init(5);
	while(1)
	{
		if(led_status)
		{
			PORTC &=~ (1<<PC0);
		}
		else
		{
			PORTC |= (1<<PC0);
		}
	}
}
