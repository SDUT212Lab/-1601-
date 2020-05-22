#include "user_led.h"
/**
*���ƣ�LED��������
*���ߣ��³�
*ʱ�䣺2018��10��
*�汾��1.0
*���£�1.0����
**/

/**
*����ȫ�ֱ���
**/
extern uint32_t LED_toogle_cnt;

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
	if(LED_toogle_cnt >= ms)
	{
		LED_toogle_cnt = 0;
		if(GPIO_ReadOutputDataBit(LED_PORT,LED_PIN))
			GPIO_WriteBit(LED_PORT,LED_PIN,Bit_RESET);
		else
			GPIO_WriteBit(LED_PORT,LED_PIN,Bit_SET);
	}
}

