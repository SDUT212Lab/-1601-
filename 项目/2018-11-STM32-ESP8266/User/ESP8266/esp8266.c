#include "esp8266.h"
#include "systick.h"
#include "usart.h"
//extern volatile uint8_t usart_2_receive_data;
void ESP8266_Send_String(uint8_t *str)
{
	USART_x_Send_String(ESP8266_USART,str);
	USART_x_Send_String(ESP8266_USART,"\r\n");
	SysTick_delay_ms(50);
}

void ESP8266_Init()
{
	USART_x_Init(ESP8266_USART);
	ESP8266_Send_String("AT+RST");
	SysTick_delay_ms(1000);
	ESP8266_Send_String("AT");
	ESP8266_Send_String("AT+CIPMODE=1");
	ESP8266_Send_String("AT+CIPMUX=0");
	ESP8266_Send_String("AT+CWMODE=1");
	ESP8266_Send_String("AT+CWJAP=\"TP-LINK_D396\",\"motor214\"");
	SysTick_delay_ms(10000);
	ESP8266_Send_String("AT+CIPSTART=\"TCP\",\"api.lewei50.com\",80");
	SysTick_delay_ms(2000);
	ESP8266_Send_String("AT+CIPSEND");
}

