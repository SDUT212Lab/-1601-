#include "LCD12864.h"
/**
*���ƣ�LCD12864��������
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.1
*���£����ӱ�������
**/

/**
*name: ��ʱ����
*fun : ���ݲ���ȷ����ʱ
*para: us:΢����
*ret : void
**/
void LCD12864_delay_us(uint8_t us)
{
	for(int i= 0;i<us;i++)
	{
	
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();

	}
}
/**
*name: ��ʱ����
*fun : ���ݲ���ȷ����ʱ
*para: ms:������
*ret : void
**/
void LCD12864_delay_ms(uint16_t ms)
{
	for(int j = 0;j<ms;j++)
	{
		for(int i = 0;i<1000;i++)
		{
			__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();

		}
	}
}
/**
*name: LCD12864_GPIO_Init()
*fun : Һ��GPIO��ʼ������
*para: void
*ret : void
**/
void LCD12864_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RS_CLKCMD(RS_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = RS_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(RS_PORT,&GPIO_InitStruct);
	RW_CLKCMD(RW_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = RW_PIN;
	GPIO_Init(RW_PORT,&GPIO_InitStruct);
	
	EN_CLKCMD(EN_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = EN_PIN;
	GPIO_Init(EN_PORT,&GPIO_InitStruct);
	
	DX_CLKCMD(DX_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = D0|D1|D2|D3|D4|D5|D6|D7;
	GPIO_Init(DX_PORT,&GPIO_InitStruct);
	
	PSB_CLKCMD(PSB_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin =	PSB_PIN;
	GPIO_Init(PSB_PORT,&GPIO_InitStruct);
	
	BLK_CLKCMD(BLK_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = BLK_PIN;
	GPIO_Init(BLK_PORT,&GPIO_InitStruct);
}
/**
*name: LCD12864_Busy()
*fun : ���12864�Ƿ���æµ״̬
*para: void
*ret : void
**/
void LCD12864_Busy()
{
	GPIO_ResetBits(RS_PORT,RS_PIN);
	GPIO_SetBits(RW_PORT,RW_PIN);
	GPIO_SetBits(EN_PORT,EN_PIN);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	DX_CLKCMD(DX_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = D7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DX_PORT,&GPIO_InitStruct);
	
	uint8_t sta = 1;
	do 
	{
		GPIO_SetBits(EN_PORT,EN_PIN);
		LCD12864_delay_ms(5);
		sta = GPIO_ReadInputDataBit(DX_PORT,D7);
		GPIO_ResetBits(EN_PORT,EN_PIN);
	}while(sta);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(DX_PORT,&GPIO_InitStruct);
}
/**
*name: LCD12864_WriteData(uint8_t data,uint8_t is_command)
*fun : д�������ݺ���
*para: data:����
*			|0x01 �����ʾ					|0x0f/d	��ʾ�α�����˸��d��e��˸���Ͳ�ͬ
*			|0x02 �α��Ƶ���ǰ��һ��		|0x0e	��ʾ�α겻��˸
*			|0x08 ˯��ģʽ					|0x0c	����ʾ�������/�ر�˯��ģʽ
		is_command:0���� 1����
*ret : void
**/
void LCD12864_WriteData(uint8_t data,uint8_t is_command)
{
	LCD12864_Busy();
	if(is_command == 0)
	{
		
		GPIO_SetBits(RS_PORT,RS_PIN);
		GPIO_ResetBits(RW_PORT,RW_PIN);
		GPIO_ResetBits(EN_PORT,EN_PIN);
		LCD12864_delay_us(4);
		GPIO_Write(DX_PORT,data);
		LCD12864_delay_us(4);
		GPIO_SetBits(EN_PORT,EN_PIN);
		LCD12864_delay_us(4);
		GPIO_ResetBits(EN_PORT,EN_PIN);
//		LCD12864_delay_ms(1500);
		
		
	}
	else if(is_command == 1)
	{
		GPIO_ResetBits(RS_PORT,RS_PIN);
		GPIO_ResetBits(RW_PORT,RW_PIN);
		GPIO_ResetBits(EN_PORT,EN_PIN);
		LCD12864_delay_us(4);
		GPIO_Write(DX_PORT,data);
		LCD12864_delay_us(4);
		GPIO_SetBits(EN_PORT,EN_PIN);
		LCD12864_delay_us(4);
		GPIO_ResetBits(EN_PORT,EN_PIN);
	}
}
/**
*name: LCD12864_Init()
*fun : Һ����ʼ������
*para: void
*ret : void
**/
void LCD12864_Init()
{
	LCD12864_GPIO_Init();
	GPIO_SetBits(PSB_PORT,PSB_PIN);
	LCD12864_delay_ms(15);
	LCD12864_WriteData(0x34,1);
	LCD12864_WriteData(0x30,1);
	LCD12864_WriteData(0x0c,1);
	LCD12864_WriteData(0x01,1);
}

/**
*name: LCD12864_WriteStr(char *p,uint8_t x,uint8_t y)
*fun : д�ַ���
*para: p���ַ����ĳ�ʼ��ַ	x����	y����
*ret : void
**/
void LCD12864_WriteStr(char *p,uint8_t x,uint8_t y)
{
		switch(x)
	{
		case 1:LCD12864_WriteData(0x80+y-1,1);break;
		case 2:LCD12864_WriteData(0x90+y-1,1);break;
		case 3:LCD12864_WriteData(0x88+y-1,1);break;
		case 4:LCD12864_WriteData(0x98+y-1,1);break;
	}
	do
	{
		LCD12864_WriteData(*p,0);
//		LCD12864_delay_ms(1000);//��ʾ������Ч
	}while(*(++p));
}
/**
*name: void LCD12864_WriteNum(float num,uint8_t x, uint8_t y)
*fun : д������
*para: num��������ֵ	x����	y����
*ret : void
**/
void LCD12864_WriteNum(uint32_t num,uint8_t x, uint8_t y)
{
	switch(x)
	{
		case 1:LCD12864_WriteData(0x80+y-1,1);break;
		case 2:LCD12864_WriteData(0x90+y-1,1);break;
		case 3:LCD12864_WriteData(0x88+y-1,1);break;
		case 4:LCD12864_WriteData(0x98+y-1,1);break;
	}
	/*��������*/
	uint32_t temp = (uint32_t)num;
	uint8_t i = 0;
	char str;
	while(temp != 0)
	{
		temp /= 10;
		i++;
	}	
	temp = (uint32_t)num;
	while(i != 0)
	{
		str = '0'+ temp/((uint32_t)pow(10,i-1))%10;
		i--;
		LCD12864_WriteData(str,0);
//		LCD12864_delay_ms(1000);//��ʾ������Ч
	}

	
}

void LCD12864_LED_ON()
{
	GPIO_ResetBits(BLK_PORT,BLK_PIN);
}

void LCD12864_LED_OFF()
{
	GPIO_SetBits(BLK_PORT,BLK_PIN);
}


void Moto_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}
