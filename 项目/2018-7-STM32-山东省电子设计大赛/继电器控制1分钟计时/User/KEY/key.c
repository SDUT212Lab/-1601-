#include "key.h" 
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}


uint8_t KEY_Scan(uint8_t key_num)
{
	uint8_t flag = 0;
	switch(key_num)
	{
		case 0: {
					if(GPIO_ReadInputDataBit(GPIOB,KEY0)==0)
					{
//						
						while(GPIO_ReadInputDataBit(GPIOB,KEY0)==0);
						delay_ms(75);
						flag = 1;
					
					}
				}break;
		case 1: {
					if(GPIO_ReadInputDataBit(GPIOB,KEY1)==0)
					{
//						delay_ms(0);
						while(GPIO_ReadInputDataBit(GPIOB,KEY1)==0);
						delay_ms(75);
						flag = 1;
					}
					
				}break;
		case 2: {
					if(GPIO_ReadInputDataBit(GPIOB,KEY2) == 0)
					{
//						delay_ms(0);
						while(GPIO_ReadInputDataBit(GPIOB,KEY2) == 0);
						delay_ms(75);
						flag = 1;
					}
				}break;
	}
	return flag;
}
