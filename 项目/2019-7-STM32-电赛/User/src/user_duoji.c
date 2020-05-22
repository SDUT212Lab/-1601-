#include "user_duoji.h"
#include "user_delay.h"
/**
*名称：直流电机驱动
*作者：陈冲
*时间：2018年8月
*版本：1.1
*更新：1.1 2019年电赛更新
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
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = DUOJI1_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */
static void DUOJI1_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    DUOJI1_TIM_APBxClock_FUN(DUOJI1_TIM_CLK, ENABLE);	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period=DUOJI1_TIM_Period;
	  // 时钟预分频数
    TIM_TimeBaseStructure.TIM_Prescaler= DUOJI1_TIM_Prescaler;	
		// 时钟分频因子 ，没用到不用管
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// 重复计数器的值，没用到不用管
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // 初始化定时器
    TIM_TimeBaseInit(DUOJI1_TIM, &TIM_TimeBaseStructure);
	
		// 清除计数器中断标志位
    TIM_ClearFlag(DUOJI1_TIM, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(DUOJI1_TIM,TIM_IT_Update,ENABLE);
		
		// 使能计数器
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
