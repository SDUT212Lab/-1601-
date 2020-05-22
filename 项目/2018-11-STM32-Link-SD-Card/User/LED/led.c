#include "led.h"
#include "systick.h"
/**
*���ƣ�LED��������
*���ߣ��³�
*ʱ�䣺2018��10��
*�汾��1.0
*���£�1.0����
**/

/**
*name:void LED_Init()  
*fun :LED��ʼ��
*para:void
*ret :void
**/
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	LED_CLKCMD(LED_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT,&GPIO_InitStruct);
}
/**
*name:void LED_Wenkle(uint32_t ms)
*fun :LED��˸����
*para:uint32_t ms ��˸��Ƶ��
*ret :void
**/
void LED_Wenkle(uint32_t ms)
{
	LED_ON;
	SysTick_delay_ms(ms);
	LED_OFF;
	SysTick_delay_ms(ms);
}

