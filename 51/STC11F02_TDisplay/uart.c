#include "uart.h"

void UART_ISR() interrupt 4 using 2
{
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
		UART_SendData(SBUF);
    }
}

void UART_Init(void)	//9600bps@12.000MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xD9;			//设定定时初值
	TH1 = 0xD9;			//设定定时器重装值
	TR1 = 1;			//启动定时器1
	ES = 1;
	EA = 1;
}

void UART_SendData(unsigned char byte)
{
	SBUF = byte;   
    while(TI == 0);   
    TI = 0;
}

void UART_SendString(unsigned char *str)
{
    while(*str) UART_SendData(*str++);
}
