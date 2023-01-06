#include "public.h"

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}



void timer0_init(u8 h8, u8 l8)
{
	TMOD = TMOD & 0xF0; // 第四位 定时器0
	TMOD = TMOD | 0x01; //定时器0工作模式
	TF0 = 0; // 防止一开始就中断
	
	// TH0 = 64535 / 256; // 0~65535 每隔1us 计数+1  初始64535 为1ms
	// TL0 = 64535 % 256;
	
	TL0 = h8;		//设置定时初值
	TH0 = l8;		//设置定时初值
	
	EA = 1; // EA=1 ET0=1  1000 0010   中断使能，Timer0使能
	ET0 = 1;
	
	PT0 = 0; // Timer0优先级0  当PT0H=0且PT0=0时，定时器0中断为较低优先级中断(优先级0)
	TR0 = 1; // 开始计时
}

