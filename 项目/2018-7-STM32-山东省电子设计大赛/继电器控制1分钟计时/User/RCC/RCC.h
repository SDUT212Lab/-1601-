#ifndef _RCC_H
#define _RCC_H
#include "stm32f10x.h"


/**
*�궨������
**/
#define USE_HSE HSE_SetSysClk(RCC_PLLMul_9)
#define USE_HSI HSI_SetSysClk(RCC_PLLMul_9)

/**
*��������
**/
void HSE_SetSysClk(uint32_t RCC_PLLMul_x);			//ʹ��HSE�ⲿ���پ���	
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);			//ʹ���ڲ�8M���� ��ƵΪ4*RCC_PLLMul_x _IO��ָ��̬����˼
void MCO_GPIO_Init(void);							//����GPIOAΪ���ʱ��


#endif
