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
#include "hc05.h"

/*������*/
int main(void)
{	
	LED_Init();
	while(1)
	{
		/*write your code here*/
		
		/*LED��˸*/
		LED_Wenkle(1000);
	}
	
}

