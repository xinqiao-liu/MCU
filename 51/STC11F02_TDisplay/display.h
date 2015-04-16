#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <STC89C5xRC.h>

#define DIS_DATA P1				//段码输出口
#define DIS_SCAN P3				//扫描口

sbit    DIS_DIAN = P1^0;		//LED小数点控制

void DISPLAY_Init(void);
void DISPLAY_Scan(unsigned char *display);

#endif