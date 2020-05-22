#include "gpio_interp.h"
/**
*���ƣ�������������
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.0
*���£���
**/

/**
*name:Touch_Key_GPIO_Init()
*fun :�����������ų�ʼ��
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
*fun :�������ض�ȡ״̬
*para:void
*ret :�д�������1��û�д���0
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
*fun :�������������ж����ȼ�
*para:void
*ret :void
**/
static void Touch_Key_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	/*���ȼ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/*�ж�Դ*/
	NVIC_InitStruct.NVIC_IRQChannel = SIG_IRQn;
	/*��ռ���ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	/*�����ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =2;
	/*ʹ��ͨ��*/
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}
/**
*name:Touch_Key_EXTI_Init()
*fun :�������������ж�
*para:void
*ret :void
**/
void Touch_Key_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	
	Touch_Key_NVIC_Init();
	/*EXTI�ź�Դ*/
	GPIO_EXTILineConfig(SIG_PORTSOURCE,SIG_PINSOURCE);
	
	EXTI_InitStruct.EXTI_Line = SIG_EXTILINE;
	/*EXTIΪ�ж�ģʽ*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*�ж�����*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	/*ʹ���ж�*/
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
}
/**
*name:Touch_Key_Init()
*fun :�������س�ʼ��
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
*fun :���������жϣ�����stm32f10x_it.c��
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
