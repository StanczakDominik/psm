/*
 * ow.h
 *
 *  Created on: 03-05-2016
 *      Author: psm11
 */

#ifndef OW_H_
#define OW_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#define OW_PIN PB3
#define OW_DIR DDRB
#define OW_OUT PORTB
#define OW_IN PINB

#define delA 6
#define delB 64
#define delC 60
#define delD 10
#define delE 9
#define delF 55
#define delG 0
#define delH 480
#define delI 70
#define delJ 410

#define OW_low OW_DIR |= 1 << OW_PIN
#define OW_high OW_DIR &= ~(1 << OW_PIN)
#define OW_check (OW_IN & ( 1 << OW_PIN))

uint8_t OW_reset(void);
//1 jak cos jest
//0 jak nic nie ma
void OW_send(uint8_t bit);
uint8_t OW_recv(void);


void OW_send_byte(uint8_t byte);
uint8_t OW_read_byte(void);
//drive bus low: ow low
//release bus: ow high
//sample bus: ow check
#endif /* OW_H_ */
