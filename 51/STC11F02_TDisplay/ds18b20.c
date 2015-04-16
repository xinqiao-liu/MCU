#include "ds18b20.h"
#include "delay.h"

//��ʼ��
void DS18B20_Init(void)
{
	DS18B20_Reset();       		// ������ת��һ��
	DS18B20_WriteByte(0xCC); 	// Skip ROM
	DS18B20_WriteByte(0x44); 	// ��ת������
}

//����
void DS18B20_Reset(void)
{
	char presence=1;
	while(presence)
	{
		while(presence)
		{
			DQ = 1;_nop_();_nop_();
			DQ = 0;    //
			delay_us(550); 		// 550us
			DQ = 1;    // 
			delay_us(70); 		// 66us
			presence = DQ; 		// presence=0������һ��
		}
		delay_us(500);    		//��ʱ500us
		presence = ~DQ;
	}
	DQ=1;
} 

//дһ���ֽ�
void DS18B20_WriteByte(unsigned char byte)
{
	unsigned char i;
	for (i = 8; i > 0; i--) //
	{
		DQ = 1;_nop_();_nop_(); 
		DQ = 0;_nop_();_nop_();_nop_();_nop_();_nop_();//5us
		DQ = byte & 0x01;      	//���λ�Ƴ�
		delay_us(70);           //66us
		byte = byte / 2;      	//����һλ
	}
	DQ = 1;
	delay_us(10); 

}

//��һ���ֽ�
unsigned char DS18B20_ReadByte(void)
{
	unsigned char i;
	unsigned char value = 0;
	for (i = 8; i > 0; i--)
	{
		DQ = 1;_nop_();_nop_();
		value >>= 1;
		DQ = 0;_nop_();_nop_();_nop_();_nop_();   //4us
		DQ = 1;_nop_();_nop_();_nop_();_nop_();   //4us 
		if(DQ)
			value |= 0x80;
		delay_us(70);           //66us
	}
	DQ = 1;
	return(value);
}

//��ȡ�¶�
unsigned int DS18B20_ReadTemperature(void)
{
	unsigned int t;
	unsigned char temp_data[2]={0x00,0x00};
	
	DS18B20_Reset();       				//���߸�λ
	DS18B20_WriteByte(0xCC); 			// ��Skip ROM����
	DS18B20_WriteByte(0xBE); 			// ��������
	
	temp_data[0] = DS18B20_ReadByte(); //�¶ȵ�8λ
	temp_data[1] = DS18B20_ReadByte(); //�¶ȸ�8λ
	t = temp_data[1];
	t = t << 8;
	t = temp_data[0];

	DS18B20_Reset();
	DS18B20_WriteByte(0xCC); 			// Skip ROM
	DS18B20_WriteByte(0x44); 			// ��ת������
	
	return t;
}

//ת���¶�
void DS18B20_ConvTemperature(unsigned int value)
{
//	uchar n=0;
//	uchar doth,dotl;
//	uchar flag, flag3=1,flag2=1;       //������ʾ�������
//	
//	if((temp_data[1]&0xf8)!=0x00)
//	{
//		temp_data[1]=~(temp_data[1]);
//		temp_data[0]=~(temp_data[0])+1;
//		n=1;
//		flag=1;
//	}//���¶�����

//	if(temp_data[0]>255)
//	{
//		temp_data[1]++; 
//	}

//	display[4]=temp_data[0]&0x0f;
//	display[0]=ditab[display[4]];
//	doth=display[0]/10;
//	dotl=display[0]%10;
//	display[4]=((temp_data[0]&0xf0)>>4)|((temp_data[1]&0x07)<<4);
//	display[3]=display[4]/100;
//	display[2]=display[4]/10%10;
//	display[1]=display[4]%10;
//	if(!display[3])
//	{
//		display[3]=0x0a;
//		flag3=0;
//		if(!display[2])
//		{
//			display[2]=0x0a;
//			flag2=0;
//		}
//	}//���λΪ0ʱ������ʾ
//	
//	if(n)
//	{
//		display[3]=0x0b;//���¶�ʱ���λ��ʾ"-"
//		flag3=0;
//	}
}