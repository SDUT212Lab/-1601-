#include "user_usart.h"

/**
*���ƣ�������������
*���ߣ��³�
*ʱ�䣺2018��9��
*�汾��1.0
*���£�1.0����
	   1.1������С����ʾС��0.1��Bug
	   1.1�����³�ʼ��ʱ����ѡ��baudrate
**/


/**
*name:void USART_delay_us(uint32_t us)
*fun :΢�뼶����ʱ
*para:uint32_t us ΢����
*ret :void
**/
void USART_delay_us(uint32_t us)
{
	for(uint32_t i = 0;i<us;i++)
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
*name:void USART_delay_ms(uint32_t ms)
*fun :���뼶����ʱ
*para:uint32_t ms ������
*ret :void
**/
void USART_delay_ms(uint32_t ms)
{
	for(uint32_t i = 0;i<ms;i++)
	{
		USART_delay_us(1000);
	}
}
/**
*name:void USART_x_NVIC_Init(uint8_t NVIC_IRQChannel,uint8_t USART_x_IRQHandlerPP,uint8_t USART_x_IRQHandlerSP)
*fun :�����ж����ʼ������
*para:NVIC_IRQChannel���ж�Դ	 USART_x_IRQHandler PP����ռ���ȼ�  USART_x_IRQHandlerSP����Ӧ���ȼ�
*ret :void
**/
void USART_x_NVIC_Init(uint8_t NVIC_IRQChannel,uint8_t USART_x_IRQHandlerPP,uint8_t USART_x_IRQHandlerSP)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel = NVIC_IRQChannel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = USART_x_IRQHandlerPP;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = USART_x_IRQHandlerSP;
	NVIC_Init(&NVIC_InitStruct);
}

/**
*name:void USART_x_GPIO_Init(USART_TypeDef* USARTx)
*fun :����GPIO��ʼ������
*para:USARTx�����ں�
*ret :void
**/
void USART_x_GPIO_Init(USART_TypeDef* USARTx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	if(USARTx == USART1)
	{
		USART_1_GPIO_CLKCMD(USART_1_GPIO_CLK,ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = USART_1_TX_GPIO_PIN;
		GPIO_Init(USART_1_TX_GPIO_PORT,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = USART_1_RX_GPIO_PIN;
		GPIO_Init(USART_1_RX_GPIO_PORT,&GPIO_InitStructure);
	}
	else if(USARTx == USART_2)
	{
		USART_2_GPIO_CLKCMD(USART_2_GPIO_CLK,ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = USART_2_TX_GPIO_PIN;
		GPIO_Init(USART_2_TX_GPIO_PORT,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = USART_2_RX_GPIO_PIN;
		GPIO_Init(USART_2_RX_GPIO_PORT,&GPIO_InitStructure);
	}
	else if(USARTx == USART_3)
	{
		USART_3_GPIO_CLKCMD(USART_3_GPIO_CLK,ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = USART_3_TX_GPIO_PIN;
		GPIO_Init(USART_3_TX_GPIO_PORT,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = USART_3_RX_GPIO_PIN;
		GPIO_Init(USART_3_RX_GPIO_PORT,&GPIO_InitStructure);
	}
	else if(USARTx == USART_4)
	{
		USART_4_GPIO_CLKCMD(USART_4_GPIO_CLK,ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = USART_4_TX_GPIO_PIN;
		GPIO_Init(USART_4_TX_GPIO_PORT,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = USART_4_RX_GPIO_PIN;
		GPIO_Init(USART_4_RX_GPIO_PORT,&GPIO_InitStructure);
	}
	else if(USARTx == USART_5)
	{
		USART_5_GPIO_CLKCMD(USART_5_GPIO_CLK,ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = USART_5_TX_GPIO_PIN;
		GPIO_Init(USART_5_TX_GPIO_PORT,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = USART_5_RX_GPIO_PIN;
		GPIO_Init(USART_5_RX_GPIO_PORT,&GPIO_InitStructure);
	}
}
/**
*name:void USART_x_Mode_Init(USART_TypeDef *USARTx)
*fun :����ģʽ��ʼ��
*para:USARTx�����ں�
*ret :void
**/
void USART_x_Mode_Init(USART_TypeDef *USARTx,uint32_t baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	if(USARTx == USART_1)
	{
		USART_1_CLKCMD(USART_1_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = baudrate;
		USART_Init(USART_1,&USART_InitStructure);
//		USART_x_NVIC_Init(USART_1_IRQ,USART_1_IRQHandlerPP,USART_1_IRQHandlerSP);
//		USART_ITConfig(USART_1,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART_1,ENABLE);
	}
	else if(USARTx == USART_2)
	{
		USART_2_CLKCMD(USART_2_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = baudrate;
		USART_Init(USART_2,&USART_InitStructure);
		USART_x_NVIC_Init(USART_2_IRQ,USART_2_IRQHandlerPP,USART_2_IRQHandlerSP);
		USART_ITConfig(USART_2,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART_2,ENABLE);
	}
	else if(USARTx == USART_3)
	{
		USART_3_CLKCMD(USART_3_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = baudrate;
		USART_Init(USART_3,&USART_InitStructure);
		USART_x_NVIC_Init(USART_3_IRQ,USART_3_IRQHandlerPP,USART_3_IRQHandlerSP);
		USART_ITConfig(USART_3,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART_3,ENABLE);
	}
//	else if(USARTx == USART_4)
//	{
//		USART_4_CLKCMD(USART_4_CLK,ENABLE);
//		USART_InitStructure.USART_BaudRate = USART_4_BAUDRATE;
//		USART_Init(USART_4,&USART_InitStructure);
//		USART_x_NVIC_Init(USART_4_IRQ,USART_4_IRQHandlerPP,USART_4_IRQHandlerSP);
//		USART_ITConfig(USART_4,USART_IT_RXNE,ENABLE);
//		USART_Cmd(USART_4,ENABLE);
//	}
//	else if(USARTx == USART_5)
//	{
//		USART_5_CLKCMD(USART_5_CLK,ENABLE);
//		USART_InitStructure.USART_BaudRate = USART_5_BAUDRATE;
//		USART_Init(USART_5,&USART_InitStructure);
//		USART_x_NVIC_Init(USART_5_IRQ,USART_5_IRQHandlerPP,USART_5_IRQHandlerSP);
//		USART_ITConfig(USART_5,USART_IT_RXNE,ENABLE);
//		USART_Cmd(USART_5,ENABLE);
//	}
}

/**
*name:void USART_x_Init(USART_TypeDef *USARTx)
*fun :���ڳ�ʼ��
*para:USARTx�����ں� buad:������
*ret :void
**/
void USART_x_Init(USART_TypeDef *USARTx,uint32_t baudrate)
{
	USART_x_GPIO_Init(USARTx);
	USART_x_Mode_Init(USARTx,baudrate);
}
/**
*name:void USART_x_Send_Byte(USART_TypeDef* USARTx,uint8_t ch)
*fun :���ֽ�
*para:USARTx�����ں�   ch:�ַ�
*ret :void
**/
void USART_x_Send_Byte(USART_TypeDef* USARTx,uint8_t ch)
{	
	USART_GetFlagStatus(USARTx,USART_FLAG_TC);
	USART_ClearFlag(USARTx,USART_FLAG_TC);
	USART_SendData(USARTx,ch);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)== RESET);
	
//	USART_delay_ms(10);//��ʾ������Ч,�����������ڶ�ʧ����
}
/**
*name:void USART_x_Send_String(USART_TypeDef* USARTx,uint8_t *str)
*fun :���ַ���
*para:USARTx�����ں�   *str���ַ���ָ��
*ret :void
**/
void USART_x_Send_String(USART_TypeDef* USARTx,uint8_t *str)
{
	do
	{
		USART_x_Send_Byte(USARTx,*str);
		
	}while(*(++str));
}
/**
*name:void USART_x_Send_Num(USART_TypeDef* USARTx,uint32_t num)
*fun :��32�޷�������
*para:USARTx�����ں�   num������
*ret :void
**/
void USART_x_Send_Num(USART_TypeDef* USARTx,uint32_t num)
{
	uint32_t temp = num;
	uint8_t i = 0;
	uint8_t j = 0;
	if(num == 0)
		USART_x_Send_Byte(USARTx,'0');
	while(temp != 0)
	{
		temp/= 10;
		i++;
	}
	while(j<i)
	{
		USART_x_Send_Byte(USARTx,num/(uint32_t)pow(10,i-j-1)%10+'0');
		j++;
	}
}
/**
*name:void USART_x_Send_Float(USART_TypeDef* USARTx,float num)
*fun :�͸�����
*para:USARTx�����ں�   num������
*ret :void
**/
void USART_x_Send_Float(USART_TypeDef* USARTx,float num)
{
	float zero_dot_one = 0.1;
	//��������
	uint32_t temp = (uint32_t)num;
	if(num<0)
	{
		USART_x_Send_Byte(USARTx,'-');
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
			USART_x_Send_Byte(USARTx,temp/(uint32_t)pow(10,i-j-1)%10+'0');
			j++;
		}
	}
	else
	{
		USART_x_Send_Byte(USARTx,'0');
	}
	//С����
	USART_x_Send_Byte(USARTx,'.');
	//С������
	float temp1 = num - (uint32_t)num;
	float temp2 = temp1;
	uint8_t zero_num = 6;//��ʾС���ĸ���
	i = 0;
	temp1 *= pow(10,zero_num);
	while(temp2 < zero_dot_one && i< zero_num )
	{
		USART_x_Send_Byte(USARTx,'0');
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
		USART_x_Send_Byte(USARTx,temp/(uint32_t)pow(10,i-j-1)%10+'0');
		j++;
	}

}
/**
*name:void USART_x_Display_Menu(USART_TypeDef* USARTx)
*fun :��ʾ�˵����ɱ༭
*para:USARTx�����ں�   
*ret :void
**/
void USART_x_Display_Menu(USART_TypeDef* USARTx)
{
	USART_x_Send_String(USARTx,"\
/***************************************/\n\
/		��ӭʹ��!!!!		/\n\
/		����������!!		/\n\
/***************************************/\n\
");
}
/*���ʹ���жϷ��������뽫���к����ŵ�it.h��*/
/**
*name:void USART_1_IRQHandler()
*fun :�����жϷ�����
*para:void
*ret :void
**/
/*
#include "user_user_usart.h"
uint8_t usart_1_receive_data;
void USART_1_IRQHandler()
{
	if(USART_GetITStatus(USART_1,USART_IT_RXNE) != RESET)
	{
		usart_1_receive_data = USART_ReceiveData(USART_1);
		USART_ClearFlag(USART_1,USART_FLAG_RXNE);
	}
}
*/

/**
*name:void USART_2_IRQHandler()
*fun :�����жϷ�����
*para:void
*ret :void
**/
/*
#include "user_usart.h"
uint8_t usart_2_receive_data;
void USART_2_IRQHandler()
{
	if(USART_GetITStatus(USART_2,USART_IT_RXNE) != RESET)
	{
		usart_2_receive_data = USART_ReceiveData(USART_2);
		USART_ClearFlag(USART_2,USART_FLAG_RXNE);
	}
}
*/
/**
*name:void USART_3_IRQHandler()
*fun :�����жϷ�����
*para:void
*ret :void
**/
/*
#include "user_usart.h"
uint8_t usart_3_receive_data;
void USART_3_IRQHandler()
{
	if(USART_GetITStatus(USART_3,USART_IT_RXNE) != RESET)
	{
		usart_3_receive_data = USART_ReceiveData(USART_3);
		USART_ClearFlag(USART_3,USART_FLAG_RXNE);
	}
}
*/
/**
*name:void USART_4_IRQHandler()
*fun :�����жϷ�����
*para:void
*ret :void
**/
/*
#include "user_usart.h"
uint8_t usart_4_receive_data;
void USART_4_IRQHandler()
{
	if(USART_GetITStatus(USART_4,USART_IT_RXNE) != RESET)
	{
		usart_4_receive_data = USART_ReceiveData(USART_4);
		USART_ClearFlag(USART_4,USART_FLAG_RXNE);
	}
}
*/


