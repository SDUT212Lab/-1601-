/*ͷ�ļ�*/
#include "user_esp8266.h"
#include "user_usartdisplay.h"
#include "user_usart.h"

/*��������*/
uint8_t usart_1_receive_data;
/*������������*/
extern uint8_t init_flag;
extern uint32_t LED_toogle_cnt;
extern uint32_t	esp8266_cnt;
extern uint16_t esp8266_count;
extern uint8_t esp8266_receivedata[200];
/*Ӳ�������ж�*/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}
/*�ڴ�����ж�*/
void MemManage_Handler(void)
{
  while (1)
  {
  }
}
/*���ߴ����ж�*/
void BusFault_Handler(void)
{
  while (1)
  {
  }
}
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

/*״̬�������ж�*/
void SysTick_Handler(void)
{
	if(init_flag == 1)
	{
		esp8266_cnt++;
		LED_toogle_cnt++;

	}
	else
	{
	
	}
}
/*����1�ж�*/
void USART_1_IRQHandler()
{
	if(USART_GetITStatus(USART_1,USART_IT_RXNE) != RESET)
	{
		USART_ClearFlag(USART_1,USART_FLAG_RXNE);
	}
}
/*����1�ж�*/
void USART_2_IRQHandler()
{
	if(USART_GetITStatus(USART_2,USART_IT_RXNE) != RESET)
	{
		esp8266_receivedata[esp8266_count] = USART_ReceiveData(USART_2);
		ESP8266_GetTimestamp((char*)esp8266_receivedata);
		esp8266_count++;
		if(esp8266_count == 199)
			esp8266_count = 0;
	}
}
/*RTC�ж�*/
#include "user_rtc.h"
extern struct tm rtc_time;
void RTC_IRQHandler(void)
{
	  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	  {
			RTC_GetTime();
			FYU43T4827_SetVal("second",rtc_time.tm_sec);
			if(rtc_time.tm_sec == 0)
			{
				FYU43T4827_SetVal("minute",rtc_time.tm_min);
				FYU43T4827_SetVal("year",rtc_time.tm_year);
				FYU43T4827_SetVal("month",rtc_time.tm_mon);
				FYU43T4827_SetVal("day",rtc_time.tm_mday);
				FYU43T4827_SetVal("hour",rtc_time.tm_hour);
			}
//			if(rtc_time.tm_min == 0 && rtc_time.tm_sec == 0)
//			{
//				RTC_SetCounter(ESP8266_Get_Time());
//			}
				// Clear the RTC Second interrupt
				RTC_ClearITPendingBit(RTC_IT_SEC);
				// Wait until last write operation on RTC registers has finished 
				RTC_WaitForLastTask();
	  }
}

