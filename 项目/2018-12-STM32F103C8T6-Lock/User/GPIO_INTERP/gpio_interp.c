#include "gpio_interp.h"
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
void Touch_Key_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SIG_CLKCMD(SIG_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = SIG_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(SIG_PORT,&GPIO_InitStruct);
}
/**
*name:Touch_Key_Read_Bit()
*fun :触摸开关读取状态
*para:void
*ret :有触摸返回1，没有触摸0
**/
uint8_t Touch_Key_Read_Bit()
{
	if(SIG == Bit_RESET)
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
static void Touch_Key_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	/*优先级组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/*中断源*/
	NVIC_InitStruct.NVIC_IRQChannel = SIG_IRQn;
	/*抢占优先级*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	/*子优先级*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =2;
	/*使能通道*/
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}
/**
*name:Touch_Key_EXTI_Init()
*fun :触摸开关配置中断
*para:void
*ret :void
**/
void Touch_Key_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	
	Touch_Key_NVIC_Init();
	/*EXTI信号源*/
	GPIO_EXTILineConfig(SIG_PORTSOURCE,SIG_PINSOURCE);
	
	EXTI_InitStruct.EXTI_Line = SIG_EXTILINE;
	/*EXTI为中断模式*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*中断类型*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	/*使能中断*/
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
}
/**
*name:Touch_Key_Init()
*fun :触摸开关初始化
*para:void
*ret :void
**/
void Touch_Key_Init()
{
	Touch_Key_GPIO_Init();
	Touch_Key_EXTI_Init();
}
/**
*name:Touch_Key_IRQHandler()
*fun :触摸开关中断，放在stm32f10x_it.c中
*para:void
*ret :void
**/
/**
#include "gpio_interp.h"
void Touch_Key_IRQHandler()
{
	if(EXTI_GetITStatus(SIG_EXTILINE) != RESET)
	{

		EXTI_ClearITPendingBit(SIG_EXTILINE);
	}
}
**/
