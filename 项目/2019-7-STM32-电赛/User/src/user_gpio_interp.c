#include "user_gpio_interp.h"
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
*fun :�������ض�ȡ״̬
*para:void
*ret :�д�������1��û�д���0
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
*fun :�������������ж����ȼ�
*para:void
*ret :void
**/
static void Interp_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	/*���ȼ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/*�ж�Դ*/
	NVIC_InitStruct.NVIC_IRQChannel = SIG1_IRQn;
	/*��ռ���ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	/*�����ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =3;
	/*ʹ��ͨ��*/
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = SIG2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4;
	
	NVIC_Init(&NVIC_InitStruct);
}
/**
*name:Touch_Key_EXTI_Init()
*fun :�������������ж�
*para:void
*ret :void
**/
void Interp_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	
	Interp_NVIC_Init();
	/*EXTI�ź�Դ*/
	GPIO_EXTILineConfig(SIG1_PORTSOURCE,SIG1_PINSOURCE);
	
	EXTI_InitStruct.EXTI_Line = SIG1_EXTILINE;
	/*EXTIΪ�ж�ģʽ*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*�ж�����*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	/*ʹ���ж�*/
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
	GPIO_EXTILineConfig(SIG2_PORTSOURCE,SIG2_PINSOURCE);
	EXTI_InitStruct.EXTI_Line = SIG2_EXTILINE;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStruct);
}
/**
*name:Touch_Key_Init()
*fun :�������س�ʼ��
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
*fun :���������жϣ�����stm32f10x_it.c��
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
