#include "user_velocity.h"

void ADVANCE_TIM_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);	
}

void ADVANCE_TIM_Mode_Config()
{
	ADVANCE_TIM_CLKCMD(ADVANCE_TIM_CLK,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	TIM_TimeBaseInitStructure.TIM_Period = ADVANCE_TIM_Period;  //累计在Period+1个频率更新或者终端
	TIM_TimeBaseInitStructure.TIM_Prescaler = ADVANCE_TIM_Prescaler; //驱动CNT计数器的始终 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(ADVANCE_TIM,&TIM_TimeBaseInitStructure);
	
	
	/*输入捕获结构体初始化*/
	TIM_ICInitTypeDef	TIM_ICInitStructure;
	/*捕获通道IC1设置8*/
	
	TIM_ICInitStructure.TIM_Channel = ADVANCE_TIM_IC1PWM_CHANNEL;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //信号来自于那个通道
	TIM_ICInitStructure.TIM_ICFilter = 0x1; //不滤波
	
	TIM_PWMIConfig(ADVANCE_TIM,&TIM_ICInitStructure);
	
	/*选择输入的触发信号*/
	TIM_SelectInputTrigger(ADVANCE_TIM,TIM_TS_TI1FP1);
	
	
	//选择从模式
	//PWM输入某试试，从模式必须工作在复位模式，输入捕获开始时，计数器CNT被复位
	TIM_SelectSlaveMode(ADVANCE_TIM,TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(ADVANCE_TIM,TIM_MasterSlaveMode_Enable);
	
	//使能捕获中断
	TIM_ITConfig(ADVANCE_TIM,TIM_IT_CC1,ENABLE);
	//清除中断标志位
	TIM_ClearITPendingBit(ADVANCE_TIM,TIM_IT_CC1);
	
	//使用高级定时器开始技术
	TIM_Cmd(ADVANCE_TIM,ENABLE);
}

void ADVANCE_TIM_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void ADVANCE_TIM_Init()
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
	ADVANCE_TIM_Mode_Config();	
}

/*中断服务函数

#include "user_velocity.h"
#include "user_usart.h"
uint16_t IC1_Value = 0;
uint16_t IC2_Value = 0;
float DutyCycle = 0;
float Frequency = 0;
void ADVANCE_TIM_IRQHandler()
{
	TIM_ClearITPendingBit(ADVANCE_TIM,TIM_IT_CC1);
	IC1_Value = TIM_GetCapture1(ADVANCE_TIM);
	IC2_Value = TIM_GetCapture2(ADVANCE_TIM);
	if(IC1_Value != 0)
	{
		DutyCycle = (float)((IC2_Value+1)*100)/(IC1_Value+1);
		Frequency = (72000000/(ADVANCE_TIM_Prescaler+1))/(float)(IC1_Value+1);
		USART_x_Send_String(USART1,"占空比");
		USART_x_Send_Float(USART1,DutyCycle);
		USART_x_Send_String(USART1,"频率");
		USART_x_Send_Float(USART1,Frequency);
	}
	else
	{
		DutyCycle = 0;
		Frequency = 0;
	}	
}

*/

