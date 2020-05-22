#include "group_key.h"
#include "delay.h"

void Group_KEY_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	C1_CLKCMD(C1_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = C1_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(C1_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C2_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C2_PIN;
	GPIO_Init(C2_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C3_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C3_PIN;
	GPIO_Init(C3_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C4_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C4_PIN;
	GPIO_Init(C4_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C5_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C5_PIN;
	GPIO_Init(C5_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C6_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C6_PIN;
	GPIO_Init(C6_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C7_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C7_PIN;
	GPIO_Init(C7_PORT,&GPIO_InitStruct);
	
	C1_CLKCMD(C8_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = C8_PIN;
	GPIO_Init(C8_PORT,&GPIO_InitStruct);
}

void Group_KEY_Mode_IN_FLOATING(GPIO_TypeDef* GPIO_x,uint16_t GPIO_Pin_x)
{
	C1_CLKCMD(C2_CLK,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_x;
	GPIO_Init(GPIO_x,&GPIO_InitStruct);
}
void Group_KEY_Init()
{
	Group_KEY_GPIO_Init();
}
uint8_t Group_KEY_Scan()
{
	delay_ms(30);
	C1_H;C2_L;C3_L;C4_L;
	C5_F;C6_F;C7_F;C8_F;
	if(C5 == Bit_SET)
	{delay_ms(30);if(C5 == Bit_SET) return 1;}
	if(C6 == Bit_SET)
	{delay_ms(30);if(C6 == Bit_SET) return 2;}
	if(C7 == Bit_SET)
	{delay_ms(30);if(C7 == Bit_SET) return 3;}
	if(C8 == Bit_SET)
	{delay_ms(30);if(C8 == Bit_SET) return 4;}
	
	delay_ms(30);
	C1_L;C2_H;C3_L;C4_L;
	C5_F;C6_F;C7_F;C8_F;
	if(C5 == Bit_SET)
	{delay_ms(30);if(C5 == Bit_SET) return 5;}
	if(C6 == Bit_SET)
	{delay_ms(30);if(C6 == Bit_SET) return 6;}
	if(C7 == Bit_SET)
	{delay_ms(30);if(C7 == Bit_SET) return 7;}
	if(C8 == Bit_SET)
	{delay_ms(30);if(C8 == Bit_SET) return 8;}
	
	delay_ms(30);
	C1_L;C2_L;C3_H;C4_L;
	C5_F;C6_F;C7_F;C8_F;
	if(C5 == Bit_SET)
	{delay_ms(30);if(C5 == Bit_SET) return 9;}
	if(C6 == Bit_SET)
	{delay_ms(30);if(C6 == Bit_SET) return 10;}
	if(C7 == Bit_SET)
	{delay_ms(30);if(C7 == Bit_SET) return 11;}
	if(C8 == Bit_SET)
	{delay_ms(30);if(C8 == Bit_SET) return 12;}
	
	delay_ms(30);
	C1_L;C2_L;C3_L;C4_H;
	C5_F;C6_F;C7_F;C8_F;
	if(C6 == Bit_SET)
	{delay_ms(30);if(C6 == Bit_SET) return 14;}
	if(C7 == Bit_SET)
	{delay_ms(30);if(C7 == Bit_SET) return 15;}
	if(C8 == Bit_SET)
	{delay_ms(30);if(C8 == Bit_SET) return 16;}
	return 0;
}
