#include "LCD1602.h"

/**
*name: ��ʱ����
*fun : ���ݲ���ȷ����ʱ
*para: us:΢����
*ret : void
**/
void LCD1602_delay_us(uint8_t us)
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
void LCD1602_delay_ms(uint16_t ms)
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
*name: LCD1602_Busy()
*fun : ���1602�Ƿ���æµ״̬
*para: void
*ret : void
**/
void LCD1602_Busy()
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
		LCD1602_delay_ms(5);
		sta = GPIO_ReadInputDataBit(DX_PORT,D7);
		GPIO_ResetBits(EN_PORT,EN_PIN);
	}while(sta);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(DX_PORT,&GPIO_InitStruct);
}
/**
*name: LCD1602_GPIO_Init()
*fun : Һ��GPIO��ʼ������
*para: void
*ret : void
**/
void LCD1602_GPIO_Init()
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
}
/**
*name: LCD1602_WriteData(uint8_t data,uint8_t is_command)
*fun : д�������ݺ���
*para: data:����	is_command:0���� 1����
*ret : void
**/
void LCD1602_WriteData(uint8_t data,uint8_t is_command)
{
	LCD1602_Busy();
	if(is_command == 0)
	{
		
		GPIO_SetBits(RS_PORT,RS_PIN);
		GPIO_ResetBits(RW_PORT,RW_PIN);
		GPIO_ResetBits(EN_PORT,EN_PIN);
		LCD1602_delay_us(2);
		GPIO_Write(DX_PORT,data);
		LCD1602_delay_us(2);
		GPIO_SetBits(EN_PORT,EN_PIN);
		LCD1602_delay_us(2);
		GPIO_ResetBits(EN_PORT,EN_PIN);
		LCD1602_delay_ms(1500);
		
		
	}
	else if(is_command == 1)
	{
		GPIO_ResetBits(RS_PORT,RS_PIN);
		GPIO_ResetBits(RW_PORT,RW_PIN);
		GPIO_ResetBits(EN_PORT,EN_PIN);
		LCD1602_delay_us(2);
		GPIO_Write(DX_PORT,data);
		LCD1602_delay_us(2);
		GPIO_SetBits(EN_PORT,EN_PIN);
		LCD1602_delay_us(2);
		GPIO_ResetBits(EN_PORT,EN_PIN);
	}
}
/**
*name: LCD1602_Init()
*fun : Һ����ʼ������
*para: void
*ret : void
**/
void LCD1602_Init()
{
	LCD1602_GPIO_Init();
	LCD1602_delay_ms(15);
	LCD1602_WriteData(0x01,1);
	LCD1602_WriteData(0x38,1);
	LCD1602_WriteData(0x38,1);
	LCD1602_WriteData(0x38,1);
	LCD1602_WriteData(0x0e,1);
//	LCD1602_WriteData(0x0c,1);//�رչ��
//	LCD1602_WriteData(0x0f,1);//�����˸
	LCD1602_WriteData(0x01,1);
	LCD1602_WriteData(0x06,1);
//	LCD1602_WriteData(0x07,1);//�����ƶ�
	LCD1602_WriteData(0x80,1);
}

/**
*name: LCD1602_WriteStr(char *p,uint8_t x,uint8_t y)
*fun : д�ַ���
*para: p���ַ����ĳ�ʼ��ַ	x����	y����
*ret : void
**/
void LCD1602_WriteStr(char *p,uint8_t x,uint8_t y)
{
	if(x == 1)
	{
		LCD1602_WriteData(0x80+y-1,1);
	}
	else if(x == 2)
	{
		LCD1602_WriteData(0xc0+y-1,1);
	}
	do
	{
		LCD1602_WriteData(*p,0);
//		LCD1602_delay_ms(1000);//��ʾ������Ч
	}while(*(++p));
}
/**
*name: void LCD1602_WriteNum(float num,uint8_t x, uint8_t y)
*fun : д������
*para: num��������ֵ	x����	y����
*ret : void
**/
void LCD1602_WriteNum(float num,uint8_t x, uint8_t y)
{
	if(x == 1)
	{
		LCD1602_WriteData(0x80+y-1,1);
	}
	else if(x == 2)
	{
		LCD1602_WriteData(0xc0+y-1,1);
	}
	/*��������*/
	uint16_t temp = (uint16_t)num;
	uint8_t i = 0;
	char str;
	while(temp != 0)
	{
		temp /= 10;
		i++;
	}	
	temp = (uint16_t)num;
	while(i != 0)
	{
		str = '0'+ temp/((uint16_t)pow(10,i-1))%10;
		i--;
		LCD1602_WriteData(str,0);
//		LCD1602_delay_ms(1000);//��ʾ������Ч
	}
	/*С������*/
	i = 0;
	float decimal = num - (uint16_t)num;
	if(decimal != 0)//�ж�С�������Ƿ�Ϊ�㣬����ɾ��
	{
		LCD1602_WriteData('.',0);
		decimal *= 100;//��ʾ��λ,����Ҫ����ʾ��˵�������
		uint16_t temp1 = (uint16_t)decimal;
		while(temp1 != 0)
		{
			temp1 /= 10;
			i++;
		}	
		temp1 = (uint16_t)decimal;
		while(i != 0)
		{
			str = '0'+ temp1/((uint16_t)pow(10,(i--)-1))%10;
			LCD1602_WriteData(str,0);
		}
	
	}
	
}




