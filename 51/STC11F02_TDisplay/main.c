#include <STC89C5xRC.h>
#include "delay.h"
#include "ds18b20.h"
#include "uart.h"
#include "time0.h"
#include "display.h"

void main()
{
	DS18B20_Init();
	UART_Init();
	TIME0_Init();
	DISPLAY_Init();
	
	UART_SendString("STC11F02 TDisplay.\r\n");
	while(1)
	{
		//����18B20�¶Ȳ�ת���¶�1����
		DS18B20_ConvTemperature(DS18B20_ReadTemperature());
		DISPLAY_Scan();
	}
}
