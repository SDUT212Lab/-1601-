#include "DS18B20.h"
#include "delay.h"


void Temper_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void Temper_Mode_IPU()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void Temper_Mode_Out_PP()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

uint8_t Temper_GetACK()
{
	uint8_t ack =0;
	Temper_Mode_Out_PP();
	Temper_Out_Low;
	delay_us(500);
	Temper_Out_High;
	delay_us(60);
	
	Temper_Mode_IPU();
	ack = !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8));
	return ack;
}

void Temper_WriteBit(uint8_t bit)
{
	if(!bit)
	{
		Temper_Mode_Out_PP();
		Temper_Out_Low;
		delay_us(15);
		Temper_Out_Low;
		delay_us(60);
		Temper_Out_High;
		
	}
	else
	{
		Temper_Mode_Out_PP();
		Temper_Out_Low;
		delay_us(1);
		Temper_Out_High;
		delay_us(60);
		Temper_Out_High;
	}
}

uint8_t Temper_ReadBit()
{
	uint8_t bit;
	Temper_Mode_Out_PP();
	Temper_Out_Low;
	delay_us(2);
	Temper_Mode_IPU();
	delay_us(2);
	delay_us(15);
	bit = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
	
	
	return bit;
}

void Temper_Write(uint8_t data)
{
	uint8_t mask;
	for(mask = 0x01;mask != 0;mask<<=1)
	{
		if((mask&data) == 0)
		{
			Temper_WriteBit(0);
		}
		else Temper_WriteBit(1);
	}
}


uint8_t Temper_Read()
{
	uint8_t data;
	uint8_t mask;
	
	for(mask =0x01;mask!= 0;mask<<=1)
	{
		if(!Temper_ReadBit())
		{
			data &= ~mask;
		}
		else data |= mask;
	}
	return data;
}

uint8_t Temper_Start()
{
	uint8_t ack;
	ack = Temper_GetACK();
	if(ack == 1)
	{
		Temper_Write(0xcc);//跳过ROM，18B20 
		Temper_Write(0x44);//开始转换

	}
	return ack;
}

uint32_t Temper_Get()
{
	uint8_t LSB,MSB;
	uint8_t ack;
	uint32_t data;
	ack = Temper_Start();
	if(ack == 1)
	{
		Temper_GetACK();
		Temper_Write(0xcc);
		Temper_Write(0xBE);//开始读取

		LSB = Temper_Read();
		MSB = Temper_Read();
	}
	data = ((uint32_t)MSB<<8)+LSB;
	return data;
}

float Temper_Deal(uint32_t data)
{
	float tem;
	tem = data*0.0625;
	return tem;
}



