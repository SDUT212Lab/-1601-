/**
*���ƣ�STM32VET6ģ��
*���ߣ��³�
*ʱ�䣺2018��9��
*�汾��1.0
*���£�1.0����
**/

/*ͷ�ļ�*/
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

