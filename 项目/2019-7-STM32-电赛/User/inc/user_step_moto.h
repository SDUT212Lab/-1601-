#ifndef _USER_STEP_MOTO_H
#define _USER_STEP_MOTO_H

#include "stm32f10x.h"

/**************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当需要哪个定时器的时候，只需要把下面的宏定义改成1即可
#define STEP_TIM2    1
#define STEP_TIM3    0
#define STEP_TIM4    0
#define STEP_TIM5    0

#if  STEP_TIM2
#define            STEP_TIM                   TIM2
#define            STEP_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            STEP_TIM_CLK               RCC_APB1Periph_TIM2
#define            STEP_TIM_Period            (1000-1)
#define            STEP_TIM_Prescaler         71
#define            STEP_TIM_IRQ               TIM2_IRQn
#define            STEP_TIM_IRQHandler        TIM2_IRQHandler

#elif  STEP_TIM3
#define            STEP_TIM                   TIM3
#define            STEP_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            STEP_TIM_CLK               RCC_APB1Periph_TIM3
#define            STEP_TIM_Period            (1000-1)
#define            STEP_TIM_Prescaler         71
#define            STEP_TIM_IRQ               TIM3_IRQn
#define            STEP_TIM_IRQHandler        TIM3_IRQHandler

#elif   STEP_TIM4
#define            STEP_TIM                   TIM4
#define            STEP_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            STEP_TIM_CLK               RCC_APB1Periph_TIM4
#define            STEP_TIM_Period            (1000-1)
#define            STEP_TIM_Prescaler         71
#define            STEP_TIM_IRQ               TIM4_IRQn
#define            STEP_TIM_IRQHandler        TIM4_IRQHandler

#elif   STEP_TIM5
#define            STEP_TIM                   TIM5
#define            STEP_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            STEP_TIM_CLK               RCC_APB1Periph_TIM5
#define            STEP_TIM_Period            (1000-1)
#define            STEP_TIM_Prescaler         71
#define            STEP_TIM_IRQ               TIM5_IRQn
#define            STEP_TIM_IRQHandler        TIM5_IRQHandler

#endif

#define						STEP_MOTO_CLKCMD						RCC_APB2PeriphClockCmd
#define						STEP_MOTO_CLK								RCC_APB2Periph_GPIOA
#define						STEP_MOTO_PORT							GPIOA
#define						STEP_MOTO_PIN								GPIO_Pin_0
#define 					STEP_OFF										GPIO_ResetBits(STEP_MOTO_PORT,STEP_MOTO_PIN)
#define 					STEP_ON											GPIO_SetBits(STEP_MOTO_PORT,STEP_MOTO_PIN)
/**************************函数声明********************************/

void STEP_TIM_Init(void);
void STEP_Init(void);
void STEP_Set_Angle(uint16_t angle);


#endif	/* __BSP_STEPTIME_H */


