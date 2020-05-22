/*头文件*/
#include "stm32f10x.h"
#include "user_delay.h"
#include "user_led.h"
#include "user_systick.h"
#include "user_usart.h"
#include "user_rtc.h"
#include "user_esp8266.h"
#include "user_usartdisplay.h"
#include "beep.h"
#include "user_matrix_key.h"
#include "user_ds18b20.h"
#include <string.h>

/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;
uint8_t display_flag = 0;
uint8_t init_flag = 0;
/*引用的其他变量*/
extern struct tm rtc_time;
/*
时间表
8:00 	起床铃
8:30-9:20 		|		第一节课
9:20-10:00 		|		吃早饭
10:00-10:50		|		第二节课
10：50-11：00 |		休息
11：-11：50		|		第三节课
11：50-12			|		休息
12-12：50			|		第四节课
12：50-13			|		休息
13：-13：50		|		第五节课
13：50-15			|		吃午饭
15-15：50			|		第六节课
15：50-16			|		休息
16：-16：50		|		第七节课
16：50-17：		|		休息
17：-17：50		|		第八节课
17：50-19			|		吃饭
*/
void Display_menu(uint8_t condition_flag)
{
	switch(condition_flag)
	{
		case 1:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第一节课");break;
		case 2:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第二节课");break;
		case 3:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第三节课");break;
		case 4:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第四节课");break;
		case 5:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第五节课");break;
		case 6:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第六节课");break;
		case 7:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第七节课");break;
		case 8:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"第八节课");break;
		case 9:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"休息");break;
		case 10:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"吃早饭");break;
		case 11:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"吃午饭");break;
		case 12:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"吃晚饭");break;
		case 13:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"睡觉");break;
		case 14:FYU43T4827_WriStr(190,90,220,210,1,65535,38912,0,0,1,"起床");break;
	}
}
uint8_t alarm_flag = 0;
void BEEP_Alarm(uint8_t hour,uint8_t minute,uint16_t alarm_time,uint8_t condition_flag)
{
	if(rtc_time.tm_hour == hour)
	{
		if(display_flag==0||rtc_time.tm_min==minute&&rtc_time.tm_sec<4)
		{
			display_flag = 1; 
//			Display_menu(condition_flag);
			BEEP_DIDI(alarm_time,70);
			BEEP_ON;
			alarm_flag=1;
		}
	}
}
void System_Init(void);
/*主函数*/
int main(void)
{	
	System_Init();
	while(1)
	{
		/*write your code here*/
		BEEP_Alarm(8,0,200,14);
		BEEP_Alarm(8,30,20,1);
		BEEP_Alarm(9,20,20,10);
		BEEP_Alarm(10,0,20,2);
		BEEP_Alarm(10,50,20,9);
		BEEP_Alarm(11,0,20,3);
		BEEP_Alarm(11,50,20,9);
		BEEP_Alarm(12,0,20,4);
		BEEP_Alarm(12,50,20,9);
		BEEP_Alarm(13,0,20,5);
		BEEP_Alarm(13,50,20,11);
		BEEP_Alarm(15,0,20,6);
		BEEP_Alarm(15,50,20,9);
		BEEP_Alarm(16,0,20,7);
		BEEP_Alarm(16,50,20,9);
		BEEP_Alarm(17,0,20,8);
		BEEP_Alarm(17,50,20,12);
		BEEP_Alarm(19,0,40,13);
		if(rtc_time.tm_hour >= 21&&rtc_time.tm_min == 30&&rtc_time.tm_sec<5)
		{
			FYU43T4827_SetBK(0);
		}
		if(rtc_time.tm_hour == 7&&rtc_time.tm_min== 30&&rtc_time.tm_sec<5)
		{
			FYU43T4827_SetBK(100);
		}
		if(Matrix_Scan() == 4)
		{
			if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_4) == 1)
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			else
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
		}
		/*LED闪烁*/
		LED_Wenkle(50);
	}
	
}

void System_Init()
{
	FYU43T4827_Init();
	FYU43T4827_Page(0);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"系统开始初始化");
	delay_ms(2000);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"串口屏初始化成功");
	SysTick_Init(1000); //初始化状态机为1ms
	delay_ms(500);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"系统滴答定时器初始化成功");
	LED_Init();
	delay_ms(500);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"LED初始化成功");
	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	delay_ms(500);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"聚光灯初始化成功");
	Matrix_Init();
	delay_ms(500);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"矩阵按键初始化成功");
	BEEP_Init();
	BEEP_ON;
	delay_ms(500);
	BEEP_DIDI(4,70);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"BEEP初始化成功");
	while(DS18B20_Init()==1);
	ESP8266_Init();
	ESP8266_Unvarnished_Transmission(); 
	delay_ms(500);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"WIFI连接成功");
	static uint32_t all;
	while((all = ESP8266_Get_Time())== 0);
	RTC_Configure(1,all);
	RTC_GetTime();
	FYU43T4827_SetVal("second",rtc_time.tm_sec);
	FYU43T4827_SetVal("minute",rtc_time.tm_min);
	FYU43T4827_SetVal("year",rtc_time.tm_year);
	FYU43T4827_SetVal("month",rtc_time.tm_mon);
	FYU43T4827_SetVal("day",rtc_time.tm_mday);
	FYU43T4827_SetVal("hour",rtc_time.tm_hour);	
	delay_ms(500);
	FYU43T4827_WriStr(160,200,200,50,0,65535,38912,0,0,1,"时间初始化成功");
	FYU43T4827_Page(0);
	init_flag = 1;
	delay_ms(5000);
//	FYU43T4827_Page(4);
	RTC_GetTime();
	FYU43T4827_SetVal("second",rtc_time.tm_sec);
	FYU43T4827_SetVal("minute",rtc_time.tm_min);
	FYU43T4827_SetVal("year",rtc_time.tm_year);
	FYU43T4827_SetVal("month",rtc_time.tm_mon);
	FYU43T4827_SetVal("day",rtc_time.tm_mday);
	FYU43T4827_SetVal("hour",rtc_time.tm_hour);	

}



