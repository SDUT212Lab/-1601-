#ifndef _PWM_H
#define _PWM_H
#include "stm32f10x.h"

#define TIM3_CH1 1
#define TIM3_CH2 1

#define GENERAL_TIM					TIM3
#define GENERAL_TIMCLKCMD			RCC_APB1PeriphClockCmd
#define GENERAL_TIMCLK				RCC_APB1Periph_TIM3
#define GENERAL_TIMPeriod			99 //+1�����õ���������us
#define GENERAL_TIMPrescaler		71 //ʱ�ӷ�Ƶ��

#if TIM3_CH1

//TIM3ͨ�ñȽ�ͨ��1
#define PWM_CH1CLKCMD				RCC_APB2PeriphClockCmd
#define PWM_CH1CLK					RCC_APB2Periph_GPIOA
#define PWM_CH1PORT					GPIOA
#define PWM_CH1PIN					GPIO_Pin_6
#define PWM_CH1_H_Time				50	//�ߵ�ƽʱ��

#endif

#if TIM3_CH2
//TIM3ͨ�ñȽ�ͨ��2
#define PWM_CH2CLKCMD				RCC_APB2PeriphClockCmd
#define PWM_CH2CLK					RCC_APB2Periph_GPIOA
#define PWM_CH2PORT					GPIOA
#define PWM_CH2PIN					GPIO_Pin_7
#define PWM_CH2_H_Time				50	//�ߵ�ƽʱ��

#endif

void PWM_Init(void);
#endif
