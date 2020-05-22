/**
 *名称：STM32VET6模板
 *作者：陈冲
 *时间：2018年9月
 *版本：1.3
 *更新：1.0：无
	    1.1：修改参数Reset and Run
	    1.2：添加系统滴答延时
			1.3：添加LED驱动，方便调试
			1.4：添加USART库，方便调试
			1.5：添加中断向量表说明，在doc/readme文件中,请自己配置中断
**/

/*头文件*/
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "systick.h"
#include "usart.h"
#include "28byj.h"
#include "rtc.h"
#include "fyu43t4827.h"


/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;
extern uint8_t usart_1_receive_data;
extern struct rtc_time systime;
/*主函数*/
int main(void)
{	
	SysTick_Init(1000); //初始化状态机为1ms
	LED_Init();
	FYU43T4827_Init();
	FYU43T4827_Page(0);
	Moto_28BYJ_Init();
	if(RTC_Configure(0,1545456920) == 0)
	{
		FYU43T4827_WriStr(0,0,300,30,0,65535,38912,0,0,1,"时间数据丢失，请联系191699575");
	}
	FYU43T4827_SetVal("year",systime.rtc_year);
	FYU43T4827_SetVal("month",systime.rtc_mon);
	FYU43T4827_SetVal("day",systime.rtc_day);
	FYU43T4827_SetVal("hour",systime.rtc_hour);
	FYU43T4827_SetVal("minute",systime.rtc_min);
	while(1)
	{	
		/*write your code here*/
		
		/*LED闪烁*/
		LED_Wenkle(50);
	}
}



