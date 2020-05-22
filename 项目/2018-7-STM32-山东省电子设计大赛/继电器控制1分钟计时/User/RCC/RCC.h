#ifndef _RCC_H
#define _RCC_H
#include "stm32f10x.h"


/**
*宏定义配置
**/
#define USE_HSE HSE_SetSysClk(RCC_PLLMul_9)
#define USE_HSI HSI_SetSysClk(RCC_PLLMul_9)

/**
*函数配置
**/
void HSE_SetSysClk(uint32_t RCC_PLLMul_x);			//使用HSE外部高速晶振	
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);			//使用内部8M晶振 分频为4*RCC_PLLMul_x _IO是指静态的意思
void MCO_GPIO_Init(void);							//设置GPIOA为输出时钟


#endif
