#ifndef _GENERAL_TIM_H
#define _GENERAL_TIM_H

#include "stm32f10x.h"


#define GENERAL_TIM2	0
#define GENERAL_TIM3	1
#define GENERAL_TIM4	0
#define GENERAL_TIM5	0

#if GENERAL_TIM2
#define 		GENERAL_TIM					TIM2
#define			GENERAL_TIM_CLKCMD			RCC_APB1PeriphClockCmd
#define			GENERAL_TIM_CLK				RCC_APB1Periph_TIM2
#define 		GENERAL_TIM_PERIOD			(1000-1)//定时1000us
#define 		GENERAL_TIM_PRESCALER		71
#define 		GENERAL_TIM_IRQ				TIM2_IRQn
#define 		GENERAL_TIM_IRQHandler		TIM2_IRQHandler

#elif GENERAL_TIM3
#define 		GENERAL_TIM					TIM3
#define 		GENERAL_TIM_CLKCMD			RCC_APB1PeriphClockCmd
#define 		GENERAL_TIM_CLK				RCC_APB1Periph_TIM3
#define 		GENERAL_TIM_PERIOD			(1000-1)//定时1000us
#define 		GENERAL_TIM_PRESCALER		71
#define 		GENERAL_TIM_IRQ				TIM3_IRQn
#define 		GENERAL_TIM_IRQHandler		TIM3_IRQHandler

#elif GENERAL_TIM4
#define 		GENERAL_TIM					TIM4
#define 		GENERAL_TIM_CLKCMD			RCC_APB1PeriphClockCmd
#define 		GENERAL_TIM_CLK				RCC_APB1Periph_TIM4
#define 		GENERAL_TIM_PERIOD			(1000-1)//定时1000us
#define 		GENERAL_TIM_PRESCALER		71
#define 		GENERAL_TIM_IRQ				TIM4_IRQn
#define 		GENERAL_TIM_IRQHandler		TIM4_IRQHandler

#elif GENERAL_TIM5
#define 		GENERAL_TIM					TIM5
#define 		GENERAL_TIM_CLKCMD			RCC_APB1PeriphClockCmd
#define 		GENERAL_TIM_CLK				RCC_APB1Periph_TIM5
#define 		GENERAL_TIM_PERIOD			(1000-1)//定时1000us
#define 		GENERAL_TIM_PRESCALER		71
#define 		GENERAL_TIM_IRQ				TIM5_IRQn
#define 		GENERAL_TIM_IRQHandler		TIM5_IRQHandler

#endif

void GENERAL_TIM_Init(void);
#endif
