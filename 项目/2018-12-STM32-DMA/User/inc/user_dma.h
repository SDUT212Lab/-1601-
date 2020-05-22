#ifndef _USER_DMA_H
#define _USER_DMA_H
/*头文件*/
#include "stm32f10x.h"

/*使用串口1的接受DMA*/
#define USE_USART1_RX_DMA								1
#if USE_USART1_RX_DMA
	#define USART1_RX_DMA									DMA1_Channel5
	#define USART1_DR_ADDRESS							(USART1_BASE + 0x04)
	void USART1_RX_DMA_Init(void);
	void USART1_RX_DMA_Mode_Init(void);
#endif

#endif

