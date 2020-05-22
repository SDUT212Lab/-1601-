#include "user_gpio_interp.h"
/**
*名称：触摸开关驱动
*作者：陈冲
*时间：2018年8月
*版本：1.0
*更新：无
**/

/**
*name:Touch_Key_GPIO_Init()
*fun :触摸开关引脚初始化
*para:void
*ret :void
**/
void Interp_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SIG1_CLKCMD(SIG1_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = SIG1_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(SIG1_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SIG2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(SIG2_PORT,&GPIO_InitStruct);
}
/**
*name:Touch_Key_Read_Bit()
*fun :触摸开关读取状态
*para:void
*ret :有触摸返回1，没有触摸0
**/
uint8_t Interp_Read_Bit()
{
	if(SIG1 == Bit_RESET)
		return 0;
	else 
		return 1;
}
/**
*name:Touch_Key_NVIC_Init()
*fun :触摸开关配置中断优先级
*para:void
*ret :void
**/
static void Interp_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	/*优先级组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/*中断源*/
	NVIC_InitStruct.NVIC_IRQChannel = SIG1_IRQn;
	/*抢占优先级*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	/*子优先级*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =3;
	/*使能通道*/
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = SIG2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4;
	
	NVIC_Init(&NVIC_InitStruct);
}
/**
*name:Touch_Key_EXTI_Init()
*fun :触摸开关配置中断
*para:void
*ret :void
**/
void Interp_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	
	Interp_NVIC_Init();
	/*EXTI信号源*/
	GPIO_EXTILineConfig(SIG1_PORTSOURCE,SIG1_PINSOURCE);
	
	EXTI_InitStruct.EXTI_Line = SIG1_EXTILINE;
	/*EXTI为中断模式*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*中断类型*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	/*使能中断*/
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
	GPIO_EXTILineConfig(SIG2_PORTSOURCE,SIG2_PINSOURCE);
	EXTI_InitStruct.EXTI_Line = SIG2_EXTILINE;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStruct);
}
/**
*name:Touch_Key_Init()
*fun :触摸开关初始化
*para:void
*ret :void
**/
void Interp_Init()
{
	Interp_GPIO_Init();
	Interp_EXTI_Init();
}
/**
*name:Touch_Key_IRQHandler()
*fun :触摸开关中断，放在stm32f10x_it.c中
*para:void
*ret :void
**/
/**
void Interp_IRQHandler()
{
	if(EXTI_GetITStatus(SIG1_EXTILINE) != RESET)
	{
		
		EXTI_ClearITPendingBit(SIG1_EXTILINE);
	}
}
**/
