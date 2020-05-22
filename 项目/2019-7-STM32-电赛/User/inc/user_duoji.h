#ifndef _USER_DC_DUOJI_H
#define _USER_DC_DUOJI_H

#include "stm32f10x.h"

//���1����ض˿�
/**************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ����Ҫ�ĸ���ʱ����ʱ��ֻ��Ҫ������ĺ궨��ĳ�1����





#define            DUOJI1_TIM                   TIM4
#define            DUOJI1_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            DUOJI1_TIM_CLK               RCC_APB1Periph_TIM4
#define            DUOJI1_TIM_Period            (10-1)
#define            DUOJI1_TIM_Prescaler         71
#define            DUOJI1_TIM_IRQ               TIM4_IRQn
#define            DUOJI1_TIM_IRQHandler        TIM4_IRQHandler



/**************************��������********************************/
void DUOJI_Init(void);
void DUOJI1_Speed(uint16_t speed);
void DUOJI2_Speed(uint16_t speed);
#endif
