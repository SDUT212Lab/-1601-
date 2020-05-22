#ifndef _BLUE_TOOTH_H
#define _BLUE_TOOTH_H

#include "stm32f10x.h"
#define 	_USART_1	1
#define		_USART_2	1

#if _USART_1 

#define	 	USART_1					USART1
#define 	USART_1_BuadRate		9600
#define 	USART_CLKCMD_1			RCC_APB2PeriphClockCmd
#define 	USART_CLK_1				RCC_APB2Periph_USART1
#define 	Blue_Tooth_IRQHandler_1 USART1_IRQHandler 

#define 	RX_CLKCMD_1				RCC_APB2PeriphClockCmd
#define 	RX_CLK_1				RCC_APB2Periph_GPIOA
#define 	RX_PORT_1				GPIOA
#define 	RX_PIN_1				GPIO_Pin_10

#define 	TX_CLKCMD_1				RCC_APB2PeriphClockCmd
#define 	TX_CLK_1				RCC_APB2Periph_GPIOA
#define 	TX_PORT_1				GPIOA
#define 	TX_PIN_1				GPIO_Pin_9

#endif

#if	_USART_2

#define	 	USART_2					USART2
#define 	USART_BuadRate_2		9600
#define 	USART_CLKCMD_2			RCC_APB1PeriphClockCmd
#define 	USART_CLK_2				RCC_APB1Periph_USART2
#define 	Blue_Tooth_IRQHandler_2 USART2_IRQHandler 

#define 	RX_CLKCMD_2				RCC_APB2PeriphClockCmd
#define 	RX_CLK_2				RCC_APB2Periph_GPIOA
#define 	RX_PORT_2				GPIOA
#define 	RX_PIN_2				GPIO_Pin_3

#define 	TX_CLKCMD_2				RCC_APB2PeriphClockCmd
#define 	TX_CLK_2				RCC_APB2Periph_GPIOA
#define 	TX_PORT_2				GPIOA
#define 	TX_PIN_2				GPIO_Pin_2

#endif

void Blue_Tooth_Init(void);
void USART_Send_String(USART_TypeDef* pUSART,char *str);
#endif
