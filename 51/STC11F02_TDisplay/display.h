#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <STC89C5xRC.h>

#define DIS_DATA P1				//���������
#define DIS_SCAN P3				//ɨ���

sbit    DIS_DIAN = P1^0;		//LEDС�������

void DISPLAY_Init(void);
void DISPLAY_Scan(unsigned char *display);

#endif