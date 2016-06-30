/*
 * ow.c
 *
 *  Created on: 03-05-2016
 *      Author: psm11
 */

#include "ow.h"

uint8_t OW_reset(void)
{
	uint8_t result;
	_delay_us(delG);
	OW_low;
	_delay_us(delH);
	OW_high;
	_delay_us(delI);
	result = OW_check;
	_delay_us(delJ);
	return result;
}

//1 jak cos jest
//0 jak nic nie ma
void OW_send(uint8_t bit)
{
	if(bit)
	{
		OW_low;
		_delay_us(delA);
		OW_high;
		_delay_us(delB);
	}
	else
	{
		OW_low;
		_delay_us(delC);
		OW_high;
		_delay_us(delD);
	}
}

uint8_t OW_recv(void)
{
	int result;
	OW_low;
	_delay_us(delA);
	OW_high;
	_delay_us(delE);
	result = OW_check;
	_delay_us(delF);

	return result;
}


void OW_send_byte(uint8_t byte)
{
	for (int loop = 0; loop < 8; loop++)
	{
		OW_send(byte & 0x01);
		byte >>= 1;
	}
}
uint8_t OW_read_byte(void)
{
	int result = 0;
	for (int loop = 0; loop < 8; loop++)
	{
		result >>= 1;
		if(OW_recv())
		{
			result |= 0x80;
		}
	}
	return result;
}
