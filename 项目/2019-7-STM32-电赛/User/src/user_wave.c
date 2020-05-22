#include "user_wave.h"
#include "user_delay.h"


void Wave_Cap_Init(u16 arr,u16 psc)	
{	 
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	WAVE_TIM_CLKCMD(WAVE_TIM_CLK, ENABLE);	
 	WAVE_GPIO_CLKCMD(WAVE_GPIO_CLK, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin  = WAVE_TIM_Channel_Pin; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   
	GPIO_Init(WAVE_TIM_Channel_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = WAVE_GPIO_Trigger_Pin;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     
	GPIO_Init(WAVE_GPIO_Trigger_Prot, &GPIO_InitStructure);
	
	//初始化定时器 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(WAVE_TIM, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3输入捕获参数
	TIM_ICInitStructure.TIM_Channel = WAVE_TIM_Channel; //CC1S=01 	选择输入端 IC3映射到TI3上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;//配置输入滤波器 不滤波
	TIM_ICInit(WAVE_TIM, &TIM_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = WAVE_TIM_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 	
	TIM_ITConfig(WAVE_TIM,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC3IE捕获中断	
	TIM_Cmd(WAVE_TIM,ENABLE ); 	//使能定时器3
}

/*超声波回波接收函数*/
uint32_t PreDistance;
uint16_t TIM3CH3_CAPTURE_STA,TIM3CH3_CAPTURE_VAL;
void Read_Distane(void)
{   
	GPIO_SetBits(WAVE_GPIO_Trigger_Prot,WAVE_GPIO_Trigger_Pin);
	delay_us(15);  
	GPIO_ResetBits(WAVE_GPIO_Trigger_Prot,WAVE_GPIO_Trigger_Pin);
	if(TIM3CH3_CAPTURE_STA&0X80)//成功捕获到了一次高电平
	{
		PreDistance=TIM3CH3_CAPTURE_STA&0X3F;
		PreDistance*=65536;					        //溢出时间总和
		PreDistance+=TIM3CH3_CAPTURE_VAL;		//得到总的高电平时间
		PreDistance=PreDistance*170/1000;
		TIM3CH3_CAPTURE_STA=0;			//开启下一次捕获
	}			
}

