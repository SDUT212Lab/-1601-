#ifndef _USER_VELOCITY_H
#define _USER_VELOCITY_H
/*headfile*/
#include "stm32f10x.h"
/*const define*/
#define						ADVANCE_TIM										TIM1
#define 					ADVANCE_TIM_CLKCMD						RCC_APB2PeriphClockCmd
#define						ADVANCE_TIM_CLK								RCC_APB2Periph_TIM1
#define						ADVANCE_TIM_Period						(4000-1)
#define 					ADVANCE_TIM_Prescaler					(72-1)


//中断相关
#define						ADVANCE_TIM_IRQ								TIM1_CC_IRQn
#define 					ADVANCE_TIM_IRQHandler				TIM1_CC_IRQHandler

//TIM1输入捕获通道
#define						ADVANCE_TIM_CH1_GPIO_CLK			RCC_APB2Periph_GPIOA
#define						ADVANCE_TIM_CH1_PORT					GPIOA
#define 					ADVANCE_TIM_CH1_PIN						GPIO_Pin_8
#define						ADVANCE_TIM_IC1PWM_CHANNEL		TIM_Channel_1


void ADVANCE_TIM_Init(void);

#endif

