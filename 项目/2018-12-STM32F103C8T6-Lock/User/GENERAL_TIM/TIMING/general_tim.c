#include "general_tim.h"
/**
*���ƣ�ͨ�ö�ʱ����ʱ����
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.0
*���£���
**/

/**
*name:GENERAL_TIM_NVIC_Init();
*fun :��ʱ�������жϵȼ�
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
*fun :��ʱ��ģʽ����
*para:void
*ret :void
**/
static void GENERAL_TIM_Mode_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	GENERAL_TIM_CLKCMD(GENERAL_TIM_CLK,ENABLE);
	/*�ۼ�Period+1��Ƶ�ʺ����һ�����»����ж�*/
	TIM_TimeBaseInitStruct.TIM_Period = GENERAL_TIM_PERIOD;
	/*ʱ�ӷ�Ƶ��*/
	TIM_TimeBaseInitStruct.TIM_Prescaler = GENERAL_TIM_PRESCALER;
	/*ʱ�ӷ�Ƶ����*/
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	/*����ģʽ*/
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	/*�ظ���ʱ����ֵ*/
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(GENERAL_TIM,&TIM_TimeBaseInitStruct);
	TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
	TIM_ClearFlag(GENERAL_TIM,TIM_FLAG_Update);
//	TIM_Cmd(GENERAL_TIM,ENABLE);
}
/**
*name:GENERAL_TIM_Init()
*fun :��ʱ����ʼ������
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
*fun :��ʱ���жϺ���������stm32f10x_it.c��
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

