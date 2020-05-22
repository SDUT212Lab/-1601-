#include "beep.h"
/**
*name:BEEP_delay_us(uint16_t us)
*fun :��ʱ����΢��
*para:us:΢����
*ret :void
**/
void BEEP_delay_us(uint16_t us)
{
	for(int i = 0;i< us;i++)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	
	}
	
}
/**
*name:BEEP_delay_ms(uint16_t ms)
*fun :��ʱ��������
*para:ms:������
*ret :void
**/
void BEEP_delay_ms(uint16_t ms)
{
	for(int i = 0;i<ms;i++)
	{
		BEEP_delay_us(1000);
	}

}
/**
*name:BEEP_GPIO_Init()
*fun :BEEP GPIO��ʼ��
*para:void
*ret :void
**/
void BEEP_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	BEEP_CLKCMD(BEEP_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = BEEP_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(BEEP_PORT,&GPIO_InitStruct);
	
}
/**
*name:BEEP_Init()
*fun :BEEP��ʼ��
*para:void
*ret :void
**/
void BEEP_Init()
{
	BEEP_GPIO_Init();
	BEEP_OFF;
}
/**
*name:BEEP_DIDI(uint16_t num,uint16_t time)
*fun :BEEP�����ε���
*para:num ��������Ŀ time��Ƶ��
*ret :void
**/
void BEEP_DIDI(uint16_t num,uint16_t time)
{
	if(num == 0)
	{
		if(GPIO_ReadOutputDataBit(BEEP_PORT,BEEP_PIN) == 0)
		{
			BEEP_OFF;
		}
		else
		{
			BEEP_ON;
		}
		BEEP_delay_ms(time);
	}
	else 
	{
		for(int i = 0;i<num;i++)
		{
			if(GPIO_ReadOutputDataBit(BEEP_PORT,BEEP_PIN) == 0)
				BEEP_OFF;
			else
				BEEP_ON;
			BEEP_delay_ms(time);
		}
	
	}
}
