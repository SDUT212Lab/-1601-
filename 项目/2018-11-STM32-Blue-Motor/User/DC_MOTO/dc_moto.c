#include "dc_moto.h"
/**
*名称：二驱小车驱动
*作者：陈冲
*时间：2018年8月
*版本：1.0
*更新：无
**/


/**
*name:DC_Moto_GPIO_Init()
*fun :直流电机IO口配置初始化
*para:void
*ret :void
**/
void DC_Moto_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	IN1_CLKCMD(IN1_CLK,ENABLE);
	IN2_CLKCMD(IN2_CLK,ENABLE);
	IN3_CLKCMD(IN3_CLK,ENABLE);
	IN4_CLKCMD(IN4_CLK,ENABLE);
	EN1_CLKCMD(EN1_CLK,ENABLE);
	EN2_CLKCMD(EN1_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = IN1_PIN | IN2_PIN | IN3_PIN | IN4_PIN | EN1_PIN | EN2_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(IN1_PORT,&GPIO_InitStruct);
	GPIO_Init(IN2_PORT,&GPIO_InitStruct);
	GPIO_Init(IN3_PORT,&GPIO_InitStruct);
	GPIO_Init(IN4_PORT,&GPIO_InitStruct);
	GPIO_Init(EN1_PORT,&GPIO_InitStruct);
	GPIO_Init(EN2_PORT,&GPIO_InitStruct);
}
/**
*name:DC_Moto_GPIO_Init()
*fun :直走
*para:void
*ret :void
**/
void DC_Moto_GO()
{
	IN1_L;
	IN2_H;
	IN3_L;
	IN4_H;
}
/**
*name:DC_Moto_Right()
*fun :右转
*para:void
*ret :void
**/
void DC_Moto_Right()
{
	IN1_L;
	IN2_L;
	IN3_L;
	IN4_H;
}
/**
*name:DC_Moto_Left()
*fun :左转
*para:void
*ret :void
**/
void DC_Moto_Left()
{
	IN1_L;
	IN2_H;
	IN3_L;
	IN4_L;
}
/**
*name:DC_Moto_Back()
*fun :后退
*para:void
*ret :void
**/
void DC_Moto_Back()
{
	IN1_H;
	IN2_L;
	IN3_H;
	IN4_L;
}
/**
*name:DC_Moto_Stop()
*fun :停止
*para:void
*ret :void
**/
void DC_Moto_Stop()
{
	IN1_H;
	IN2_H;
	IN3_H;
	IN4_H;
}
/**
*name:PWM_GPIO_Init()
*fun :PWM信号GPIO初始化
*para:void
*ret :void
**/
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
/**
*name:PWM_TIM_Mode_Init(uint16_t speed1,uint16_t speed2)
*fun :PWM模式配置
*para:void
*ret :void
**/
void PWM_TIM_Mode_Init(uint16_t speed1,uint16_t speed2)
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
	TIM_OCInitStruct.TIM_Pulse = speed1;
	
	TIM_OC1Init(GENERAL_TIM,&TIM_OCInitStruct);
	TIM_OC1PreloadConfig(GENERAL_TIM,TIM_OCPreload_Enable);
	
	TIM_OCInitStruct.TIM_Pulse = speed2;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC2Init(GENERAL_TIM,&TIM_OCInitStruct);
	TIM_OC2PreloadConfig(GENERAL_TIM,TIM_OCPreload_Enable);
	
	TIM_Cmd(GENERAL_TIM,ENABLE);
	
}
/**
*name:DC_Moto_Init(uint16_t speed1,uint16_t speed2)
*fun :直流电机初始化
*para:speed1 CH1的速度，speed2 CH2速度
*ret :void
**/
void DC_Moto_Init(uint16_t speed1,uint16_t speed2)
{
	DC_Moto_GPIO_Init();
	PWM_GPIO_Init();
	PWM_TIM_Mode_Init(speed1,speed2);
}
