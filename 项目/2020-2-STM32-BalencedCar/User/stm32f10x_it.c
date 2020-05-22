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
extern uint32_t Motor1_cnt;
extern uint32_t Motor2_cnt;
extern uint32_t Motor1_Speed;
extern uint32_t Motor2_Speed;
extern uint32_t mpu6050_cnt;
extern uint8_t init_flag;
#include "user_led.h"
#include "user_motor.h"
#include "user_mpu6050.h"
#include "user_pidcalculate.h"
#include "user_usart.h"
float angle_pid = 0;
PID_TypeDef DUOJI_pid;
void SysTick_Handler(void)
{
	if(init_flag == 1)
	{
		LED_toogle_cnt++;
		Motor1_cnt++;
		Motor2_cnt++;
		if(Motor1_cnt == 30)
			Motor1_cnt = 0;
		if(Motor2_cnt == 30)
			Motor2_cnt = 0;
		LED_Wenkle(100);
		Motor_Set_Speed();
		
		{
			mpu6050_cnt = 0;
			MPU6050_Pose();
			DUOJI_pid.Last_Ed = DUOJI_pid.Ep; //
			DUOJI_pid.Ep =   0 - Pitch;
			DUOJI_pid.Ei += DUOJI_pid.Ep;
			DUOJI_pid.Ed = DUOJI_pid.Ep - DUOJI_pid.Last_Ed;
			angle_pid = PID_Calculate(DUOJI_pid);	
			
			
//			USART_x_Send_Float(USART1,Pitch);
//			USART_x_Send_Byte(USART1,'\r');
//			USART_x_Send_Byte(USART1,'\n');
			
			USART_x_Send_Float(USART1,angle_pid);
			USART_x_Send_Byte(USART1,'\r');
			USART_x_Send_Byte(USART1,'\n');
		}
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


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
/**
*name:Blue_Tooth_IRQHandler_1(void)
*fun :蓝牙中断服务函数
*para:字符串
*ret :void
**/
#include "user_bluetooth.h"
uint8_t receive_data;
void Blue_Tooth_IRQHandler_1(void)
{
	if(USART_GetITStatus(USART_x,USART_IT_RXNE) != RESET)
	{
		receive_data = USART_ReceiveData(USART_x);
	}
}
