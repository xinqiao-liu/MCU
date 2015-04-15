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

void Timer0Init(void)	//1΢��@12.000MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x02;		//���ö�ʱ��ģʽ
	TL0 = 0xF4;			//���ö�ʱ��ֵ
	TH0 = 0xF4;			//���ö�ʱ����ֵ
	TF0 = 0;			//���TF0��־
	TR0 = 1;			//��ʱ��0��ʼ��ʱ
}

void Timer0_Isr() interrupt 1 using 1
{
	microSecond++;
}

void UartInit(void)		//9600bps@12.000MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xD9;			//�趨��ʱ��ֵ
	TH1 = 0xD9;			//�趨��ʱ����װֵ
	//ET1 = 0;			//��ֹ��ʱ��1�ж�
	TR1 = 1;			//������ʱ��1
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
