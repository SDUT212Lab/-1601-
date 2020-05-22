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
#include "usart.h"

int main(void)
{	

	USART_x_Init(USART_1);
	USART_x_Init(USART_2);
	while(1)
	{
		USART_SendData(USART_1,'a');
		USART_SendData(USART_2,'b');
		delay_ms(100);
	}
}

