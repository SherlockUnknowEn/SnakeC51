#include "74hc595.h"

void _74HC595_init()
{
	SCK = 0;
	RCK = 0;
}

void _74HC595_write_byte(unsigned char byte) // 行扫描
{
	unsigned char  i = 0;
	for (i = 0; i < 8; i++) {
		SR = byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}		
	RCK = 1;
	RCK = 0;
}