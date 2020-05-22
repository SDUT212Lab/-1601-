#ifndef _RTC_H
#define _RTC_H
/*头文件*/
#include "stm32f10x.h"

/*宏定义*/
//选择时钟源
#define RTC_CLOCK_SOURCE_LSE
//设置备份的寄存器
#define RTC_BKP_DXR	BKP_DR1
//写入到备份寄存器的数据
#define RTC_BKP_DATA   0xa5a5
//北京地区的时间差
#define TIME_ZOOM (8)

/*变量*/
struct rtc_time {
	int rtc_sec;
	int rtc_min;
	int rtc_hour;
	int rtc_day;
	int rtc_mon;
	int rtc_year;
	int rtc_wday;
};

/*函数*/
uint8_t RTC_Configure(uint8_t is_set,uint32_t time);
void RTC_GetYear(void);
void RTC_GetMonth(void);
void RTC_GetDay(void);
void RTC_GetHour(void);
void RTC_GetMinute(void);
void RTC_GetSecond(void);
void RTC_GetTime(void);

#endif

