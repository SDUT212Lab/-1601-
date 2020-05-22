#include "LCD1602.h"
/**
*���ƣ�LCD1602Һ����������
*���ߣ��³�
*ʱ�䣺2018��10��
*�汾��1.0
*���£�1.0����
	   1.1��1.����С����ʾС��0.1��Bug 2.��ȷ��ʱʱ��
**/
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
	
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();

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
		LCD1602_delay_us(1000);
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
//		LCD1602_delay_ms(1500);//��ʾ������Ч
		
		
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
	float zero_dot_one = 0.1;
	//��������
	uint32_t temp = (uint32_t)num;
	if(num<0)
	{
		LCD1602_WriteData('-',0);
	}
	uint8_t i = 0;
	uint8_t j = 0;
	if(temp != 0)
	{
		while(temp != 0)
		{
			temp/= 10;
			i++;
		}
		temp = (uint32_t)num;
		while(j<i)
		{
			LCD1602_WriteData(temp/(uint32_t)pow(10,i-j-1)%10+'0',0);
			j++;
		}
	}
	else
	{
		LCD1602_WriteData('0',0);
	}
	//С����
	LCD1602_WriteData('.',0);
	//С������
	float temp1 = num - (uint32_t)num;
	float temp2 = temp1;
	uint8_t zero_num = 5;//��ʾС���ĸ���
	i = 0;
	temp1 *= pow(10,zero_num);
	while(temp2 < zero_dot_one && i< zero_num )
	{
		LCD1602_WriteData('0',0);
		zero_dot_one/=10.0;
		i++;
	}
	temp = (uint32_t)temp1;
	i = 0;j = 0;
	while(temp != 0)
	{
		temp/= 10;
		i++;
	}
	temp = (uint32_t)temp1;
	while(j<i)
	{
		LCD1602_WriteData(temp/(uint32_t)pow(10,i-j-1)%10+'0',0);
		j++;
	}

	
}




