/**
 *���ƣ�STM32VET6ģ��
 *���ߣ��³�
 *ʱ�䣺2018��9��
 *�汾��1.3
 *���£�1.0����
	    1.1���޸Ĳ���Reset and Run
	    1.2�����ϵͳ�δ���ʱ
		1.3�����LED�������������
**/

/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "delay.h"
#include "systick.h"
#include "led.h"
#include "oled.h"

/*������*/
int main(void)
{	
	LED_Init();
	OLED_Init();
	OLED_Print_ENString(0,0,"I LOVE MCU");
//	OLED_Print_ENWord(0,0,'!');
	while(1)
	{
		/*write your code here*/
		
		LED_Wenkle(50);
	}
	
	
}

