#ifndef _public_H
#define _public_H

#include "regx52.h"

typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long u32;

void delay_10us(u16 ten_us);
void delay_ms(u16 ms);
void timer0_init(u8 h0, u8 l0);
	
#endif
