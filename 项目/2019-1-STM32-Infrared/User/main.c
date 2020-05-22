/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "user_delay.h"
#include "user_led.h"
#include "user_systick.h"
#include "user_usart.h"
#include "user_rtc.h"
#include "user_infrared.h"

/*ȫ��״̬������*/
uint32_t LED_toogle_cnt = 0;

/*���õ���������*/
extern struct rtc_time systime;
extern uint32_t infrared_data;
/*������*/

int main(void)
{	
	SysTick_Init(1000); //��ʼ��״̬��Ϊ1ms
	Infrared_Init();
	USART_x_Init(USART1);
	LED_Init();
	while(1)
	{
		/*write your code here*/
		if(infrared_data!= 0)
		{
			USART_x_Send_Num(USART1,infrared_data);
			USART_x_Send_String(USART1,"\r\n");
			infrared_data = 0;
		}
		/*LED��˸*/
		LED_Wenkle(80);
	}
}

