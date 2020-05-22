/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}
//状态机参数
extern uint32_t LED_toogle_cnt;
#include "user_led.h"
#include "user_cmd.h"
uint8_t usart_2_disposedata = 0;
uint8_t usart_2_receive_data[300];
void SysTick_Handler(void)
{
	LED_toogle_cnt++;
	LED_Wenkle(100);
	if(usart_2_disposedata == 1)
	{
		Cmd_Printf();
		for(uint16_t i = 0;i<=299;i++)
		{
			usart_2_receive_data[i]=0x00;
		}
		usart_2_disposedata = 0;
	}
}
/**
*name:void USART_1_IRQHandler()
*fun :串口中断服务函数
*para:void
*ret :void
**/
#include "user_usart.h"
#include "user_usartlcd.h"
uint8_t usart_1_receive_data;
void USART_1_IRQHandler()
{
	if(USART_GetITStatus(USART_1,USART_IT_RXNE) != RESET)
	{
		usart_1_receive_data = USART_ReceiveData(USART_1);
		USART_ClearFlag(USART_1,USART_FLAG_RXNE);
	}
}

uint32_t usart_2_word_cnt = 0;

void USART_2_IRQHandler()
{
	if(USART_GetITStatus(USART_2,USART_IT_RXNE) != RESET )
	{
		usart_2_receive_data[usart_2_word_cnt] = USART_ReceiveData(USART_2);
		if(usart_2_disposedata == 0)
		{
			if(usart_2_receive_data[usart_2_word_cnt] == 0x0a && usart_2_receive_data[usart_2_word_cnt-1] == 0x0d )
			{
				usart_2_receive_data[usart_2_word_cnt] = 0x00;
				usart_2_receive_data[usart_2_word_cnt-1] = 0x00;
				usart_2_disposedata = 1;
				usart_2_word_cnt = 0;
			}
			else
			{
				usart_2_word_cnt++;
				if(usart_2_word_cnt == 60)
				{
					usart_2_word_cnt = 0;
				}
			}
		}
		
		USART_ClearFlag(USART_2,USART_FLAG_RXNE);
	}
}
