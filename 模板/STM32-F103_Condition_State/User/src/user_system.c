#include "user_system.h"
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
}
