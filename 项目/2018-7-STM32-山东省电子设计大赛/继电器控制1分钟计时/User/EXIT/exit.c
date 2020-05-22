#include "exit.h"

static void MyNVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	//����NVICΪ������1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//�����ж�Դ1
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	//������ռ���ȼ�1������������ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	
	//�����ж�ͨ���������ر��ж�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	

	
}	

void EXIT_PB6_Init(FunctionalState Flag)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//��APB2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	MyNVIC_Init();
	
	/*GPIO����*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line6;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStruct.EXTI_LineCmd = Flag;
	
	EXTI_Init(&EXTI_InitStruct);
}

void EXIT_PB7_Init(FunctionalState Flag)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//��APB2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	MyNVIC_Init();
	
	/*GPIO����*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line7;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStruct.EXTI_LineCmd = Flag;
	
	EXTI_Init(&EXTI_InitStruct);
}

void EXIT_PB8_Init(FunctionalState Flag)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//��APB2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	MyNVIC_Init();
	
	/*GPIO����*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line8;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStruct.EXTI_LineCmd = Flag;
	
	EXTI_Init(&EXTI_InitStruct);
}
/**�ʼ�
	
	1.��ռ���ȼ�����Ӧ���ȼ�
		������Ӧ���ȼ�1����Ӧ���ȼ���ָ����ռ���ȼ���ͬ������£�
		��������ж�ͬʱ�����ô�ȴ�����Ӧ���ȼ��ߵ��ж�
		////////////////////////////////////////////////////////////////
		//�ж�����		|		��ռ���ȼ�			|	��Ӧ���ȼ�	  //
		//      A		|			0 				|		0		  //
		//      B		|			1 				|		0		  //
		//      C		|			1 				|		1		  //
		////////////////////////////////////////////////////////////////
		
		����ں�����ִ��C�жϷ���������ô���ܱ����ȼ����ߵ��ж�A�����
		��B��C��ǰ��ֻ�����ȼ���ͬ��C���ܱ�B��ϣ��������B��C��ͬʱ����
		�ģ��ں�����ӦB�жϡ�
	2.NVIC�����ȼ���
		���������ȼ���ʱ��Ҫע���ж������������NVICֻ��������16���ж�
		������������Ҳ����˵����ռ���ȼ�����Ӧ���ȼ���һ����λ���־�����
		�������λ���ַ������ռ���ȼ�����Ӧ���ȼ��������ַ���ģʽ
		1����λȫ������Ӧ���ȼ�
		2�����λ����ռ���ȼ���������λ����Ӧ���ȼ���16���ж�����֮�У�
		0����ռ��0-7����Ӧ��1����ռ��0-7����Ӧ
		3��������
	3.EXTI�ⲿ�ж�
		STM������GPIO�����뵽EXTI���ⲿ�ж����ϣ�ʹ�����е�GPIO������Ϊ�ⲿ�ж�
		������ԴPA0-PG0 ���ӵ�EXIT0��PA1-PG1 ���ӵ� EXTI1 .��������EXITxֻ����Ӧ
		һ���˿ڵ��¼�����������ͨ��Ӧ�þ��ǽ���һ������������Ϊ�½��ش�������
		�жϼ�ⰴ����
		EXTI_InitStruct.EXTI_Line = EXTI_Line5;  ��EXTI
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;ѡ���жϻ���ѡ���¼�
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;ѡ���жϴ����ķ�ʽ
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;�򿪻��߹ر��ж�
	4.AFIOʱ��
		RCC_APB2PeriphClockCmd()���ǻ������˲���RCC_APB2Periph_AFIO��ʾ������AFIO
		ʱ�ӡ�
		GPIO����������������⣬��������ΪƬ������ĸ�������������紮�ڡ�ADC��
		�������GPIO����һ��Ĭ�ϵĸ��ù��ܣ��е�GPIO������ӳ�书�ܡ���ӳ�书����ָ
		�ܰ�ԭ������A���ŵ�Ĭ�ϸ��ù���ת�Ƶ�B���Ž���ʹ�ã�ǰ����B���ž�����ӳ��
		����
		����GPIO����EXTI�ⲿ�жϻ���ʹ����ӳ�书��ʱ���ͱ����AFIOʱ�ӣ�ʹ��Ĭ��
		���ù���ʱ���Ͳ���Ҫ��AFIOʱ��
	5.����GPIO�жϵĲ���
		1������NVIC��������ʼ��������������NVIC_PriorityGroupConfig��
		��ʱ��
		2��GPIO��ʼ��
		3���ⲿ�жϳ�ʼ��
	
**/
