#include "user_dma.h"
/**
*名称：RTC获取系统时间函数
*作者：陈冲
*时间：2018年12月
*版本：1.0
*更新：1.0：无
**/
/*
*变量定义
*/
uint8_t usart_buffer[20]; //数据缓存寄存器
/*
*name:void USART1_RX_DMA_GPIO_Init()
*fun :串口的GPIO 和 DMA使能
*para:void
*ret :void
*/
void USART1_RX_DMA_GPIO_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	USART_InitTypeDef USART_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruct);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	USART_Cmd(USART1,ENABLE);
}
/*
*name:void USART1_RX_DMA_Mode_Init()
*fun :DMA模式初始化
*para:void
*ret :void
*/
void USART_DMA_Mode_Init()
{
		DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//内存是DR
	DMA_InitStruct.DMA_BufferSize = 16;
	//设置数据从哪里来,地址源
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)usart_buffer;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_Init(USART1_RX_DMA,&DMA_InitStruct);
	DMA_Cmd(USART1_RX_DMA,ENABLE);
	DMA_ITConfig(USART1_RX_DMA,DMA_IT_TC,ENABLE);
}
/*
*name:void USART_DMA_Init()
*fun :串口DMA初始化
*para:void
*ret :void
*/
void USART1_RX_DMA_Init()
{
	USART1_RX_DMA_GPIO_Init();
	USART_DMA_Mode_Init();
}



