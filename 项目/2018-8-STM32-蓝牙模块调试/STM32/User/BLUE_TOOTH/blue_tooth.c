#include "blue_tooth.h"
#include "stdio.h"
void Blue_Tooth_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
}
void Blue_Tooth_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	TX_CLKCMD_1(TX_CLK_1,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = TX_PIN_1;
	GPIO_Init(TX_PORT_1,&GPIO_InitStruct);
	
	RX_CLKCMD_1(RX_CLK_1,ENABLE);
	GPIO_InitStruct.GPIO_Pin = RX_PIN_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RX_PORT_1,&GPIO_InitStruct);
	
	TX_CLKCMD_2(TX_CLK_2,ENABLE);
	GPIO_InitStruct.GPIO_Pin =TX_PIN_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(TX_PORT_2,&GPIO_InitStruct);
	
	RX_CLKCMD_2(RX_CLK_2,ENABLE);
	GPIO_InitStruct.GPIO_Pin = RX_PIN_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RX_PORT_2,&GPIO_InitStruct);
}

void Blue_Tooth_USART_Init()
{
	USART_InitTypeDef USART_InitStruct;
	
	USART_CLKCMD_1(USART_CLK_1,ENABLE);	
	USART_InitStruct.USART_BaudRate = USART_1_BuadRate;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity  = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART_1,&USART_InitStruct);
	USART_Cmd(USART_1,ENABLE);
	
	USART_CLKCMD_2(USART_CLK_2,ENABLE);
	USART_Init(USART_2,&USART_InitStruct);
	USART_Cmd(USART_2,ENABLE);
}

void Blue_Tooth_Init()
{
	Blue_Tooth_GPIO_Init();
	Blue_Tooth_USART_Init();
	Blue_Tooth_NVIC_Init();
	USART_ITConfig(USART_1,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART_2,USART_IT_RXNE,ENABLE);
}

void USART_Send_Byte_1(uint8_t ch)
{
	USART_SendData(USART_1,ch);
	while(USART_GetFlagStatus(USART_1,USART_FLAG_TXE) == RESET);

}

void USART_Send_String_1(char *str)
{
	uint8_t k=0;
	do
	{
		USART_Send_Byte_1(*(str+k));
		k++;
	}
	while(*(str+k) != '\0');
	while(USART_GetFlagStatus(USART_1,USART_FLAG_TC));
}

void USART_Send_Byte_2(USART_TypeDef* pUSART,uint8_t ch)
{
	USART_SendData(pUSART,ch);
	while(USART_GetFlagStatus(pUSART,USART_FLAG_TXE) == RESET);

}

void USART_Send_String_2(USART_TypeDef* pUSART,char *str)
{
	
	uint8_t k=0;
	do
	{
		USART_Send_Byte_2(USART_1,*(str+k));
		k++;
	}
	while(*(str+k) != '\0');
	while(USART_GetFlagStatus(pUSART,USART_FLAG_TC));
}


//void Blue_Tooth_IRQHandler_1(void)
//{
//	if(USART_GetITStatus(USART_1,USART_IT_RXNE) != RESET)
//	{
//		receive_data = USART_ReceiveData(USART_1);
//		USART_SendData(USART_1,receive_data);
//	}
//}
