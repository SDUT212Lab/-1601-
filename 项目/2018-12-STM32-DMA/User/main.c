/*头文件*/
#include "stm32f10x.h"
#include "string.h"
#include "user_delay.h"
#include "user_led.h"
#include "user_systick.h"
#include "user_usart.h"
#include "user_rtc.h"
#include "user_dma.h"
#include "user_fyu43t4827.h"
#include "user_28byj.h"
#include "user_pwm.h"
#include "bsp_ds18b20.h"
#include "user_infrared.h"
/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;
uint8_t  zf_flag= 0;
/*引用的其他变量*/
extern struct tm rtc_time;
extern uint8_t usart_1_receive_data[80];
extern uint8_t usart_buffer[10] ;
extern uint8_t command_flag;
extern uint8_t pwm_data;
extern uint32_t infrared_data;
/*主函数*/

int main(void)
{	
	SysTick_Init(1000); //初始化状态机为1ms
	LED_Init();
	USART_x_Init(USART1);
	RTC_Configure(0,1546587750);
	RTC_GetTime();
	FYU43T4827_SetVal("second",rtc_time.tm_sec);
	FYU43T4827_SetVal("minute",rtc_time.tm_min);
	FYU43T4827_SetVal("year",rtc_time.tm_year);
	FYU43T4827_SetVal("month",rtc_time.tm_mon);
	FYU43T4827_SetVal("day",rtc_time.tm_mday);
	FYU43T4827_SetVal("hour",rtc_time.tm_hour);
	while(1)
	{
		/*write your code here*/
		/*LED闪烁*/
		LED_Wenkle(100);
	}
}
