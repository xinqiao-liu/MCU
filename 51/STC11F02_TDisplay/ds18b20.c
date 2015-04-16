#include "ds18b20.h"
#include "delay.h"

//初始化
void DS18B20_Init(void)
{
	DS18B20_Reset();       		// 开机先转换一次
	DS18B20_WriteByte(0xCC); 	// Skip ROM
	DS18B20_WriteByte(0x44); 	// 发转换命令
}

//重置
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
			presence = DQ; 		// presence=0继续下一步
		}
		delay_us(500);    		//延时500us
		presence = ~DQ;
	}
	DQ=1;
} 

//写一个字节
void DS18B20_WriteByte(unsigned char byte)
{
	unsigned char i;
	for (i = 8; i > 0; i--) //
	{
		DQ = 1;_nop_();_nop_(); 
		DQ = 0;_nop_();_nop_();_nop_();_nop_();_nop_();//5us
		DQ = byte & 0x01;      	//最低位移出
		delay_us(70);           //66us
		byte = byte / 2;      	//右移一位
	}
	DQ = 1;
	delay_us(10); 

}

//读一个字节
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

//读取温度
unsigned int DS18B20_ReadTemperature(void)
{
	unsigned int t;
	unsigned char temp_data[2]={0x00,0x00};
	
	DS18B20_Reset();       				//总线复位
	DS18B20_WriteByte(0xCC); 			// 发Skip ROM命令
	DS18B20_WriteByte(0xBE); 			// 发读命令
	
	temp_data[0] = DS18B20_ReadByte(); //温度低8位
	temp_data[1] = DS18B20_ReadByte(); //温度高8位
	t = temp_data[1];
	t = t << 8;
	t = temp_data[0];

	DS18B20_Reset();
	DS18B20_WriteByte(0xCC); 			// Skip ROM
	DS18B20_WriteByte(0x44); 			// 发转换命令
	
	return t;
}

//转换温度
void DS18B20_ConvTemperature(unsigned int value)
{
//	uchar n=0;
//	uchar doth,dotl;
//	uchar flag, flag3=1,flag2=1;       //数字显示修正标记
//	
//	if((temp_data[1]&0xf8)!=0x00)
//	{
//		temp_data[1]=~(temp_data[1]);
//		temp_data[0]=~(temp_data[0])+1;
//		n=1;
//		flag=1;
//	}//负温度求补码

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
//	}//最高位为0时都不显示
//	
//	if(n)
//	{
//		display[3]=0x0b;//负温度时最高位显示"-"
//		flag3=0;
//	}
}