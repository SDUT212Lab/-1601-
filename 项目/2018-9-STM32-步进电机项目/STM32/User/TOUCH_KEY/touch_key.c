#include "touch_key.h"
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
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = SIG_PIN;
	
	GPIO_Init(SIG_PORT,&GPIO_InitStruct);
	
	KEY1_CLKCMD(KEY1_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PORT,&GPIO_InitStruct);
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
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	/*�����ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
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
void Touch_Key_IRQHandler()
{
	if(EXTI_GetITStatus(SIG_EXTILINE) != RESET)
	{
		LCD12864_LED_ON();
		delay_ms(1000);
		EXTI_ClearITPendingBit(SIG_EXTILINE);
	}
}
**/


static void KEY_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	/*���ȼ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/*�ж�Դ*/
	NVIC_InitStruct.NVIC_IRQChannel = KEY1_IRQn;
	/*��ռ���ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	/*�����ȼ�*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =2;
	/*ʹ��ͨ��*/
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}

void KEY_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	
	KEY_NVIC_Init();
	/*EXTI�ź�Դ*/
	GPIO_EXTILineConfig(KEY1_PORTSOURCE	,KEY1_PINSOURCE);
	
	EXTI_InitStruct.EXTI_Line = KEY1_EXTILINE;
	/*EXTIΪ�ж�ģʽ*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*�ж�����*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	/*ʹ���ж�*/
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
}

void KEY_Init()
{
	KEY_EXTI_Init();
}
