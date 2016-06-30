/*
 * main.c
 *
 *  Created on: 29-04-2016
 *      Author: psm11
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "spi.h"


FILE lcd_stream=FDEV_SETUP_STREAM (lcd_putc, NULL, _FDEV_SETUP_WRITE);

void init_timer_registers()
{
	sei();

	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);
	TIMSK |= (1<<OCIE1A) | (1<<OCIE0);
	OCR1A = 691;

	//nozki wejsciowe na PC1, PC2
	DDRC &=~ ((1<<PC1) | (1<<PC2));
	PORTC |= ((1<<PC1) | (1<<PC2));
}



float v_prog = 0.3f;
//obsluga przerwania
uint16_t liczba;
float napiecie_na_ad;


int led_status = 0;

ISR(TIMER1_COMPA_vect)
{
//	lcd_clear();
	lcd_set_xy(0,0);
	fprintf(&lcd_stream, "v_prog: %.3f", v_prog);
	if(!(PINC & (1<<PC1))) //jesli SW0 wlaczony
	{
		v_prog += 0.1f;
	}
	if(!(PINC & (1<<PC2))) //jesli SW1 wlaczony
	{
		v_prog = (v_prog - 0.1f > 0) ? v_prog - 0.1f: 0.0f;
	}

	//czytaj z SPI
	PORTB &=~ (1<<PB4);
	TransferSPI(1);
	uint16_t high = 0b00001111 & TransferSPI(0xA0);
	uint16_t low = TransferSPI(0);
	liczba = (high<<8) | low;
	napiecie_na_ad = (liczba * 5.0 / 4096.0);
	lcd_set_xy(0,1);
	fprintf(&lcd_stream, "v_ad: %.3f", napiecie_na_ad);
	PORTB |= (1<<PB4);

	led_status = (napiecie_na_ad > v_prog) ? 1: 0;
}


void init_led_ports()
{
	DDRC |= 1<<PC0;
}

void switch_led(int i)
{
	if (i == 0)
	{
		PORTC |= 1<<PC0;
		USART_Transmit('-');
	}
	else
	{
		PORTC &=~ (1<<PC0);
		USART_Transmit('+');
	}
}

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

char bufor[20];
int i = 0;

ISR(USART_RXC_vect)
{
	bufor[i] = UDR;
	if(bufor[i]==0x0A)
	{
		v_prog = atof((char*)bufor);
		USART_Transmit('x');
		USART_Transmit('\n');
		i=0;
	}
	else
	{
		i++;
	}
	USART_Transmit('y');
}

int main()
{
	lcdinit();
	InitSPI();

	USART_Init(5);
	init_timer_registers();
	init_led_ports();
	fprintf(&lcd_stream, "liczba: %.3f", v_prog);
	while(1)
	{
		switch_led(led_status);
	}
}
