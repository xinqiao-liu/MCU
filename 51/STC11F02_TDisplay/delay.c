#include "delay.h"

void delay_us(unsigned int us)		//@12.000MHz
{
	unsigned int i = us * 3;
	while (--i);
}
