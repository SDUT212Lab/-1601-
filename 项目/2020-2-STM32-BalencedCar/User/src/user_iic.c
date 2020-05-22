#include "user_iic.h"
#include "user_delay.h"


void I2C_Init_IO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(I2C_RCC_APBxPeriph_GPIOx,ENABLE);

	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

void I2C_SDA_OUT()
{
     GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}


void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

//产生起始信号
void I2C_Start(void)
{
     I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_Us(4);
	I2C_SDA_L;
	delay_Us(4);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   delay_Us(4);
   I2C_SCL_H;
   I2C_SDA_H;
   delay_Us(4);
}

//主机产生应答信号ACK
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_Us(2);
   I2C_SCL_H;
   delay_Us(2);
   I2C_SCL_L;
}

//主机不产生应答信号NACK
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_Us(2);
   I2C_SCL_H;
   delay_Us(2);
   I2C_SCL_L;
}
//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
uint8_t I2C_Wait_Ack(void)
{
	uint8_t tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_Us(1);
	I2C_SCL_H;
	delay_Us(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
//I2C 发送一个字节
void I2C_Send_Byte(uint8_t txd)
{
	uint8_t i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_Us(2); //发送数据
		I2C_SCL_L;
		delay_Us(2);
	}
}

//I2C 读取一个字节

uint8_t I2C_Read_Byte(void)
{
   uint8_t i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_Us(2);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_Us(1);	
   }
	return receive;
}
