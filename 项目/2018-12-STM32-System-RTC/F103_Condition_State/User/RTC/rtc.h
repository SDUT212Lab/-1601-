#ifndef _RTC_H
#define _RTC_H
/*ͷ�ļ�*/
#include "stm32f10x.h"

/*�궨��*/
//ѡ��ʱ��Դ
#define RTC_CLOCK_SOURCE_LSE
//���ñ��ݵļĴ���
#define RTC_BKP_DXR	BKP_DR1
//д�뵽���ݼĴ���������
#define RTC_BKP_DATA   0xa5a5
//����������ʱ���
#define TIME_ZOOM (8)

/*����*/
struct rtc_time {
	int rtc_sec;
	int rtc_min;
	int rtc_hour;
	int rtc_day;
	int rtc_mon;
	int rtc_year;
	int rtc_wday;
};

/*����*/
uint8_t RTC_Configure(uint8_t is_set,uint32_t time);
void RTC_GetYear(void);
void RTC_GetMonth(void);
void RTC_GetDay(void);
void RTC_GetHour(void);
void RTC_GetMinute(void);
void RTC_GetSecond(void);
void RTC_GetTime(void);

#endif

