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
		//读出18B20温度并转换温度1数据
		DS18B20_ConvTemperature(DS18B20_ReadTemperature());
		DISPLAY_Scan();
	}
}
