#ifndef _BLUE_TOOTH_H
#define _BLUE_TOOTH_H

#include "stm32f10x.h"
#define 	_USART_1	1
#define		_USART_2	0

#if _USART_1 

#define	 	USART_x										USART1
#define 	USART_BuadRate_x					9600
#define 	USART_CLKCMD_x						RCC_APB2PeriphClockCmd
#define 	USART_CLK_x								RCC_APB2Periph_USART1
#define 	Blue_Tooth_IRQHandler_x 	USART1_IRQHandler 

#define 	RX_CLKCMD_x								RCC_APB2PeriphClockCmd
#define 	RX_CLK_x									RCC_APB2Periph_GPIOA
#define 	RX_PORT_x									GPIOA
#define 	RX_PIN_x									GPIO_Pin_10

#define 	TX_CLKCMD_x								RCC_APB2PeriphClockCmd
#define 	TX_CLK_x									RCC_APB2Periph_GPIOA
#define 	TX_PORT_x									GPIOA
#define 	TX_PIN_x									GPIO_Pin_9

#endif
#if _USART_2

#define	 	USART_x										USART2
#define 	USART_BuadRate_x					9600
#define 	USART_CLKCMD_x						RCC_APB1PeriphClockCmd
#define 	USART_CLK_x								RCC_APB1Periph_USART2
#define 	Blue_Tooth_IRQHandler_x 	USART1_IRQHandler 

#define 	RX_CLKCMD_x								RCC_APB2PeriphClockCmd
#define 	RX_CLK_x									RCC_APB2Periph_GPIOA
#define 	RX_PORT_x									GPIOA
#define 	RX_PIN_x									GPIO_Pin_3

#define 	TX_CLKCMD_x								RCC_APB2PeriphClockCmd
#define 	TX_CLK_x									RCC_APB2Periph_GPIOA
#define 	TX_PORT_x									GPIOA
#define 	TX_PIN_x									GPIO_Pin_2

#endif



void Blue_Tooth_Init(void);

#endif
