#include "user_rtc.h"
/**
*名称：RTC获取系统时间函数
*作者：陈冲
*时间：2018年12月
*版本：1.0
*更新：1.0：无
**/
/*变量定义*/
uint32_t all_second = 0;
struct tm rtc_time;
typedef unsigned int time_t;
const char Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/*
*name:void localtime(time_t time,struct tm *t)
*fun :转化为当地时间
*para:time:自1970年到现在过去的秒数    *t结构体
*ret :void
*/
void localtime(time_t time,struct tm *t)
{
	unsigned int Pass4year;
	int hours_per_year;
	//取秒时间
	t->tm_sec=(int)(time % 60);
	time /= 60;
	//取分钟时间
	t->tm_min=(int)(time % 60);
	time /= 60;
	//取过去多少个四年，每四年有 1461*24 小时
	Pass4year=((unsigned int)time / (1461L * 24L));
	//计算年份
	t->tm_year=(Pass4year << 2) + 1970;
	//四年中剩下的小时数
	time %= 1461L * 24L;
	//校正闰年影响的年份，计算一年中剩下的小时数
	for (;;)
	{
		//一年的小时数
		hours_per_year = 365 * 24;
		//判断闰年
		if ((t->tm_year & 3) == 0)
		{
			//是闰年，一年则多24小时，即一天
			hours_per_year += 24;
		}
		if (time < hours_per_year)
		{
			break;
		}
		t->tm_year++;
		time -= hours_per_year;
	}
		//小时数
	t->tm_hour=(int)(time % 24);
	//一年中剩下的天数
	time /= 24;
	//假定为闰年
	time++;
	//校正闰年的误差，计算月份，日期
	if((t->tm_year & 3) == 0)
	{
		if (time > 60)
		{
			time--;
		}
		else
		{
			if (time == 60)
			{
				t->tm_mon = 1;
				t->tm_mday = 29;
				return ;
			}
		}
}
//计算月日
	for (t->tm_mon = 0; Days[t->tm_mon] < time;t->tm_mon++)
	{
		time -= Days[t->tm_mon];
		}
		t->tm_mday = (int)(time);
		return;
}
/*
*name:int isleap(int year)
*fun :判断闰年函数
*para:year:年份
*ret :1:闰年 0:平年
*/
int isleap(int year)
{
	return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}
inline void RTC_GetTime()
{
	all_second = RTC_GetCounter();
	RTC_WaitForLastTask();
	localtime(all_second,&rtc_time);
	rtc_time.tm_mon +=1;
	rtc_time.tm_hour += TIME_ZOOM;
	if(rtc_time.tm_hour>=24)
		rtc_time.tm_mday+=1;
	rtc_time.tm_hour%=24;
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
	if(BKP_ReadBackupRegister(RTC_BKP_DRX) != RTC_BKP_DATA || is_set == 1 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		//允许访问backup区域
		PWR_BackupAccessCmd(ENABLE);
		//复位backup区域
		BKP_DeInit();
		//打开外部晶振
		#ifdef 	RTC_CLOCK_SOURCE_LSE
			/* 使能 LSE */
			RCC_LSEConfig(RCC_LSE_ON);
			/* 等待 LSE 准备好 */
			while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
			/* 选择 LSE 作为 RTC 时钟源 */
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
			/* 使能 RTC 时钟 */
			RCC_RTCCLKCmd(ENABLE);
			/* 等待 RTC 寄存器同步因为RTC时钟是低速的，内环时钟是高速的，所以要同步*/
			RTC_WaitForSynchro();
			/* 确保上一次 RTC 的操作完成 */
			RTC_WaitForLastTask();
			/* 使能 RTC 秒中断 */
			RTC_ITConfig(RTC_IT_SEC, ENABLE);
			/* 确保上一次 RTC 的操作完成 */
			RTC_WaitForLastTask();
			/* 设置 RTC 分频: 使 RTC 周期为1s  */
			/* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) = 1HZ */
			RTC_SetPrescaler(32767); 
			/* 确保上一次 RTC 的操作完成 */
			RTC_WaitForLastTask();
		#endif
		#ifdef RTC_CLOCK_SOURCE_LSI
			/* 使能 LSI */
			RCC_LSICmd(ENABLE);
			/* 等待 LSI 准备好 */
			while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
			/* 选择 LSI 作为 RTC 时钟源 */
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
			/* 使能 RTC 时钟 */
			RCC_RTCCLKCmd(ENABLE);
			/* 等待 RTC 寄存器同步 因为RTC时钟是低速的，内环时钟是高速的，所以要同步*/
			RTC_WaitForSynchro();
			/* 确保上一次 RTC 的操作完成 */
			RTC_WaitForLastTask();
			/* 使能 RTC 秒中断 */
			RTC_ITConfig(RTC_IT_SEC, ENABLE);
			/* 确保上一次 RTC 的操作完成 */
			RTC_WaitForLastTask();
			/* 设置 RTC 分频: 使 RTC 周期为1s ,LSI约为40KHz */
			/* RTC period = RTCCLK/RTC_PR = (40 KHz)/(40000-1+1) = 1HZ */	
			RTC_SetPrescaler(40000-1); 
			/* 确保上一次 RTC 的操作完成 */
			RTC_WaitForLastTask();
		#endif
		RTC_SetCounter(time);
		flag = 0;
	}
	else
	{
		RTC_SetCounter(time);
		BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);
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
#include "user_rtc.h"
extern struct tm rtc_time;
void RTC_IRQHandler(void)
{
	  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	  {
	    // Clear the RTC Second interrupt
	    RTC_ClearITPendingBit(RTC_IT_SEC);
			RTC_GetTime();
	    // Wait until last write operation on RTC registers has finished 
	    RTC_WaitForLastTask();
	  }
}
*/

