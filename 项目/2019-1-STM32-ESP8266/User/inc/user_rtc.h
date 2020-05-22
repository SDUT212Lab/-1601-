#ifndef _USER_RTC_H
#define _USER_RTC_H
/*ͷ�ļ�*/
#include "stm32f10x.h"

/*�궨��*/
//���ñ��ݵļĴ���
#define RTC_BKP_DRX	BKP_DR1
//д�뵽���ݼĴ���������
#define RTC_BKP_DATA   0xa5a5
//����������ʱ���
#define TIME_ZOOM (8)
//�Ƿ�ʹ���ⲿ����
//#define RTC_CLOCK_SOURCE_LSE 
#define RTC_CLOCK_SOURCE_LSI

struct tm
{
	int tm_sec; /* �� �C ȡֵ����Ϊ[0,59] */
	int tm_min; /* �� - ȡֵ����Ϊ[0,59] */
	int tm_hour; /* ʱ - ȡֵ����Ϊ[0,23] */
	int tm_mday; /* һ�����е����� - ȡֵ����Ϊ[1,31] */
	int tm_mon; /* �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11] */
	int tm_year; /* ��ݣ���ֵ����ʵ����ݼ�ȥ1900 */
};

/*����*/
uint8_t RTC_Configure(uint8_t is_set,uint32_t time);
void RTC_GetTime(void);

#endif

