#ifndef _USER_DC_DUOJI_H
#define _USER_DC_DUOJI_H

#include "stm32f10x.h"

//电机1的相关端口
/**************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当需要哪个定时器的时候，只需要把下面的宏定义改成1即可





#define            DUOJI1_TIM                   TIM4
#define            DUOJI1_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            DUOJI1_TIM_CLK               RCC_APB1Periph_TIM4
#define            DUOJI1_TIM_Period            (10-1)
#define            DUOJI1_TIM_Prescaler         71
#define            DUOJI1_TIM_IRQ               TIM4_IRQn
#define            DUOJI1_TIM_IRQHandler        TIM4_IRQHandler



/**************************函数声明********************************/
void DUOJI_Init(void);
void DUOJI1_Speed(uint16_t speed);
void DUOJI2_Speed(uint16_t speed);
#endif
