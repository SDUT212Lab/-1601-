#include "user_system.h"
//��Щ�豸����Ҫ��ʼ���ɹ�����ʹ�ã����жϿ��ܻ���ŵ���ʼ���Ľ���
uint8_t init_flag = 0;
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
	Motor_Init();
	Blue_Tooth_Init();
	MPU6050_Init();
	init_flag = 1;
}
