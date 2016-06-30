/*
 * spi.h
 *
 *  Created on: 28-03-2016
 *      Author: psm11
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define MOSI PB5
#define SCK PB7
#define SS PB4

//miso jest zdefiniowane w nocie katalogowej atmega 32 jako pb6

void InitSPI(void);
uint8_t TransferSPI(uint8_t);

#endif /* SPI_H_ */
