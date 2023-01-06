#ifndef _74hc595_H
#define _74hc595_H

#include <regx52.h>
sbit SR = P3^4;
sbit RCK = P3^5;
sbit SCK = P3^6;

void _74HC595_init(); // 595串转并初始化
void _74HC595_write_byte(unsigned char byte);

#endif

