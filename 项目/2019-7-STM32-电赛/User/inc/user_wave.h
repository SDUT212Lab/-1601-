#ifndef _USER_WAVE_H
#define _USER_WAVE_H


#include "stm32f10x.h"


//这里使用TIM3的
#define							WAVE_TIM									TIM3
#define							WAVE_TIM_CLKCMD						RCC_APB1PeriphClockCmd
#define							WAVE_TIM_CLK							RCC_APB1Periph_TIM3
#define							WAVE_TIM_Channel_Pin			GPIO_Pin_0
#define 						WAVE_TIM_Channel_Port			GPIOB
#define							WAVE_TIM_Channel					TIM_Channel_3
#define							WAVE_TIM_IRQn							TIM3_IRQn
#define							WAVE_TIM_IRQHandler				TIM3_IRQHandler




//GPIO相关
#define							WAVE_GPIO_CLKCMD					RCC_APB2PeriphClockCmd
#define							WAVE_GPIO_CLK							RCC_APB2Periph_GPIOB
#define							WAVE_GPIO_Trigger_Pin			GPIO_Pin_1
#define							WAVE_GPIO_Trigger_Prot		GPIOB

void Wave_Cap_Init(u16 arr,u16 psc);
void Read_Distane(void);

#endif

