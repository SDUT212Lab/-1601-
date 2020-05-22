#include "user_dc_moto.h"
/**
*名称：直流电机驱动
*作者：陈冲
*时间：2018年8月
*版本：1.1
*更新：1.1 2019年电赛更新
**/

void DC_Moto_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	DCMOTO1_IN0_CLKCMD(DCMOTO1_IN0_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = DCMOTO1_IN0_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DCMOTO1_IN0_PORT,&GPIO_InitStruct);
	
	DCMOTO1_IN0_CLKCMD(DCMOTO1_IN1_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = DCMOTO1_IN1_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DCMOTO1_IN1_PORT,&GPIO_InitStruct);
}


void MOTO_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(MOTO_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTO_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTO_TIM_CH1_PORT, &GPIO_InitStructure);
	
}

void MOTO_TIM_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	MOTO_TIM_APBxClock_FUN(MOTO_TIM_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=MOTO_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= MOTO_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(MOTO_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/	
	// 占空比配置

	uint16_t CCR1_Val = 5;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(MOTO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(MOTO_TIM, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(MOTO_TIM, ENABLE);
}

void DC_Moto_Speed(uint16_t speed)
{
	speed += 14;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = speed;
	TIM_OC1Init(MOTO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(MOTO_TIM, TIM_OCPreload_Enable);
	TIM_Cmd(MOTO_TIM, ENABLE);
}

void DC_Moto_Init()
{
	DC_Moto_GPIO_Init();
	MOTO_TIM_GPIO_Config();
	MOTO_TIM_Mode_Config();
}
