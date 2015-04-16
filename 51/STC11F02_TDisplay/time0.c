#include "time0.h"

volatile unsigned long microSecond;

void TIME0_ISR() interrupt 1 using 1
{
	microSecond++;
}

void TIME0_Init(void)	//1΢��@12.000MHz
{
	microSecond = 0;
	
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x02;		//���ö�ʱ��ģʽ
	TL0 = 0xF4;			//���ö�ʱ��ֵ
	TH0 = 0xF4;			//���ö�ʱ����ֵ
	TF0 = 0;			//���TF0��־
	TR0 = 1;			//��ʱ��0��ʼ��ʱ
}

//unsigned long TIME0_GetCurrentMicroSecond(void)
//{
//	return microSecond;
//}
