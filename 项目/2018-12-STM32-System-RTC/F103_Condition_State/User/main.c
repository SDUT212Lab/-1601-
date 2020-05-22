/**
 *���ƣ�STM32VET6ģ��
 *���ߣ��³�
 *ʱ�䣺2018��9��
 *�汾��1.3
 *���£�1.0����
	    1.1���޸Ĳ���Reset and Run
	    1.2�����ϵͳ�δ���ʱ
			1.3�����LED�������������
			1.4�����USART�⣬�������
			1.5������ж�������˵������doc/readme�ļ���,���Լ������ж�
**/

/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "systick.h"
#include "usart.h"
#include "28byj.h"
#include "rtc.h"
#include "fyu43t4827.h"


/*ȫ��״̬������*/
uint32_t LED_toogle_cnt = 0;
extern uint8_t usart_1_receive_data;
extern struct rtc_time systime;
/*������*/
int main(void)
{	
	SysTick_Init(1000); //��ʼ��״̬��Ϊ1ms
	LED_Init();
	FYU43T4827_Init();
	FYU43T4827_Page(0);
	Moto_28BYJ_Init();
	if(RTC_Configure(0,1545456920) == 0)
	{
		FYU43T4827_WriStr(0,0,300,30,0,65535,38912,0,0,1,"ʱ�����ݶ�ʧ������ϵ191699575");
	}
	FYU43T4827_SetVal("year",systime.rtc_year);
	FYU43T4827_SetVal("month",systime.rtc_mon);
	FYU43T4827_SetVal("day",systime.rtc_day);
	FYU43T4827_SetVal("hour",systime.rtc_hour);
	FYU43T4827_SetVal("minute",systime.rtc_min);
	while(1)
	{	
		/*write your code here*/
		
		/*LED��˸*/
		LED_Wenkle(50);
	}
}



