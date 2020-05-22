#include "usart.h"


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

void USART_x_Mode_Init(USART_TypeDef *USARTx)
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
		USART_InitStructure.USART_BaudRate = USART_1_BAUDRATE;
		USART_Init(USART_1,&USART_InitStructure);
		USART_Cmd(USART_1,ENABLE);
	}
	else if(USARTx == USART_2)
	{
		USART_2_CLKCMD(USART_2_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = USART_2_BAUDRATE;
		USART_Init(USART_2,&USART_InitStructure);
		USART_Cmd(USART_2,ENABLE);
	}
	else if(USARTx == USART_3)
	{
		USART_3_CLKCMD(USART_3_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = USART_3_BAUDRATE;
		USART_Init(USART_3,&USART_InitStructure);
		USART_Cmd(USART_3,ENABLE);
	}
	else if(USARTx == USART_4)
	{
		USART_4_CLKCMD(USART_4_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = USART_4_BAUDRATE;
		USART_Init(USART_3,&USART_InitStructure);
		USART_Cmd(USART_4,ENABLE);
	}
	else if(USARTx == USART_5)
	{
		USART_5_CLKCMD(USART_5_CLK,ENABLE);
		USART_InitStructure.USART_BaudRate = USART_5_BAUDRATE;
		USART_Init(USART_5,&USART_InitStructure);
		USART_Cmd(USART_5,ENABLE);
	}
}


void USART_x_Init(USART_TypeDef *USARTx)
{
	USART_x_GPIO_Init(USARTx);
	USART_x_Mode_Init(USARTx);
}

//int fputc(int ch, FILE *f)
//{
//		/* 发送一个字节数据到串口 */
//		USART_SendData(USART1, (uint8_t) ch);
//		
//		/* 等待发送完毕 */
//		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
//	
//		return (ch);
//}

/////重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
//{
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		return (int)USART_ReceiveData(USART1);
//}


