#include "user_system.h"
/*
*name:void System_Init()
*fun :ϵͳ��ʼ��������������һЩϵͳ�˿ڳ�ʼ���Ķ���
*para:void
*fun :void
*/
void System_Init()
{
	SysTick_Init(1000); //��ʼ��״̬��Ϊ1ms
	LED_Init();
}
