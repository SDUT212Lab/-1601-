#include "user_duoji.h"
#include "user_delay.h"
/**
*���ƣ�ֱ���������
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.1
*���£�1.1 2019���������
**/
extern uint16_t DUOJI1_Speed_cnt;
extern uint16_t DUOJI2_Speed_cnt;

void DUOJI_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
}
static void DUOJI1_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = DUOJI1_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
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
static void DUOJI1_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    DUOJI1_TIM_APBxClock_FUN(DUOJI1_TIM_CLK, ENABLE);	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period=DUOJI1_TIM_Period;
	  // ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler= DUOJI1_TIM_Prescaler;	
		// ʱ�ӷ�Ƶ���� ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(DUOJI1_TIM, &TIM_TimeBaseStructure);
	
		// ����������жϱ�־λ
    TIM_ClearFlag(DUOJI1_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(DUOJI1_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(DUOJI1_TIM, ENABLE);
}
void DUOJI1_Speed(uint16_t speed)//shang
{
	if(speed>=10&&speed<=50)
	{
		speed = speed*10+540;
		speed/=10;
		DUOJI1_Speed_cnt = speed;
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		TIM_Cmd(DUOJI1_TIM,ENABLE);
		while(DUOJI1_Speed_cnt!=0);
	}
}
void DUOJI2_Speed(uint16_t speed) //xia
{
	if( speed <=64)
	{
		speed = speed*10+600;
		speed/=10;
		DUOJI2_Speed_cnt = speed;
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		TIM_Cmd(DUOJI1_TIM,ENABLE);
		while(DUOJI2_Speed_cnt!=0);
	}
}
void DUOJI_Init(void)
{
	DUOJI_GPIO_Init();
	DUOJI1_TIM_NVIC_Config();
	DUOJI1_TIM_Mode_Config();		
}
