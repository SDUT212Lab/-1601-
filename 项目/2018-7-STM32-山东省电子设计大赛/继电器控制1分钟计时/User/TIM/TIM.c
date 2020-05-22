#include "TIM.h"

void BASE_TIM_NVIC_INIT()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	//1.设置中断组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}

void TIM6_Init()
{
	TIM_TimeBaseInitTypeDef TIM6_InitStruct;
	
	BASE_TIM_NVIC_INIT();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM6_InitStruct.TIM_Period = 999;
	TIM6_InitStruct.TIM_Prescaler = 71;
	
	TIM_TimeBaseInit(TIM3,&TIM6_InitStruct);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM3,TIM_FLAG_Update,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}
/**
笔记：
	1.基本定时器，只能计时，可以触发中断或者触发DMA请求TIM67
	定是时间的计算：500ms PSC= 72-1	ARR = 999
	
	2.通用定时器，检测输入脉冲的频率，脉冲宽度和输出PWM脉冲的场合
	3.高级定时器

**/
