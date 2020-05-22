#ifndef _USER_ESP8266_H
#define _USER_ESP8266_H
#include "stm32f10x.h"
/*宏定义*/
#define ESP8266_USART			USART2

/*函数定义*/
void ESP8266_Unvarnished_Transmission(void);
void ESP8266_Init(void);
void ESP8266_SendCommand(uint8_t *commad_str);
void ESP8266_GetTimestamp(char *str);
uint32_t ESP8266_Get_Time(void);

#endif
