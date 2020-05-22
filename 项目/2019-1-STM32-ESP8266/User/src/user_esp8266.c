#include "user_esp8266.h"
#include "user_usart.h"
#include "user_delay.h"
#include <string.h>
//命令不成功时，此变量的值是0；
//时间
//systemtick
uint32_t esp8266_cnt = 0;
uint32_t esp8266_timestamp = 0;
uint8_t esp8266_receivedata[200];
uint16_t esp8266_count = 0;
/*
*建立透传模式
*什么是透传模式：就是把ESP78266当作一个中间人，传话的，从服务器传话到客户端
*/
void ESP8266_Init()
{
	USART_x_Init(ESP8266_USART,9600);
}
void ESP8266_ClearData()
{
	for(uint16_t i = 0;i<200;i++)
		esp8266_receivedata[i] = '\0';
}
void ESP8266_SendCommand(uint8_t *commad_str)
{
	USART_x_Send_String(ESP8266_USART,commad_str);
}
void ESP8266_Unvarnished_Transmission()
{
	ESP8266_SendCommand("AT+CWMODE=3\r\n");
	delay_ms(50);
	ESP8266_SendCommand("AT+RST\r\n");
	delay_ms(500);
	ESP8266_SendCommand("AT+CWJAP_DEF=\"1234567\",\"1990082525\"\r\n");
	delay_ms(6000);
}
void ESP8266_GetTimestamp(char *str)
{
//	if(strstr(str,"OK")!= NULL)
//		ESP8266_ClearData();
	char *str1 = strstr(str,"\",\"datetime");
	if(str1!= NULL)
	{
		for(uint8_t i = 0;i<10;i++)
		{
			if((*(str1-10+i)>='0' ) && (*(str1-10+i)<= '9'))
			{
				esp8266_timestamp *= 10;
				esp8266_timestamp +=( *(str1-10+i) - '0');
			}
		}
		ESP8266_ClearData();
	}
}
uint32_t ESP8266_Get_Time()
{
	uint16_t i = 0;
	ESP8266_SendCommand("AT+CIPSTART=\"TCP\",\"103.205.4.43\",80\r\n");
	delay_ms(50);
	ESP8266_SendCommand("AT+CIPSEND=200\r\n");
	delay_ms(100);
	ESP8266_SendCommand("GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json\r\n");
	delay_ms(30);
	ESP8266_SendCommand("GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json\r\n");	
	delay_ms(200);
	while(esp8266_timestamp==0) {delay_ms(1); i++; if(i>5000) break;}
	return esp8266_timestamp;
}

