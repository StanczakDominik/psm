/*
 * i2c.c
 *
 *  Created on: 01-05-2016
 *      Author: psm11
 */
#include "i2c.h"

// procedura transmisji sygnału START
void i2c_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

// procedura transmisji sygnału STOP
void i2c_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while ((TWCR & (1<<TWSTO)));
}

// procedura transmisji bajtu danych
void i2c_write(uint8_t bajt)
{
	TWDR = bajt;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

//procedura odczytu bajtu danych
uint8_t i2c_read(uint8_t ack)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

void i2c_init(void)
{
	TWBR = 47;
}
