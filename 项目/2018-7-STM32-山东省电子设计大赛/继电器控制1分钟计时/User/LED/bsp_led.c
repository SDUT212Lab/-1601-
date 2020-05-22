// bsp board surport package 板级支持包 只和这一个板子有关
#include "bsp_led.h" //每次建立一个头文件都得用魔术棒包含进来
#include "key.h"
#include "delay.h"
#include "beep.h"
#include "delay.h"

void LED_Init(void)
{
	//LED0
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct); //按照指定的结构体参数初始化GPIO
	LED(0,0);
	//LED1
	GPIO_InitStruct.GPIO_Pin = LED1;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	LED(1,0);
	//LED2
	GPIO_InitStruct.GPIO_Pin = LED2;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	LED(2,0);

}
void LED(uint8_t LED,uint8_t condition)
{
	switch(condition)
	{
		case 0:
			switch(LED)
			{
				case 0: GPIO_SetBits(GPIOB,GPIO_Pin_0);break;
				case 1: GPIO_SetBits(GPIOB,GPIO_Pin_1);break;
				case 2: GPIO_SetBits(GPIOB,GPIO_Pin_2);break;
			
			}break;
		case 1:
		
			switch(LED)
			{
				case 0: GPIO_ResetBits(GPIOB,GPIO_Pin_0);break;
				case 1: GPIO_ResetBits(GPIOB,GPIO_Pin_1);break;
				case 2: GPIO_ResetBits(GPIOB,GPIO_Pin_2);break;
			}break;
		case 2:
			switch(LED)
			{
				case 0:	{
							if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0) == 0)
							{
								GPIO_SetBits(GPIOB,GPIO_Pin_0);
							}
							else GPIO_ResetBits(GPIOB,GPIO_Pin_0);
						}break;
				
				case 1:	{
							if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1) == 0)
							{
								GPIO_SetBits(GPIOB,GPIO_Pin_1);
							}
							else GPIO_ResetBits(GPIOB,GPIO_Pin_1);
						}break;
						
				case 2:	{
							if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_2) == 0)
							{
								GPIO_SetBits(GPIOB,GPIO_Pin_2);
							}
							else GPIO_ResetBits(GPIOB,GPIO_Pin_2);
						}break;
			
			}break;
	}

}

void LED_Wenkle()
{
	int i = 0;
	do
	{
		LED(i,1);
		delay_ms(100);
		LED(i,0);
		delay_ms(100);
		i++;
	}while(i != 3);

}

void KEY_LED()
{
	if(KEY_Scan(1) == 1)
	{
		LED(1,2);
	}

	if(KEY_Scan(2) == 1)
	{
		LED(2,2);
	}
		if(KEY_Scan(0) == 1)
	{
		LED(0,2);
	}

}

void JDQ_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
	
}
void System_Init()
{
	int i = 0;
	LED(1,1);
	BEEP_ON;
	delay_ms(80);
	BEEP_OFF;
	JDQ_OFF;
	for(i=0;i<50;i++)
	{
		LED(1,0);
		delay_ms((54*1000)/100);
		LED(1,1);
		delay_ms((54*1000)/100);
	}
	
	for(i=0;i<11;i++)
	{	
		BEEP_ON;
		LED(0,1);
		LED(1,1);
		LED(2,1);
		delay_ms(100-10*i);
		BEEP_OFF;
		LED(0,0);
		LED(1,0);
		LED(2,0);
		delay_ms(100-10*i);
	}
	LED(0,1);
	LED(1,1);
	LED(2,1);
	JDQ_ON;

	
}
