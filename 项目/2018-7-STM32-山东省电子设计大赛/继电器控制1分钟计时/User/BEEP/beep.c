#include "beep.h"

void BEEP_Init()
{
	GPIO_InitTypeDef BEEP_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	BEEP_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	BEEP_InitStruct.GPIO_Pin = GPIO_Pin_9;
	BEEP_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&BEEP_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	
}
