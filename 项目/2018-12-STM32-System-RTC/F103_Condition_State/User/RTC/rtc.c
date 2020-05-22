#include "rtc.h"
/**
*名称：RTC获取系统时间函数
*作者：陈冲
*时间：2018年12月
*版本：1.0
*更新：1.0：无
**/
//定义的到具体时间的时间
//定义的到具体时间的时间
static uint32_t all_second = 0;			//读取寄存器的时间
static uint32_t year_second = 0;		//计算到今年的1月1日 00:00是多少秒
static uint32_t month_second = 0;		//计算到今年的某月的1日 00：00是多少秒
static uint32_t day_second = 0;			//计算到今天的00：00是多少秒
static uint32_t hour_second = 0;		//计算到今天这个小时00是多少秒
static uint32_t minute_second = 0;	//计算到今天这个小时的这个分钟00是多少秒
//定义系统时间变量
struct rtc_time systime = 
{
	0,0,0,1,1,2000,0
};
/*
*name:void RTC_GetYear()
*fun :获取当前年份
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
*fun :获取当前月份
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
*fun :获取当前日
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
*fun :获取当前小时
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
*fun :获取当前分
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
*fun :获取当前秒，并刷新其他时间
*para:void
*ret :void
*/
void RTC_GetSecond()
{
	systime.rtc_sec = all_second - year_second - month_second - day_second -hour_second -minute_second;
}
/*
*name:void RTC_GetSecond()
*fun :刷新所有时间时间
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
*fun :RTC初始化配置函数
*para:is_set:如果要设置当前的时间戳，将其设置为1，下一次设置为0 time：当前的时间戳
*ret :1 ：数据没有丢失，0：数据丢失
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
	//检查数据是否丢失；
	if(BKP_ReadBackupRegister(RTC_BKP_DXR) != RTC_BKP_DATA || is_set == 1 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		//允许访问backup区域
		PWR_BackupAccessCmd(ENABLE);
		//复位backup区域
		BKP_DeInit();
		//打开外部晶振
		RCC_LSEConfig(RCC_LSE_ON);
		//等待LSE准备好
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET){}
		//使用外部晶振
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		//使能RTC
		RCC_RTCCLKCmd(ENABLE);
		//等待外部时钟同步
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
*fun :RTC中断服务程序
*para:is_set:如果要设置当前的时间戳，将其设置为1，下一次设置为0 time：当前的时间戳
*ret :1 ：数据没有丢失，0：数据丢失
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
			//RTC刷新时间
			RTC_GetTime();
	    // Wait until last write operation on RTC registers has finished 
	    RTC_WaitForLastTask();
	  }
}
*/

