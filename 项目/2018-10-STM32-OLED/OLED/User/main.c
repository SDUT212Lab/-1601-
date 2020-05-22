/**
 *名称：STM32VET6模板
 *作者：陈冲
 *时间：2018年9月
 *版本：1.3
 *更新：1.0：无
	    1.1：修改参数Reset and Run
	    1.2：添加系统滴答延时
		1.3：添加LED驱动，方便调试
**/

/*头文件*/
#include "stm32f10x.h"
#include "delay.h"
#include "systick.h"
#include "led.h"
#include "oled.h"

/*主函数*/
int main(void)
{	
	LED_Init();
	OLED_Init();
	OLED_Print_ENString(0,0,"I LOVE MCU");
//	OLED_Print_ENWord(0,0,'!');
	while(1)
	{
		/*write your code here*/
		
		LED_Wenkle(50);
	}
	
	
}

