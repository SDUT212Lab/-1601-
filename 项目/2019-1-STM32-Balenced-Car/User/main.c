/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "user_delay.h"
#include "user_led.h"
#include "user_systick.h"
#include "user_usart.h"
#include "user_rtc.h"
#include "user_28byj.h"

/*ȫ��״̬������*/
uint32_t LED_toogle_cnt = 0;

/*���õ���������*/
extern struct rtc_time systime;

/*������*/
int main(void)
{	
	SysTick_Init(1000); //��ʼ��״̬��Ϊ1ms
	LED_Init();
	Moto_28BYJ_Init();
	while(1)
	{
		/*write your code here*/
		Moto_28BYJ_Run_Sin8(10);
		/*LED��˸*/
		LED_Wenkle(100);
	}
	
}



