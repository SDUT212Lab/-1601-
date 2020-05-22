#include "user_rtc.h"
/**
*���ƣ�RTC��ȡϵͳʱ�亯��
*���ߣ��³�
*ʱ�䣺2018��12��
*�汾��1.0
*���£�1.0����
**/
/*��������*/
uint32_t all_second = 0;
struct tm rtc_time;
typedef unsigned int time_t;
const char Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/*
*name:void localtime(time_t time,struct tm *t)
*fun :ת��Ϊ����ʱ��
*para:time:��1970�굽���ڹ�ȥ������    *t�ṹ��
*ret :void
*/
void localtime(time_t time,struct tm *t)
{
	unsigned int Pass4year;
	int hours_per_year;
	//ȡ��ʱ��
	t->tm_sec=(int)(time % 60);
	time /= 60;
	//ȡ����ʱ��
	t->tm_min=(int)(time % 60);
	time /= 60;
	//ȡ��ȥ���ٸ����꣬ÿ������ 1461*24 Сʱ
	Pass4year=((unsigned int)time / (1461L * 24L));
	//�������
	t->tm_year=(Pass4year << 2) + 1970;
	//������ʣ�µ�Сʱ��
	time %= 1461L * 24L;
	//У������Ӱ�����ݣ�����һ����ʣ�µ�Сʱ��
	for (;;)
	{
		//һ���Сʱ��
		hours_per_year = 365 * 24;
		//�ж�����
		if ((t->tm_year & 3) == 0)
		{
			//�����꣬һ�����24Сʱ����һ��
			hours_per_year += 24;
		}
		if (time < hours_per_year)
		{
			break;
		}
		t->tm_year++;
		time -= hours_per_year;
	}
		//Сʱ��
	t->tm_hour=(int)(time % 24);
	//һ����ʣ�µ�����
	time /= 24;
	//�ٶ�Ϊ����
	time++;
	//У��������������·ݣ�����
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
//��������
	for (t->tm_mon = 0; Days[t->tm_mon] < time;t->tm_mon++)
	{
		time -= Days[t->tm_mon];
		}
		t->tm_mday = (int)(time);
		return;
}
/*
*name:int isleap(int year)
*fun :�ж����꺯��
*para:year:���
*ret :1:���� 0:ƽ��
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
	if(BKP_ReadBackupRegister(RTC_BKP_DRX) != RTC_BKP_DATA || is_set == 1 )
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		//�������backup����
		PWR_BackupAccessCmd(ENABLE);
		//��λbackup����
		BKP_DeInit();
		//���ⲿ����
		#ifdef 	RTC_CLOCK_SOURCE_LSE
			/* ʹ�� LSE */
			RCC_LSEConfig(RCC_LSE_ON);
			/* �ȴ� LSE ׼���� */
			while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
			/* ѡ�� LSE ��Ϊ RTC ʱ��Դ */
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
			/* ʹ�� RTC ʱ�� */
			RCC_RTCCLKCmd(ENABLE);
			/* �ȴ� RTC �Ĵ���ͬ����ΪRTCʱ���ǵ��ٵģ��ڻ�ʱ���Ǹ��ٵģ�����Ҫͬ��*/
			RTC_WaitForSynchro();
			/* ȷ����һ�� RTC �Ĳ������ */
			RTC_WaitForLastTask();
			/* ʹ�� RTC ���ж� */
			RTC_ITConfig(RTC_IT_SEC, ENABLE);
			/* ȷ����һ�� RTC �Ĳ������ */
			RTC_WaitForLastTask();
			/* ���� RTC ��Ƶ: ʹ RTC ����Ϊ1s  */
			/* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) = 1HZ */
			RTC_SetPrescaler(32767); 
			/* ȷ����һ�� RTC �Ĳ������ */
			RTC_WaitForLastTask();
		#endif
		#ifdef RTC_CLOCK_SOURCE_LSI
			/* ʹ�� LSI */
			RCC_LSICmd(ENABLE);
			/* �ȴ� LSI ׼���� */
			while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
			/* ѡ�� LSI ��Ϊ RTC ʱ��Դ */
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
			/* ʹ�� RTC ʱ�� */
			RCC_RTCCLKCmd(ENABLE);
			/* �ȴ� RTC �Ĵ���ͬ�� ��ΪRTCʱ���ǵ��ٵģ��ڻ�ʱ���Ǹ��ٵģ�����Ҫͬ��*/
			RTC_WaitForSynchro();
			/* ȷ����һ�� RTC �Ĳ������ */
			RTC_WaitForLastTask();
			/* ʹ�� RTC ���ж� */
			RTC_ITConfig(RTC_IT_SEC, ENABLE);
			/* ȷ����һ�� RTC �Ĳ������ */
			RTC_WaitForLastTask();
			/* ���� RTC ��Ƶ: ʹ RTC ����Ϊ1s ,LSIԼΪ40KHz */
			/* RTC period = RTCCLK/RTC_PR = (40 KHz)/(40000-1+1) = 1HZ */	
			RTC_SetPrescaler(40000-1); 
			/* ȷ����һ�� RTC �Ĳ������ */
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
*fun :RTC�жϷ������
*para:is_set:���Ҫ���õ�ǰ��ʱ�������������Ϊ1����һ������Ϊ0 time����ǰ��ʱ���
*ret :1 ������û�ж�ʧ��0�����ݶ�ʧ
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

