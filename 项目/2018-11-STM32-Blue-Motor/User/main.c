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
**/

/*头文件*/
#include "stm32f10x.h"
#include "delay.h"
#include "systick.h"
#include "led.h"
#include "usart.h"
#include "blue_tooth.h"
#include "dc_moto.h"

extern volatile uint8_t usart_1_receive_data;

/*主函数*/
int main(void)
{	
	LED_Init();
	USART_x_Init(USART1);
	DC_Moto_Init(1400,1400);
	while(1)
	{
		/*write your code here*/
		switch(usart_1_receive_data)
		{
			case 'g' : DC_Moto_GO();break;
			case 'b' : DC_Moto_Back();break;
			case 's' : DC_Moto_Stop();break;
			case 'l' : DC_Moto_Left();break;
			case 'r' : DC_Moto_Right();break;
			case '1' : DC_Moto_Init(400,400);break;
			case '2' : DC_Moto_Init(800,800);break;
			case '3' : DC_Moto_Init(1000,1000);break;
		}
		/*LED闪烁*/
//		LED_Wenkle(1000);
	}
	
}

