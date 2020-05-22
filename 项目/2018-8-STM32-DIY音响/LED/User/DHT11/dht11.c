#include "dht11.h"
static uint8_t HTdata[5] = {0,0,0,0,1};
/**
*���ƣ�DHT11�¶ȴ�������������
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.0
*���£�1.0����
*	   1.1�����º궨�壬��ֹ�ظ�
**/

/**
*name:DHT11_delay_us(uint16_t us)
*fun :ʵ�ֽ�Ϊ��ȷ��us��ʱ
*para:us��us��
*ret :void
**/
void DHT11_delay_us(uint16_t us)
{
	for(int i = 0;i<us;i++)
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
*name:DHT11_delay_ms(uint16_t ms)
*fun :ʵ�ֽ�Ϊ��ȷ��ms��ʱ
*para:ms��ms��
*ret :void
**/
void  DHT11_delay_ms(uint16_t ms)
{
	for(int i = 0;i<ms;i++)
	{
		DHT11_delay_us(1000);
	}

}
/**
*name:DHT11_GPIO_Mode_Out()
*fun :GPIO�������ģʽ
*para:void
*ret :void
**/
void DHT11_GPIO_Mode_Out()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	DHT11_DATA_CLKCMD(DHT11_DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = DHT11_DATA_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_DATA_PORT,&GPIO_InitStruct);
}
/**
*name:DHT11_GPIO_Mode_IN()
*fun :GPIO������ģʽ
*para:void
*ret :void
**/
void DHT11_GPIO_Mode_IN()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	DHT11_DATA_CLKCMD(DHT11_DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = DHT11_DATA_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_DATA_PORT,&GPIO_InitStruct);
}
/**
*name:DHT11_Read_Bit(void)
*fun :��ȡλ
*para:void
*ret :λֵ
**/
uint8_t DHT11_Read_Bit()
{
    while (DHT11_DATA == RESET);
    DHT11_delay_us(40);
    if (DHT11_DATA == SET)
    {
        while (DHT11_DATA == SET);
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
*name:DHT11_Init()
*fun :DHT11��ʼ��
*para:void
*ret :void
**/
void DHT11_Init()
{
	DHT11_GPIO_Mode_Out();
	DHT11_DATAH;
	DHT11_delay_ms(1000);
}
/**
*name:DHT11_Read_Data()
*fun :DHT11��ȡ���ݣ������������ֵһֱΪ0��˵������
*para:void
*ret :У����ȷ����1������Ϊ0
**/
uint8_t DHT11_Read_Data()
{

	{
		DHT11_GPIO_Mode_Out();
		DHT11_DATAL;
		DHT11_delay_ms(18);
		DHT11_DATAH;
		DHT11_delay_us(30);
		DHT11_GPIO_Mode_IN();
		if(DHT11_DATA == Bit_RESET)
		{
			while(DHT11_DATA == Bit_RESET);
			while(DHT11_DATA == Bit_SET);
			for(int i = 0;i<5;i++)
			{
				for(int j = 0;j<8;j++)
				{
					HTdata[i] <<= 1;
					HTdata[i] |= DHT11_Read_Bit();
				}
			}
			while(DHT11_DATA == Bit_RESET);
			DHT11_GPIO_Mode_Out();
			DHT11_DATAH;
		}	
	}
	if(HTdata[0]+HTdata[1]+HTdata[2]+HTdata[3] == HTdata[4])
		return 1;
	else
	{
		HTdata[0]=0;
		HTdata[1]=0;
		HTdata[2]=0;
		HTdata[3]=0;
	}

}
/**
*name:DHT11_Read_Humidity()
*fun :����ʪ��ֵ
*para:void
*ret :ʪ��ֵ
**/
float DHT11_Read_Humidity()
{
	float temp = HTdata[1]; //С������
	uint8_t i =0;
	while(HTdata[1] !=0)
	{
		HTdata[1]/=10;
		i++;
	}
	temp /= pow(10,i);
	return	HTdata[0]+temp;
}
/**
*name:DHT11_Read_Humidity()
*fun :�����¶�ֵ
*para:void
*ret :�¶�ֵ
**/
float DHT11_Read_Temper()
{
	float temp = HTdata[3]; //С������
	uint8_t i =0;
	while(HTdata[3] !=0)
	{
		HTdata[3]/=10;
		i++;
	}
	temp /= pow(10,i);
	return	HTdata[2]+temp;
}


