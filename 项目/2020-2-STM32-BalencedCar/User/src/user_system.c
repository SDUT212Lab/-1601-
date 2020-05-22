#include "user_system.h"
//有些设备可能要初始化成功才能使用，而中断可能会打扰到初始化的进行
uint8_t init_flag = 0;
/*
*name:void System_Init()
*fun :系统初始化函数，包含了一些系统端口初始化的定义
*para:void
*fun :void
*/
void System_Init()
{
	SysTick_Init(1000); //初始化状态机为1ms
	LED_Init();
	Motor_Init();
	Blue_Tooth_Init();
	MPU6050_Init();
	init_flag = 1;
}
