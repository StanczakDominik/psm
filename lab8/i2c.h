/*
 * i2c.h
 *
 *  Created on: 01-05-2016
 *      Author: psm11
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>

void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t bajt);
uint8_t i2c_read(uint8_t ack);
void i2c_init(void);

#endif /* I2C_H_ */
