#ifndef _USER_RTC_H
#define _USER_RTC_H
/*头文件*/
#include "stm32f10x.h"

/*宏定义*/
//设置备份的寄存器
#define RTC_BKP_DRX	BKP_DR1
//写入到备份寄存器的数据
#define RTC_BKP_DATA   0xa5a5
//北京地区的时间差
#define TIME_ZOOM (8)
//是否使用外部晶振
//#define RTC_CLOCK_SOURCE_LSE 
#define RTC_CLOCK_SOURCE_LSI

struct tm
{
	int tm_sec; /* 秒 – 取值区间为[0,59] */
	int tm_min; /* 分 - 取值区间为[0,59] */
	int tm_hour; /* 时 - 取值区间为[0,23] */
	int tm_mday; /* 一个月中的日期 - 取值区间为[1,31] */
	int tm_mon; /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
	int tm_year; /* 年份，其值等于实际年份减去1900 */
};

/*函数*/
uint8_t RTC_Configure(uint8_t is_set,uint32_t time);
void RTC_GetTime(void);

#endif

