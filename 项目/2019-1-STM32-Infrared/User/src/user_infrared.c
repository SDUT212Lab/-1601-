#include "user_infrared.h"
/**
  * @name 		the driver of the infrared 
  * @time	    2019-1
	* @author   chenchong
  * @version	1.0
	*	@log			1.0:void
  */
	
/**
  * @brief  infraerd init function
  * @param  None
  * @retval None
  */
void Infrared_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = INFRARED_IRQCHANNEL;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	INFRARED_DATA_CLKCMD(INFRARED_DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = INFRARED_DATA_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(INFRARED_DATA_PORT,&GPIO_InitStruct);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_EXTILineConfig(INFRARED_PORTSOURCE,INFRARED_PINSOURCE);
	EXTI_InitStruct.EXTI_Line = INFRARED_EXTILINE;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	
	EXTI_Init(&EXTI_InitStruct);
}
/**
  * @brief  infraerd interrupt function,put it in stm32f10x_it.c file when you use it
  * @param  None
  * @retval None
  */
/*
#include "user_delay.h"
#include "user_infrared.h"
//infrared_data	红外线接收数据
uint32_t infrared_data = 0;
//trigger_num		检测中断的个数
uint8_t infrared_trigger_num	= 0;
void INFRARED_IRQHANDELER()
{
	uint16_t j = 0;
	uint32_t data_temp = 0;
	if(EXTI_GetITStatus(INFRARED_EXTILINE) != RESET)
	{
		infrared_trigger_num++;
		if(infrared_trigger_num == 4)
		{
			infrared_trigger_num = 0;
			for(int i =0;i<32;i++)
			{
				while(INFRARED_DATA == 1)
				{
					delay_us(10);
					j++;
					if(j>150) //需要修改此值以适应不同的
						break;
				}
				if(j>80)
				{
					data_temp |= (0x0001<<(31-i));
				}
				j = 0;
				while(INFRARED_DATA != 1)
				{
					delay_us(10);
					j++;
					if(j>150) //防止卡死
						break;
				}
				j = 0;
			}
			if((data_temp & 0xffff0000) == 0x00ff0000)
				infrared_data = data_temp;
		}
		EXTI_ClearFlag(INFRARED_EXTILINE);
	}	
}

*/

