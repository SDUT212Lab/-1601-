#include "28byj.h"

/**
*���ƣ�28BYJ��������
*���ߣ��³�
*�汾��1.0
*ʱ�䣺2018��8��
*���£���
**/

/**
*name: Moto_28BYJ_delay_us(uint16_t us)
*fun : ���ݲ���ȷ����ʱ
*para: us:΢����
*ret : void
**/
void Moto_28BYJ_delay_us(uint16_t us)
{
	for(int i = 0;i<us;i++)
	{
		__NOP();__NOP();
	}
}
/**
*name: Moto_28BYJ_delay_ms(uint16_t ms)
*fun : ���ݲ���ȷ����ʱ
*para: ms:΢����
*ret : void
**/
void Moto_28BYJ_delay_ms(uint16_t ms)
{
	for(int i = 0;i<ms;i++)
	Moto_28BYJ_delay_us(1000);

}
/**
*name: Moto_28BYJ_GPIO_Init()
*fun : �������28BYJʵ�ֶ˿ڳ�ʼ��
*para: void
*ret : void
**/
void Moto_28BYJ_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	IN1_CLKCMD(IN1_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = IN1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IN1_PORT,&GPIO_InitStruct);
	
	IN2_CLKCMD(IN2_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = IN2_PIN;
	GPIO_Init(IN2_PORT,&GPIO_InitStruct);
	
	IN3_CLKCMD(IN3_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = IN3_PIN;
	GPIO_Init(IN3_PORT,&GPIO_InitStruct);
	
	IN3_CLKCMD(IN3_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = IN4_PIN;
	GPIO_Init(IN3_PORT,&GPIO_InitStruct);
}
/**
*name:void Moto_28BYJ_Init()
*fun :���������ʼ��
*para:void
*ret :void
**/
void Moto_28BYJ_Init()
{
	Moto_28BYJ_GPIO_Init();
	GPIO_ResetBits(IN1_PORT,IN1_PIN);
	GPIO_ResetBits(IN2_PORT,IN2_PIN);
	GPIO_ResetBits(IN3_PORT,IN3_PIN);
	GPIO_ResetBits(IN4_PORT,IN4_PIN);
}
/**
*name:void Moto_28BYJ_Run_Sin4(uint8_t speed)
*fun :�������������ת��
*para:speedת�٣�0��12
*ret :void
**/
void Moto_28BYJ_Run_Sin4(uint8_t speed)
{
	for(int i = 1;i<=4;i++)
	{
		switch(i)
		{
			case 1:IN1H;IN2L;IN3L;IN4L;break;
			case 2:IN1L;IN2H;IN3L;IN4L;break;
			case 3:IN1L;IN2L;IN3H;IN4L;break;
			case 4:IN1L;IN2L;IN3L;IN4H;break;
		}
		Moto_28BYJ_delay_ms(20+12-speed);	//0.0288856s
		
	
	}
}
/**
*name:Moto_28BYJ_Run_Dou4(uint8_t speed)
*fun :�������˫����ת��
*para:speedת�٣�0��12
*ret :void
**/
void Moto_28BYJ_Run_Dou4(uint8_t speed)
{
	if(speed <=12)
	for(int i = 1;i<=4;i++)
	{
		switch(i)
		{
			case 1:IN1H;IN2H;IN3L;IN4L;break;
			case 2:IN1L;IN2H;IN3H;IN4L;break;
			case 3:IN1L;IN2L;IN3H;IN4H;break;
			case 4:IN1H;IN2L;IN3L;IN4H;break;
		}
		Moto_28BYJ_delay_ms(16+12-speed);
	}

}
/**
*name:Moto_28BYJ_Run_Sin8(uint8_t speed)
*fun :�������������ת��
*para:speedת�٣�0��12
*ret :void
**/
void Moto_28BYJ_Run_Sin8(uint8_t speed)
{
	if(speed <=12)
	for(int i = 1;i<=8;i++)
	{
		switch(i)
		{
			case 1:IN1H;IN2H;IN3L;IN4L;break;
			case 2:IN1H;IN2H;IN3L;IN4L;break;
			case 3:IN1L;IN2H;IN3L;IN4L;break;
			case 4:IN1L;IN2H;IN3H;IN4L;break;
			case 5:IN1L;IN2L;IN3H;IN4L;break;
			case 6:IN1L;IN2L;IN3H;IN4H;break;
			case 7:IN1L;IN2L;IN3L;IN4H;break;
			case 8:IN1H;IN2L;IN3L;IN4H;break;
		}
		Moto_28BYJ_delay_ms(20-speed);

	}

}
/**
*name:Moto_28BYJ_Run_xCri(uint8_t speed ,double x)
*fun :�������ת��xȦ
*para:	speedת�٣�0��12	xת����Ȧ����������С��
*ret :void
**/
void Moto_28BYJ_Run_xCri(uint8_t speed ,double x)
{
	for(int i = 0;i<8*64*x+1;i++)
	{
		Moto_28BYJ_Run_Sin4(speed);
	}
	

}
