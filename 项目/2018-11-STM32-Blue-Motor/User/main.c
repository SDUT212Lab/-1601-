/**
 *���ƣ�STM32VET6ģ��
 *���ߣ��³�
 *ʱ�䣺2018��9��
 *�汾��1.3
 *���£�1.0����
	    1.1���޸Ĳ���Reset and Run
	    1.2�����ϵͳ�δ���ʱ
			1.3�����LED�������������
			1.4�����USART�⣬�������
**/

/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "delay.h"
#include "systick.h"
#include "led.h"
#include "usart.h"
#include "blue_tooth.h"
#include "dc_moto.h"

extern volatile uint8_t usart_1_receive_data;

/*������*/
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
		/*LED��˸*/
//		LED_Wenkle(1000);
	}
	
}

