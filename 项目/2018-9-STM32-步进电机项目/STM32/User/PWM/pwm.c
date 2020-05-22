#include "pwm.h"

void PWM_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PWM_CH1CLKCMD(PWM_CH1CLK,ENABLE);	
	GPIO_InitStruct.GPIO_Pin = PWM_CH1PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_CH1PORT,&GPIO_InitStruct);
	
	PWM_CH2CLKCMD(PWM_CH2CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = PWM_CH2PIN;
	GPIO_Init(PWM_CH2PORT,&GPIO_InitStruct);
}

void PWM_TIM_Mode_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	GENERAL_TIMCLKCMD(GENERAL_TIMCLK,ENABLE);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = GENERAL_TIMPeriod;
	TIM_TimeBaseInitStruct.TIM_Prescaler = GENERAL_TIMPrescaler;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(GENERAL_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = PWM_CH1_H_Time;
	
	TIM_OC1Init(GENERAL_TIM,&TIM_OCInitStruct);
	TIM_OC1PreloadConfig(GENERAL_TIM,TIM_OCPreload_Enable);
	
	TIM_OCInitStruct.TIM_Pulse = PWM_CH2_H_Time;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OC2Init(GENERAL_TIM,&TIM_OCInitStruct);
	TIM_OC2PreloadConfig(GENERAL_TIM,TIM_OCPreload_Enable);
	
	TIM_Cmd(GENERAL_TIM,ENABLE);
	
}

void PWM_Init()
{
	
	PWM_GPIO_Init();
	PWM_TIM_Mode_Init();
}
