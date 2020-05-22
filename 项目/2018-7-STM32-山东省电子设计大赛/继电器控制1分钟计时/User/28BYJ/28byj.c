#include "28byj.h"

void Moto_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 \
			|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
}

void Moto_Single()				//实现单四拍控制
{
	uint16_t mask;

	Moto_Init();
	for(mask = 0x11;mask != 0x110;mask<<=1) // 0011 0011
	{
		GPIO_Write(GPIOA,mask);
		delay_us(15);
	}
	
}

void Stright_Moto(uint8_t Moto_x,uint8_t Dir,uint8_t pwm)
{
	Moto_Init();
	switch(Moto_x)
	{
		case 0: switch(Dir)
			{
				case 0: COR;break;
				case 1: BACK;break;
//				case: pwm:
			}
	
	}
	
}
