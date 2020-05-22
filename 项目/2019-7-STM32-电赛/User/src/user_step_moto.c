#include "user_step_moto.h"
#include "user_delay.h"

/**
*���ƣ�ͨ�ö�ʱ����ʱ����
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.0
*���£���
**/

// �ж����ȼ�����
static void STEP_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = STEP_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */
static void STEP_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    STEP_TIM_APBxClock_FUN(STEP_TIM_CLK, ENABLE);	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period=STEP_TIM_Period;
	  // ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler= STEP_TIM_Prescaler;	
		// ʱ�ӷ�Ƶ���� ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(STEP_TIM, &TIM_TimeBaseStructure);
	
		// ����������жϱ�־λ
    TIM_ClearFlag(STEP_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(STEP_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(STEP_TIM, ENABLE);
}

void STEP_TIM_Init(void)
{
	STEP_TIM_NVIC_Config();
	STEP_TIM_Mode_Config();		
}


void STEP_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	STEP_MOTO_CLKCMD(STEP_MOTO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = STEP_MOTO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(STEP_MOTO_PORT,&GPIO_InitStructure);
}
void STEP_Init()
{
	STEP_GPIO_Init();
}
void STEP_Set_Angle(uint16_t angle)
{
	STEP_OFF;
	STEP_ON;
	delay_us(500+11.11*angle);
	STEP_OFF;
}
/**
*name:ENERAL_TIM_IRQHandler()
*fun :��ʱ���жϺ���������stm32f10x_it.c��
*para:void
*ret :void
**/
/*
uint32_t time = 0;
void STEP_TIM_IRQHandler()
{
	if(TIM_GetITStatus(STEP_TIM,TIM_IT_Update) != RESET)
	{
		time++;
		TIM_ClearITPendingBit(STEP_TIM,TIM_FLAG_Update);
	
	}
}
*/

