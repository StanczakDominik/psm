/*
 * main.c
 *
 *  Created on: 25-04-2016
 *      Author: psm11
 */

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "longdelay.h"
#include <string.h>

/*
generacja sygnalu PWM
nota: 16-bit timer/counter1
fast PWM - jedno zbocze
kontrastem dla niego jest "wolny" PWM - trójkąt typu tent, dokładny na fazie

OC1x czyszczona gdy TCNT1 == OCR1x

rejestr ICR1 definiuje rozdzielczość poprzez maksymalną wartość
musimy tą wykorzystać bo mamy mieć variable pulse period

OCR1a: jak licznik do niej doliczy, ustawia OC1a
OC1a: high w zero, low w OCR1a
tryb 14: fast pwm
* top icr1
* update of ocr1x on bottom
* tov1 flag set on top
wszystko można równolegle zrobić, tym samym timerem, na OC1b

dla preskalera 8 -> TOP = 27648


COM1A1 = 1, COM1A0 = 0 - Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM,

tryb 14:
(non-inverting mode)
WGM13 1
WGM12 1

(rejest TCCR1B)
(te dwa siedzą w drugim rejestrze, B)
WGM11 1
WGM10 0


preskaler:
* cs12 0
* cs11 1
* cs10 0


w while:
	* 27647 - 20
	  x - 0.9
	  ->
	  OCR1A
	* odczekać
	* to samo z x

oc1a - nóżka wyjściowa
*/
void init_pwm_registers()
{
	/*servo setup:
	czarny masa
	czerwony vtg zasilanie
	zolty (control) pd5
	*/

	//TCCR1A
	//COM1A1 = 1, COM1A0 = 0 - Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM,
	//	WGM13 1				work mode 14
	//	WGM12 1
	TCCR1A |= (1<<COM1A1) | (1 << WGM11);
	TCCR1A &=~ ((1<<COM1A0) | (1<<WGM10));

	//TCCR1B
	//WGM11 1				work mode 14
	//WGM10 0
	//CS12 0, CS11 1, CS10 0: prescaler x8
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11);
	TCCR1B &=~ ((1<<CS12) | (1<<CS10));

	//ICR1: set to TOP
	ICR1 = 27647;

	//nozka wyjsciowa na PD5
	DDRD |= (1<<PD5);
}

int convert_to_ocr1a(float x)
{
	//x: time in miliseconds
	int OCR1A_value = x*27647/20;
	return OCR1A_value;
	//OC1a pin is PD5
}

int angle_to_ocr1a(float angle_degrees)
{
	//angle_degrees from 0 to 90
	float time = 0.9 + angle_degrees/90.0f * (2.1-0.9);
	return convert_to_ocr1a(time);
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
		int kat = atoi((char*)bufor);
		OCR1A = angle_to_ocr1a(kat);
		USART_Transmit('-');
		USART_Transmit('\n');
		i=0;
	}
	else
	{
		i++;
	}
}

void rotate_90_degrees()
{
	init_pwm_registers();
	while(1)
	{
		OCR1A = angle_to_ocr1a(0);
		longdelay(1000);
		OCR1A = angle_to_ocr1a(90);
		longdelay(1000);
	}
}

void drive_via_console()
{
	/*
	usart setup:
	xcd -> pd0
	txd -> pd1
	*/
	init_pwm_registers();
	sei();
	DDRD |= (1<<PD1);
	DDRD &=~ (1<<PD0);
	USART_Init(5);
	while(1)
	{

	}
}

void led_pwm()
{
	init_pwm_registers();
	DDRD |= (1<<PD0);
	while(1)
	{

	}
}

int main()
{
	drive_via_console();
}
