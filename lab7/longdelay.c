/*
 * longdelay.c
 *
 *  Created on: 04-03-2016
 *      Author: psm11
 */

#include "longdelay.h"
void longdelay(uint16_t time_ms)
{
	for(uint16_t i = 0; i<time_ms; i++)
		_delay_ms(1);
}
