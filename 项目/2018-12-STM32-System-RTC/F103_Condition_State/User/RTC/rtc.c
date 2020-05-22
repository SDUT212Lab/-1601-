#include "rtc.h"
/**
*���ƣ�RTC��ȡϵͳʱ�亯��
*���ߣ��³�
*ʱ�䣺2018��12��
*�汾��1.0
*���£�1.0����
**/
//����ĵ�����ʱ���ʱ��
//����ĵ�����ʱ���ʱ��
static uint32_t all_second = 0;			//��ȡ�Ĵ�����ʱ��
static uint32_t year_second = 0;		//���㵽�����1��1�� 00:00�Ƕ�����
static uint32_t month_second = 0;		//���㵽�����ĳ�µ�1�� 00��00�Ƕ�����
static uint32_t day_second = 0;			//���㵽�����00��00�Ƕ�����
static uint32_t hour_second = 0;		//���㵽�������Сʱ00�Ƕ�����
static uint32_t minute_second = 0;	//���㵽�������Сʱ���������00�Ƕ�����
//����ϵͳʱ�����
struct rtc_time systime = 
{
	0,0,0,1,1,2000,0
};
/*
*name:void RTC_GetYear()
*fun :��ȡ��ǰ���
*para:void
*ret :void
*/
void RTC_GetYear()
{
	year_second = 0;
	for(systime.rtc_year = 1970;year_second<=all_second-366*60*60*24;systime.rtc_year ++)
	{
		
		if((systime.rtc_year %4 == 0 && systime.rtc_year  %100!= 0)||systime.rtc_year%400 == 0)
			year_second+= 366*60*60*24;
		else
			year_second+= 365*60*60*24;
	}
}
/*
*name:void RTC_GetMonth()
*fun :��ȡ��ǰ�·�
*para:void
*ret :void
*/
void RTC_GetMonth()
{
	month_second = 0;
	for(systime.rtc_mon = 1;month_second <=all_second - year_second-31*24*60*60;systime.rtc_mon++)
	{
		switch(systime.rtc_mon)
		{
			case 1:case 3:case 5:case 7:case 8:case 10:case 12: month_second+=31*24*60*60;break;
			case 4:case 6:case 9:case 11: month_second+=30*24*60*60;break;
			case 2: if((systime.rtc_year%4 == 0 && systime.rtc_year  %100!= 0)||systime.rtc_year%400 == 0) month_second+=29*24*60*60; else month_second+=28*24*60*60;break;
		}
	}
}
/*
*name:void RTC_GetDay()
*fun :��ȡ��ǰ��
*para:void
*ret :void
*/
void RTC_GetDay()
{
	day_second = 0;
	for(systime.rtc_day = 1;day_second<= all_second - year_second - month_second - 24*60*60 ;systime.rtc_day++)
	{
		day_second += 60*24*60;
	}
}
/*
*name:void RTC_GetHour()
*fun :��ȡ��ǰСʱ
*para:void
*ret :void
*/
void RTC_GetHour()
{
	hour_second = 0;
	for(systime.rtc_hour = 0;hour_second<= all_second - year_second - month_second - day_second -60*60;systime.rtc_hour++)
	{
		hour_second += 60*60;
	}
	systime.rtc_hour+=TIME_ZOOM;
}
/*
*name:void RTC_GetMinute()
*fun :��ȡ��ǰ��
*para:void
*ret :void
*/
void RTC_GetMinute()
{
	minute_second = 0;
	for(systime.rtc_min = 0;minute_second<= all_second - year_second - month_second - day_second -hour_second-60;systime.rtc_min++)
	{
		minute_second += 60;
	}
}
/*
*name:void RTC_GetSecond()
*fun :��ȡ��ǰ�룬��ˢ������ʱ��
*para:void
*ret :void
*/
void RTC_GetSecond()
{
	systime.rtc_sec = all_second - year_second - month_second - day_second -hour_second -minute_second;
}
/*
*name:void RTC_GetSecond()
*fun :ˢ������ʱ��ʱ��
*para:void
*ret :void
*/
inline void RTC_GetTime()
{
	all_second = RTC_GetCounter();
	RTC_WaitForLastTask();
	RTC_GetYear();
	RTC_GetMonth();
	RTC_GetHour();
	RTC_GetDay();
	RTC_GetMinute();
	RTC_GetSecond();
}
/*
*name:uint8_t RTC_Configure(uint8_t is_set,uint32_t time)
*fun :RTC��ʼ�����ú���
*para:is_set:���Ҫ���õ�ǰ��ʱ�������������Ϊ1����һ������Ϊ0 time����ǰ��ʱ���
*ret :1 ������û�ж�ʧ��0�����ݶ�ʧ
*/
uint8_t RTC_Configure(uint8_t is_set,uint32_t time)
{
	NVIC_InitTypeDef NVIC_InitsStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitsStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitsStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitsStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitsStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitsStruct);
	uint8_t flag = 1;
	//��������Ƿ�ʧ��
	if(BKP_ReadBackupRegister(RTC_BKP_DXR) != RTC_BKP_DATA || is_set == 1 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		//�������backup����
		PWR_BackupAccessCmd(ENABLE);
		//��λbackup����
		BKP_DeInit();
		//���ⲿ����
		RCC_LSEConfig(RCC_LSE_ON);
		//�ȴ�LSE׼����
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET){}
		//ʹ���ⲿ����
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		//ʹ��RTC
		RCC_RTCCLKCmd(ENABLE);
		//�ȴ��ⲿʱ��ͬ��
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(RTC_BKP_DXR,RTC_BKP_DATA);
		RTC_WaitForLastTask();
		RTC_SetCounter(time);
		flag = 0;
	}
	RTC_ITConfig(RTC_IT_SEC,ENABLE);
	RTC_GetTime();
	return flag;
}
/*
*name:void RTC_IRQHandler(void)
*fun :RTC�жϷ������
*para:is_set:���Ҫ���õ�ǰ��ʱ�������������Ϊ1����һ������Ϊ0 time����ǰ��ʱ���
*ret :1 ������û�ж�ʧ��0�����ݶ�ʧ
*/
/*
#include "rtc.h"
extern struct rtc_time systime;
void RTC_IRQHandler(void)
{
	  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	  {
	    // Clear the RTC Second interrupt
	    RTC_ClearITPendingBit(RTC_IT_SEC);
			//RTCˢ��ʱ��
			RTC_GetTime();
	    // Wait until last write operation on RTC registers has finished 
	    RTC_WaitForLastTask();
	  }
}
*/

