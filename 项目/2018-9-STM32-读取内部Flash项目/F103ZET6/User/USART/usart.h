#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"
#include <stdio.h>

/** 
    * ���ں궨�壬��ͬ�Ĵ��ڹ��ص����ߺ�IO��һ������ֲʱ��Ҫ�޸��⼸����
	* 1-�޸�����ʱ�ӵĺ꣬uart1���ص�apb2���ߣ�����uart���ص�apb1����
	* 2-�޸�GPIO�ĺ�
  */
		

#define  USART_1                    USART1
#define  USART_1_CLK                RCC_APB2Periph_USART1
#define  USART_1_CLKCMD       	    RCC_APB2PeriphClockCmd
#define  USART_1_BAUDRATE           115200
#define  USART_1_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  USART_1_GPIO_CLKCMD   	    RCC_APB2PeriphClockCmd    
#define  USART_1_TX_GPIO_PORT       GPIOA   
#define  USART_1_TX_GPIO_PIN        GPIO_Pin_9
#define  USART_1_RX_GPIO_PORT       GPIOA
#define  USART_1_RX_GPIO_PIN        GPIO_Pin_10
#define  USART_1_IRQ                USART1_IRQn
#define  USART_1_IRQHandler         USART1_IRQHandler

#define  USART_2                    USART2
#define  USART_2_CLK                RCC_APB1Periph_USART2
#define  USART_2_CLKCMD		        RCC_APB1PeriphClockCmd
#define  USART_2_BAUDRATE           115200
#define  USART_2_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  USART_2_GPIO_CLKCMD	    RCC_APB2PeriphClockCmd 
#define  USART_2_TX_GPIO_PORT       GPIOA   
#define  USART_2_TX_GPIO_PIN        GPIO_Pin_2
#define  USART_2_RX_GPIO_PORT       GPIOA
#define  USART_2_RX_GPIO_PIN        GPIO_Pin_3
#define  USART_2_IRQ                USART2_IRQn
#define  USART_2_IRQHandler         USART2_IRQHandler


#define  USART_3                    USART3
#define  USART_3_CLK                RCC_APB1Periph_USART3
#define  USART_3_CLKCMD		        RCC_APB1PeriphClockCmd
#define  USART_3_BAUDRATE           115200
#define  USART_3_GPIO_CLK           RCC_APB2Periph_GPIOB
#define  USART_3_GPIO_CLKCMD	    RCC_APB2PeriphClockCmd 
#define  USART_3_TX_GPIO_PORT       GPIOB   
#define  USART_3_TX_GPIO_PIN        GPIO_Pin_10
#define  USART_3_RX_GPIO_PORT       GPIOB
#define  USART_3_RX_GPIO_PIN        GPIO_Pin_11
#define  USART_3_IRQ                USART3_IRQn
#define  USART_3_IRQHandler         USART3_IRQHandler

#define  USART_4                    UART4
#define  USART_4_CLK                RCC_APB1Periph_UART4
#define  USART_4_CLKCMD		        RCC_APB1PeriphClockCmd
#define  USART_4_BAUDRATE           115200
#define  USART_4_GPIO_CLK           RCC_APB2Periph_GPIOC
#define  USART_4_GPIO_CLKCMD	    RCC_APB2PeriphClockCmd  
#define  USART_4_TX_GPIO_PORT       GPIOC   
#define  USART_4_TX_GPIO_PIN        GPIO_Pin_10
#define  USART_4_RX_GPIO_PORT       GPIOC
#define  USART_4_RX_GPIO_PIN        GPIO_Pin_11
#define  USART_4_IRQ                USART4_IRQn
#define  USART_4_IRQHandler         USART4_IRQHandler



#define  USART_5                    UART5
#define  USART_5_CLK                RCC_APB1Periph_UART5
#define  USART_5_CLKCMD		        RCC_APB1PeriphClockCmd
#define  USART_5_BAUDRATE           115200
#define  USART_5_GPIO_CLK           RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD
#define  USART_5_GPIO_CLKCMD	    RCC_APB2PeriphClockCmd
#define  USART_5_TX_GPIO_PORT       GPIOC   
#define  USART_5_TX_GPIO_PIN        GPIO_Pin_12
#define  USART_5_RX_GPIO_PORT       GPIOD
#define  USART_5_RX_GPIO_PIN        GPIO_Pin_2
#define  USART_5_IRQ                USART5_IRQn
#define  USART_5_IRQHandler         USART5_IRQHandler

void USART_x_Init(USART_TypeDef *USARTx);
void USART_x_Send_Byte(USART_TypeDef* pUSARTx,uint8_t ch);
void USART_x_Send_String(USART_TypeDef* pUSARTx,uint8_t *str);
void USART_Config(void);
	
#endif
