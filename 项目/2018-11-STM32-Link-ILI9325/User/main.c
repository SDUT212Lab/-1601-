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
#include "ILI9325.h"

/*������*/
int main(void)
{	
	LED_Init();
	ILI9325_Init();
//	ILI9325_BL_OFF;
	while(1)
	{
		/*write your code here*/
		ILI9325_Print_ENString(0,0,"Welcome To MCU World",0);
		/*LED��˸*/
		LED_Wenkle(1000);
	}
	
}

