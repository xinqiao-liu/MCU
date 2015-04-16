#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <STC89C5xRC.h>
#include <intrins.h>

sbit     DQ = P3^7;			//ÎÂ¶ÈÊäÈë¿Ú

void DS18B20_Init(void);
void DS18B20_Reset(void);
void DS18B20_WriteByte(unsigned char byte);
unsigned char DS18B20_ReadByte(void);
unsigned int DS18B20_ReadTemperature(void);
void DS18B20_ConvTemperature(unsigned int value);

#endif