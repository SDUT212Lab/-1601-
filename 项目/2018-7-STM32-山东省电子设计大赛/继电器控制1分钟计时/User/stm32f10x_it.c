/**
  ******************************************************************************
  * @file    ADC/3ADCs_DMA/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_led.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "bsp_led.h"
#include "beep.h"
#include "USART.h"
#include "exit.h"
#include "dma.h"

 volatile uint32_t ADC2_Value;
 uint8_t vol = 0;
 volatile uint32_t cnt = 0;
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_3ADCs_DMA
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t ADC2ConvertedValue;

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
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(SysTick ->CTRL &1)
	{
		cnt++;
	}
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

void EXTI9_5_IRQHandler(void) //表示从5-9的中断服务函数 ，EXTI15_10_IRQHander()表示从15到10的中断服务函数 EXTI1-4
	//写成EXTIx_IQRHandler
{
	if(EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		
		LED(0,2);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 0);
		delay_ms(150);
		
		EXTI_ClearITPendingBit(EXTI_Line6);//清楚中断位
	}
	if(EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		
		LED(1,2);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0);
		delay_ms(150);
		
		EXTI_ClearITPendingBit(EXTI_Line7);//清楚中断位
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		
		vol++;
		if(vol>=20)
		{
			vol = 0;
		}
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 0);
		delay_ms(150);
	
		
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	
}

void USART1_IRQHandler(void)
{
	uint8_t Temp;
	
	//电脑过来发数据了，中断才开始相应。
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE ) == SET)
	{
		Temp = USART_ReceiveData(USART1);
		switch(Temp)
		{
			case '0':LED_Init();LED(0,2);printf("转换LED0");break;
			case '1':LED_Init();LED(1,2);printf("转换LED1");break;
			case '2':LED_Init();LED(2,2);printf("转换LED2");break;
			case '3':BEEP_Init();BEEP_ON;printf("打开BEEP");break;
			case '4':BEEP_Init();BEEP_OFF;printf("关闭BEEP");break;
			case '5':LED_Init();EXIT_PB6_Init(ENABLE);EXIT_PB7_Init(ENABLE);printf("按键中断");break;
			case '6':LED_Init();EXIT_PB6_Init(DISABLE);EXIT_PB7_Init(DISABLE);printf("关闭中断IT");break;
			case '7':Print_Menu();break;
			case '8':USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);break;
			case '9':printf("电动机加速");if((vol++)>= 20) vol =0;break;
			
		}
		putchar('\n');
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
	}
//	if(USART_GetFlagStatus(USART1,USART_FLAG_TC) == SET)
//	{

//		printf("发送完成,寄存器为空");
//		LED(2,2);
//		USART_ClearFlag(USART1,USART_FLAG_TXE);
//		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
//	}
//	if(USART_GetFlagStatus(USART1,USART_FLAG_PE) == SET)
//	{
//		printf("错误");
//	}

}

//void ADC1_2_IRQHandler()
//{
//	
//	 if(ADC_GetITStatus(ADC2,ADC_IT_EOC) == SET)
//	 {
//		ADC2_Value = ADC_GetConversionValue(ADC2);
//	 }
//	 
//	 ADC_ClearITPendingBit(ADC2,ADC_IT_EOC);
//	 
//}

/**
	注意：所有的中断服务函数名都在启动文件中
**/

