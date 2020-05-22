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
#include "led.h"
#include "systick.h"
#include "usart.h"
#include "matrix_key.h"
#include "math.h"
#include "lock_display.h"
#include "28byj.h"
#include "general_tim.h"
#include "gpio_interp.h"
#include "ht1261.h"
#include "mg90s.h"

extern uint32_t input_time;

/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;
uint32_t MG90S_toogle_cnt = 0;
uint32_t Matrix_KEY_cnt = 0;

/*主函数*/
int main(void)
{	
	SysTick_Init(1000); //初始化状态机
//	NVIC_SetPriority(SysTick_IRQn,(1<<__NVIC_PRIO_BITS)-15);
	MG90S_Init();
	GENERAL_TIM_Init();
	HT1261_Init();
	HT1261_Display_Data(0,5,0,0,0);
	LED_Init();
	Matrix_Init();
	while(1)
	{

		/*write your code here*/
		/*LED闪烁*/
		LED_Wenkle(50);
	}
	
}

