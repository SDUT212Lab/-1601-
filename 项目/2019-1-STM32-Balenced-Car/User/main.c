/*头文件*/
#include "stm32f10x.h"
#include "user_delay.h"
#include "user_led.h"
#include "user_systick.h"
#include "user_usart.h"
#include "user_rtc.h"
#include "user_28byj.h"

/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;

/*引用的其他变量*/
extern struct rtc_time systime;

/*主函数*/
int main(void)
{	
	SysTick_Init(1000); //初始化状态机为1ms
	LED_Init();
	Moto_28BYJ_Init();
	while(1)
	{
		/*write your code here*/
		Moto_28BYJ_Run_Sin8(10);
		/*LED闪烁*/
		LED_Wenkle(100);
	}
	
}



