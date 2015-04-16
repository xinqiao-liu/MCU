#ifndef __UART_H__
#define __UART_H__

#include <STC89C5xRC.h>

void UART_Init(void);
void UART_SendData(unsigned char byte);
void UART_SendString(unsigned char *str);

#endif