#include "user_blue_tooth.h"

/**
*���ƣ�����������������
*���ߣ��³�
*ʱ�䣺2018��8��
*�汾��1.0
*���£�1.0��
**/

/**
*name:Blue_Tooth_NVIC_Init()
*fun :�����ж����ȼ����ú���
*para:void
*ret :void
**/
void Blue_Tooth_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}
/**
*name:Blue_Tooth_GPIO_Init()
*fun :����IO���ó�ʼ��
*para:void
*ret :void
**/
void Blue_Tooth_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	TX_CLKCMD_x(TX_CLK_x,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = TX_PIN_x;
	GPIO_Init(TX_PORT_x,&GPIO_InitStruct);
	
	RX_CLKCMD_x(RX_CLK_x,ENABLE);
	GPIO_InitStruct.GPIO_Pin = RX_PIN_x;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RX_PORT_x,&GPIO_InitStruct);
}
/**
*name:Blue_Tooth_USART_Init()
*fun :�������ڳ�ʼ��
*para:void
*ret :void
**/
void Blue_Tooth_USART_Init()
{
	USART_InitTypeDef USART_InitStruct;
	
	USART_CLKCMD_x(USART_CLK_x,ENABLE);	
	USART_InitStruct.USART_BaudRate = USART_BuadRate_x;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity  = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART_x,&USART_InitStruct);
	USART_Cmd(USART_x,ENABLE);

}
/**
*name:Blue_Tooth_Init()
*fun :������ʼ��
*para:void
*ret :void
**/
void Blue_Tooth_Init()
{
	Blue_Tooth_GPIO_Init();
	Blue_Tooth_USART_Init();
	Blue_Tooth_NVIC_Init();
	USART_ITConfig(USART_x,USART_IT_RXNE,ENABLE);

}
/**
*name:USART_Send_Byte(uint16_t ch)
*fun :��������16λ�ַ�
*para:void
*ret :void
**/
void USART_Send_Byte(uint16_t ch)
{
	USART_SendData(USART_x,ch);
	while(USART_GetFlagStatus(USART_x,USART_FLAG_TXE) == RESET);
}
/**
*name:USART_Send_String(char *str)
*fun :���������ַ���
*para:�ַ���
*ret :void
**/
void USART_Send_String(char *str)
{
	uint8_t k=0;
	do
	{
		USART_Send_Byte(*(str+k));
		k++;
	}
	while(*(str+k) != '\0');
	while(USART_GetFlagStatus(USART_x,USART_FLAG_TC));
}
/**
*name:Blue_Tooth_IRQHandler_1(void)
*fun :�����жϷ�����
*para:�ַ���
*ret :void
**/
//uint8_t receive_data;
//void Blue_Tooth_IRQHandler_1(void)
//{
//	if(USART_GetITStatus(USART_1,USART_IT_RXNE) != RESET)
//	{
//		receive_data = USART_ReceiveData(USART_1);
//		USART_SendData(USART_1,receive_data);
//	}
//}
