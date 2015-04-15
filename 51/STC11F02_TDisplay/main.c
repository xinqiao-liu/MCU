#include <STC89C5xRC.h>

volatile unsigned long microSecond;
	
void Timer0Init(void);
void UartInit(void);
void SendData(unsigned char byte);
void SendString(unsigned char *str);

void main()
{
	microSecond = 0;
	
	Timer0Init();
	UartInit();
	SendString("STC11F02 TDisplay.\r\n");
	while(1)
	{
	}
}

void Timer0Init(void)	//1微秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x02;		//设置定时器模式
	TL0 = 0xF4;			//设置定时初值
	TH0 = 0xF4;			//设置定时重载值
	TF0 = 0;			//清除TF0标志
	TR0 = 1;			//定时器0开始计时
}

void Timer0_Isr() interrupt 1 using 1
{
	microSecond++;
}

void UartInit(void)		//9600bps@12.000MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xD9;			//设定定时初值
	TH1 = 0xD9;			//设定定时器重装值
	//ET1 = 0;			//禁止定时器1中断
	TR1 = 1;			//启动定时器1
	ES = 1;
	EA = 1;
}

void Uart_Isr() interrupt 4 using 2
{
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
		SendData(SBUF);
    }
}

void SendData(unsigned char byte)
{
	SBUF = byte;   
    while(TI == 0);   
    TI = 0;
}

void SendString(unsigned char *str)
{
    while(*str) SendData(*str++);
}
