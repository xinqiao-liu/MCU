#include <STC12C5A60S2.H>

void SendData(unsigned char byte);
void SendString(unsigned char *str);

void UartInit(void);
void Timer0Init(void);
void Timer1Init(void);

volatile unsigned char servo = 0;
volatile unsigned char PV[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
volatile unsigned char PT[32] = {0,0,0,0,0,0,0,0,10,15,20,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
void main()
{
	P0M0 = 0xFF;		//设置所有IO口强推挽输出
	P1M0 = 0xFF;
	P2M0 = 0xFF;
	P3M0 = 0xFC;

	UartInit();
	Timer0Init();
	Timer1Init();
	EA = 1;
	
	SendString("32Servo!\r\n");
	while(1){};
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

void UartInit(void)		//115200bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0xFD;			//设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	ES = 0x01;
}

void Timer0Init(void)	//20毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;			//设置定时初值
	TH0 = 0xB8;			//设置定时初值
	TF0 = 0;			//清除TF0标志
	TR0 = 1;			//定时器0开始计时
	ET0 = 1;
}

void Timer1Init(void)	//100微秒@11.0592MHz
{	
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xA4;			//设置定时初值
	TH1 = 0xA4;			//设置定时重载值
	TF1 = 0;			//清除TF1标志
	TR1 = 1;			//定时器1开始计时
	ET1 = 1;
}

void tm0_isr() interrupt 1 using 1
{
	TL0 = 0x00;			//设置定时初值
	TH0 = 0xB8;			//设置定时初值

	PV[0] = 0;
	PV[1] = 0;
	PV[2] = 0;
	PV[3] = 0;
	PV[4] = 0;
	PV[5] = 0;
	PV[6] = 0;
	PV[7] = 0;
	PV[8] = 0;
	PV[9] = 0;
	PV[10] = 0;
	PV[11] = 0;
	PV[12] = 0;
	PV[13] = 0;
	PV[14] = 0;
	PV[15] = 0;
	PV[16] = 0;
	PV[17] = 0;
	PV[18] = 0;
	PV[19] = 0;
	PV[20] = 0;
	PV[21] = 0;
	PV[22] = 0;
	PV[23] = 0;
//	PV[24] = 0;
//	PV[25] = 0;
	PV[26] = 0;
	PV[27] = 0;
	PV[28] = 0;
	PV[29] = 0;
	PV[30] = 0;
	PV[31] = 0;
}

void tm1_isr() interrupt 3 using 2
{
	P00 = (PV[0]++ >= PT[0]) ? 0 : 1;
	P01 = (PV[1]++ >= PT[1]) ? 0 : 1;
	P02 = (PV[2]++ >= PT[2]) ? 0 : 1;
	P03 = (PV[3]++ >= PT[3]) ? 0 : 1;
	P04 = (PV[4]++ >= PT[4]) ? 0 : 1;
	P05 = (PV[5]++ >= PT[5]) ? 0 : 1;
	P06 = (PV[6]++ >= PT[6]) ? 0 : 1;
	P07 = (PV[7]++ >= PT[7]) ? 0 : 1;
	
	P10 = (PV[8]++ >= PT[8]) ? 0 : 1;
	P11 = (PV[9]++ >= PT[9]) ? 0 : 1;
	P12 = (PV[10]++ >= PT[10]) ? 0 : 1;
	P13 = (PV[11]++ >= PT[11]) ? 0 : 1;
	P14 = (PV[12]++ >= PT[12]) ? 0 : 1;
	P15 = (PV[13]++ >= PT[13]) ? 0 : 1;
	P16 = (PV[14]++ >= PT[14]) ? 0 : 1;
	P17 = (PV[15]++ >= PT[15]) ? 0 : 1;
	
	P20 = (PV[16]++ >= PT[16]) ? 0 : 1;
	P21 = (PV[17]++ >= PT[17]) ? 0 : 1;
	P22 = (PV[18]++ >= PT[18]) ? 0 : 1;
	P23 = (PV[19]++ >= PT[19]) ? 0 : 1;
	P24 = (PV[20]++ >= PT[20]) ? 0 : 1;
	P25 = (PV[21]++ >= PT[21]) ? 0 : 1;
	P26 = (PV[22]++ >= PT[22]) ? 0 : 1;
	P27 = (PV[23]++ >= PT[23]) ? 0 : 1;
	
//	P30 = (PV[24]++ >= PT[24]) ? 0 : 1;
//	P31 = (PV[25]++ >= PT[25]) ? 0 : 1;
	P32 = (PV[26]++ >= PT[26]) ? 0 : 1;
	P33 = (PV[27]++ >= PT[27]) ? 0 : 1;
	P34 = (PV[28]++ >= PT[28]) ? 0 : 1;
	P35 = (PV[29]++ >= PT[29]) ? 0 : 1;
	P36 = (PV[30]++ >= PT[30]) ? 0 : 1;
	P37 = (PV[31]++ >= PT[31]) ? 0 : 1;
}

void Uart_Isr() interrupt 4 using 3
{
	if(RI)   
    {   
        RI = 0;
		if(SBUF&0x80)
			servo = SBUF&0x1F;
		else if(SBUF&0x40)
		{
			switch(SBUF)
			{
				case 0x40: EA = 0; break;
				case 0x41: EA = 1; break;
				default: break;
			}
		}
		//else if(SBUF&0x20){	}
		else
		{
			PT[servo&0x1F] = SBUF;
		}
    }   
}
