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
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xD9;			//�趨��ʱ��ֵ
	TH1 = 0xD9;			//�趨��ʱ����װֵ
	TR1 = 1;			//������ʱ��1
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
