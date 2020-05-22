#include "1602.h"

void delay(uint8_t x)
{
	uint8_t a,b;
	for(a=x;a>0;a--)
		for(b=3;b>0;b--); 
}

void GPIOA_Init()
{

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);

}

void GPIO_ModeIPU(GPIO_TypeDef * GPIO_x,uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_x,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIO_x,GPIO_Pin);
	
}


void GPIO_ModeIPD(GPIO_TypeDef * GPIO_x,uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_x,&GPIO_InitStruct);
	GPIO_ResetBits(GPIO_x,GPIO_Pin);
	
}

void SMC_WriteData(uint8_t data)
{
	uint16_t data1;
	data1 = GPIO_ReadOutputData(GPIOA);
	GPIOA_Init();
	GPIO_Write(GPIOA, data);
	RSH;
	ENL;
	delay(5);
	ENH;
	delay(5);
	ENL;
}

void SMC_WriteCom(uint8_t com)
{
	uint16_t data1;
	data1 = GPIO_ReadOutputData(GPIOA);
	GPIOA_Init();
	GPIO_Write(GPIOA, com);
	RSL;
	ENL;
	delay(5);
	ENH;
	delay(5);
	ENL;
}

void SMC_Init()
{
	SMC_WriteCom(0x38);
	delay(20);
	SMC_WriteCom(0x0f);
	delay(20);
	SMC_WriteCom(0x06);
	delay(20);
	SMC_WriteCom(0x01);
	delay(20);

}
