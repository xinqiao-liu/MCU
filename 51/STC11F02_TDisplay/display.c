#include "display.h"
#include "delay.h"

//**************�¶�С�������ò��***********//
unsigned char code ditab[16] = {0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x04,0x05,0x06,0x06,0x07,0x08,0x08,0x09,0x09};
unsigned char code dis_7[12]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf};
//����LED�����        "0"  "1"  "2"  "3"  "4"  "5"  "6"  "7"  "8"  "9" "����" "-"      
unsigned char code scan_con[4]={0x7f,0xbf,0xdf,0xef};    //��ɨ�������

unsigned char display[5]={0x00,0x00,0x00,0x00,0x00};     //��ʾ��Ԫ���ݣ���4�����ݺ�һ����������

void DISPLAY_Init(void)
{
	DIS_DATA = 0xff;    //��ʼ���˿�
	DIS_SCAN = 0xff;
	//for(h = 0; h<4;h++){display[h]=8;}//������ʾ8888
	//	for(h=0;h<500;h++)
	//		{scan();}          //������ʾ"8888"2��
}

void DISPLAY_Scan(unsigned char *display)
{
//char k;
//    for(k=0;k<4;k++)         //��λLEDɨ�����
//     {
//	 DIS_DATA=0xff;
//      DIS_DATA=dis_7[display[k]];
//      if(k==1){DIN=0;}
//      DIS_SCAN=scan_con[k];delay(90);
//	  DIS_SCAN=0xff;
//     }
}
