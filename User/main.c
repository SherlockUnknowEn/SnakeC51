//#include <regx52.h>
#include "lcd1602.h"
#include "public.h"
#include "game.h"
#include "74hc595.h"
#include <stdlib.h>


// 定时器 10ms
#define TIMER_H0 0xDC
#define TIMER_L0 0x00

static u16 Tcount = 0;


void matrix_on_row(u8 row, u8 col)
{
	_74HC595_write_byte(row);
	P0 = ~col;
	delay_ms(1);
	P0 =0xFF;
}


void show_map()
{
	u8 i;
	u8 map[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // 地图
	create_map(map);
	for (i = 0; i < 8; i++) {
		matrix_on_row(0x80 >> i, map[i]);
	}
}


// 计时器中断函数
void timer0_routine() interrupt 1 {
	
	TH0 = TIMER_H0;
	TL0 = TIMER_L0;
	Tcount++;
	
	if (Tcount >= 50) { // 每隔0.5s 更新map
		Tcount = 0;
		snake_move();
	}
}

u8 keyboard()
{
	u8 i = 0;
	u8 a = 0x80; // 1000 0000
	for (i = 0; i < 4; i++) {
	  P1 = 0xFF;
		// delay_ms(20);
		P1 = P1 & (~a); // 高四位某位为1
		a = a >> 1;
		
//		if (P1_3 == 0) { delay_ms(20); while(P1_3 == 0); delay_ms(20); return 4 * i + 1; }
//		if (P1_2 == 0) { delay_ms(20); while(P1_2 == 0); delay_ms(20); return 4 * i + 2; }
//		if (P1_1 == 0) { delay_ms(20); while(P1_1 == 0); delay_ms(20); return 4 * i + 3; }
//		if (P1_0 == 0) { delay_ms(20); while(P1_0 == 0); delay_ms(20); return 4 * i + 4; }
		if (P1_3 == 0) { return 4 * i + 1; }
		if (P1_2 == 0) { return 4 * i + 2; }
		if (P1_1 == 0) { return 4 * i + 3; }
		if (P1_0 == 0) { return 4 * i + 4; }
	}
	return 99;
}

void light_all()
{
	matrix_on_row(0x80, 0xFF);
	matrix_on_row(0x40, 0xFF);
	matrix_on_row(0x20, 0xFF);
	matrix_on_row(0x10, 0xFF);
	matrix_on_row(0x08, 0xFF);
	matrix_on_row(0x04, 0xFF);
	matrix_on_row(0x02, 0xFF);
	matrix_on_row(0x01, 0xFF);
}

void dir_scan(u8 k)
{
	if (k == 2) {
		change_dir('u');
	} else if (k == 10) {
		change_dir('d');
	} else if (k == 5) {
		change_dir('l');
	} else if (k == 7) {
		change_dir('r');
	}
}

void main()
{
	u8 k;
	_74HC595_init();
	game_init();
	timer0_init(TIMER_H0, TIMER_L0);
	while(1)
	{		
		if (is_game_over()) { 
			light_all();
		} else {
			show_map();
			k = keyboard();
			dir_scan(k);
		}
	}		
	
}

