#include "time0.h"

volatile unsigned long microSecond;

void TIME0_ISR() interrupt 1 using 1
{
	microSecond++;
}

void TIME0_Init(void)	//1微秒@12.000MHz
{
	microSecond = 0;
	
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x02;		//设置定时器模式
	TL0 = 0xF4;			//设置定时初值
	TH0 = 0xF4;			//设置定时重载值
	TF0 = 0;			//清除TF0标志
	TR0 = 1;			//定时器0开始计时
}

//unsigned long TIME0_GetCurrentMicroSecond(void)
//{
//	return microSecond;
//}
