#ifndef _USART_H
#define _USART_H
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
#include "delay.h"
#include "SYSTICK.h"


#define USART1_CLK RCC_APB2Periph_GPIOA
//函数定义
void USART1_Init(void);
int fputc(int ch,FILE *f);
void USART1_SendByte(uint8_t ch);
void USART1_SendString(char *str);
void USART1_SendTime(void);						//发送时间函数




#endif

