/*头文件*/
#include "stm32f10x_it.h"
#include "bsp_ds18b20.h"
#include "user_fyu43t4827.h"

//状态机参数
extern uint32_t LED_toogle_cnt;

uint16_t temper_time = 0;
float temper = 0;
void SysTick_Handler(void)
{
	LED_toogle_cnt++;
//	temper_time++;
//	if(temper_time>3000)
//	{
//		temper_time = 0;
//		temper = DS18B20_GetTemp_SkipRom();
//		FYU43T4827_SetVal("temper",(uint8_t)temper);
//	}
}


//void DMA1_Channel5_IRQHandler()
//{
//	if(DMA_GetITStatus(DMA1_IT_TC5) != RESET)
//	{
//		DMA_ClearITPendingBit(DMA1_IT_TC5);
//		
//	}
//}

#include "user_rtc.h"
#include "user_dma.h"
extern struct tm rtc_time;
void RTC_IRQHandler(void)
{
	  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	  {
	    // Clear the RTC Second interrupt
	    RTC_ClearITPendingBit(RTC_IT_SEC);
			//RTC刷新时间
			RTC_GetTime();
			FYU43T4827_SetVal("second",rtc_time.tm_sec);
			if(rtc_time.tm_sec == 0)
			{	FYU43T4827_SetVal("minute",rtc_time.tm_min);
				FYU43T4827_SetVal("year",rtc_time.tm_year);
				FYU43T4827_SetVal("month",rtc_time.tm_mon);
				FYU43T4827_SetVal("day",rtc_time.tm_mday);
				FYU43T4827_SetVal("hour",rtc_time.tm_hour);
			}
	    // Wait until last write operation on RTC registers has finished 
	    RTC_WaitForLastTask();
	  }
}
#include "user_usart.h"
#include "user_delay.h"

uint8_t mystrcmp(uint8_t *str1,uint8_t *str2)
{
	while(*(str1) != '\n')
	{
		if(*(str1++) != *(str2++))
			return 0;
	}
	return 1;
}

uint8_t usart_1_receive_data[80];
#include "user_28byj.h"
uint8_t usart_command[30] = "command_is_bujinoff\r\n";
uint8_t usart_command1[30] = "command_is_bujinon\r\n";
uint8_t usart_command2[20] = "command_bujinr\r\n";
uint8_t usart_command3[20] = "command_bujinb\r\n";
uint8_t pwm_data = 0;
uint8_t command_flag = 0;
int i = 0;
void USART_1_IRQHandler()
{
	if(USART_GetITStatus(USART_1,USART_IT_RXNE) != RESET)
	{
		usart_1_receive_data[i] = USART_ReceiveData(USART_1);
		if(usart_1_receive_data[i] == 0x0a)
		{
			if(usart_1_receive_data[i-1] == 0x0d)
			{
				if(mystrcmp(usart_1_receive_data,usart_command) == 1) command_flag =1;
				else if(mystrcmp(usart_1_receive_data,usart_command1) == 1) command_flag = 2;
				else if(mystrcmp(usart_1_receive_data,usart_command2) == 1) command_flag = 3;
				else if(mystrcmp(usart_1_receive_data,usart_command3) == 1) command_flag = 4;
				if(i == 13)
					{
						pwm_data = (usart_1_receive_data[0]-'0')*100;
						pwm_data+= (usart_1_receive_data[4]-'0')*10;
						pwm_data+= (usart_1_receive_data[8]-'0');
						command_flag = 5;
					}
				i = -1;
				
			}
		}
		i++;
		if(i==79)
		{
			i = 0;
		}
		
		USART_ClearFlag(USART_1,USART_FLAG_RXNE);
	}
}

#include "user_delay.h"
#include "user_infrared.h"
//infrared_data	红外线接收数据
uint32_t infrared_data = 0;
uint32_t data_temp = 0;
//trigger_num		检测中断的个数
uint8_t infrared_trigger_num	= 0;
void INFRARED_IRQHANDELER()
{
	uint16_t j = 0;
	
	if(EXTI_GetITStatus(INFRARED_EXTILINE) != RESET)
	{
		infrared_trigger_num++;
		if(infrared_trigger_num == 4)
		{
			data_temp = 0;
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
					if(j>150) //需要修改此值以适应不同的
						break;
				}
				j = 0;
			}
			EXTI_ClearFlag(INFRARED_EXTILINE);
			if((data_temp & 0xffff0000) == 0x00ff0000)
				infrared_data = data_temp;
		}
		
	}	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
