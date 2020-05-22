/**
*名称：STM32VET6模板
*作者：陈冲
*时间：2018年9月
*版本：1.0
*更新：1.0：无
**/

/*头文件*/
#include "stm32f10x.h"
#include "delay.h"
#include "systick.h"
#include "usart.h"
#include "ds18b20.h"
#include "ht1261.h"

extern volatile uint8_t usart_1_receive_data;

int main(void)
{	

	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	while(1)
	{
		
	}
}

