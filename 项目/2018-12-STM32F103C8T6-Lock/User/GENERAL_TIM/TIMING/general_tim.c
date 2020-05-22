#include "general_tim.h"
/**
*名称：通用定时器定时程序
*作者：陈冲
*时间：2018年8月
*版本：1.0
*更新：无
**/

/**
*name:GENERAL_TIM_NVIC_Init();
*fun :定时器配置中断等级
*para:void
*ret :void
**/
static void GENERAL_TIM_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStruct.NVIC_IRQChannel =  GENERAL_TIM_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
/**
*name:GENERAL_TIM_Mode_Init()
*fun :定时器模式配置
*para:void
*ret :void
**/
static void GENERAL_TIM_Mode_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	GENERAL_TIM_CLKCMD(GENERAL_TIM_CLK,ENABLE);
	/*累计Period+1个频率后产生一个更新或者中断*/
	TIM_TimeBaseInitStruct.TIM_Period = GENERAL_TIM_PERIOD;
	/*时钟分频数*/
	TIM_TimeBaseInitStruct.TIM_Prescaler = GENERAL_TIM_PRESCALER;
	/*时钟分频因子*/
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	/*计数模式*/
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	/*重复计时器的值*/
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(GENERAL_TIM,&TIM_TimeBaseInitStruct);
	TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
	TIM_ClearFlag(GENERAL_TIM,TIM_FLAG_Update);
//	TIM_Cmd(GENERAL_TIM,ENABLE);
}
/**
*name:GENERAL_TIM_Init()
*fun :定时器初始化函数
*para:void
*ret :void
**/
void GENERAL_TIM_Init()
{
	GENERAL_TIM_NVIC_Init();
	GENERAL_TIM_Mode_Init();
}
/**
*name:ENERAL_TIM_IRQHandler()
*fun :定时器中断函数，放在stm32f10x_it.c中
*para:void
*ret :void
**/
/*
uint32_t time = 0;
void GENERAL_TIM_IRQHandler()
{
	if(TIM_GetITStatus(GENERAL_TIM,TIM_IT_Update) != RESET)
	{
		time++;
		TIM_ClearITPendingBit(GENERAL_TIM,TIM_FLAG_Update);
	
	}
}
*/

