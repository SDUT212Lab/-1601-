#include "TIM.h"

void BASE_TIM_NVIC_INIT()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	//1.�����ж���
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
�ʼǣ�
	1.������ʱ����ֻ�ܼ�ʱ�����Դ����жϻ��ߴ���DMA����TIM67
	����ʱ��ļ��㣺500ms PSC= 72-1	ARR = 999
	
	2.ͨ�ö�ʱ����������������Ƶ�ʣ������Ⱥ����PWM����ĳ���
	3.�߼���ʱ��

**/
