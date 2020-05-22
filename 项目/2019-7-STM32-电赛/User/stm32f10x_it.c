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
#include <math.h>

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


//����
#include "user_usartlcd.h"
#include "user_dc_moto.h"
extern uint8_t fashe_flag;
uint8_t usart_1_receive_data[50];			//�������ݻ�������
uint8_t datapoint = 0;								//�������ݵĸ���
uint8_t Usartlcd_flag = 0;						//������Ϣ������ 1���ٶȿ��ơ�
uint16_t distance_v = 0;
uint16_t angle_v = 0;
uint8_t test_flag = 0;
uint8_t start_flag = 0;
uint8_t dir_flag = 0;
uint8_t dir=0;

void USARLCD_IRQHandler()
{
	if(USART_GetITStatus(USART_USARTLCD,USART_IT_RXNE) != RESET)
	{
		usart_1_receive_data[datapoint] = USART_ReceiveData(USART_USARTLCD);
		if(usart_1_receive_data[datapoint] == 0x0a && usart_1_receive_data[datapoint-1] == 0x0d)  //���ж��ǲ��ǽ��յ������һ���ַ�
		{
//			if() //�жϽ��ܵĵ����ڶ����ַ�
			{
				usart_1_receive_data[datapoint+1] = '\0';  // ��������
				Usartlcd_flag = USARTLCD_DisposeData(usart_1_receive_data); //������Ϣ����
				
				//������Ϣ����
				switch(Usartlcd_flag)
				{
					case 1:
					{
						distance_v = 0;
						distance_v = usart_1_receive_data[4];
						distance_v <<=8;
						distance_v += usart_1_receive_data[3];
					};break;
					case 2:
					{
						angle_v = 0;
						angle_v = usart_1_receive_data[4];
						angle_v <<=8;
						angle_v += usart_1_receive_data[3];
					}break;
					case 3:
					{
						test_flag = 0;
						test_flag = usart_1_receive_data[4];
					}break;
					case 4:
					{
						start_flag = 0;
						start_flag = usart_1_receive_data[5];
					}break;
					case 5:
					{
						dir_flag = usart_1_receive_data[3];
						dir++;
					}break;
					case 6:
					{
						fashe_flag = usart_1_receive_data[5]+1;
					}
					break;
					default:break;
				}
				for(uint8_t i = 0;i<datapoint+1;i++)			//�������
				{
					usart_1_receive_data[i] = 0x00;
				}
				datapoint = 55;
			}
		}
		if(datapoint == 55) 		//��ֹ�����㿪ʼ
			datapoint = 0;
		else
			datapoint++;
		if(datapoint==49)
		{
			datapoint = 0;
		}
		
		USART_ClearFlag(USART_USARTLCD,USART_FLAG_RXNE);
	}
}

//���������
//#include "user_wave.h"
//extern uint32_t Distance;
//extern uint16_t TIM3CH3_CAPTURE_STA,TIM3CH3_CAPTURE_VAL;
///*�������ز������ȡ�ж�*/
//void WAVE_TIM_IRQHandler(void)
//{ 		    		  			    
//	u16 tsr;
//	tsr=WAVE_TIM->SR;
//	if((TIM3CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
//	{
//		if(tsr&0X01)//���
//		{	    
//			if(TIM3CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
//			{
//				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
//				{
//					TIM3CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
//					TIM3CH3_CAPTURE_VAL=0XFFFF;
//				}
//				else 
//					TIM3CH3_CAPTURE_STA++;
//			}	 
//		}
//		if(tsr&0x08)//����3���������¼�
//		{	
//			if(TIM3CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
//			{	  			
//				TIM3CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
//				TIM3CH3_CAPTURE_VAL=TIM3->CCR3;	//��ȡ��ǰ�Ĳ���ֵ.
//				WAVE_TIM->CCER&=~(1<<9);			//CC1P=0 ����Ϊ�����ز���
//			}
//			else  								//��δ��ʼ,��һ�β���������
//			{
//				TIM3CH3_CAPTURE_STA=0;			//���
//				TIM3CH3_CAPTURE_VAL=0;
//				TIM3CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
//				WAVE_TIM->CNT=0;					//���������
//				WAVE_TIM->CCER|=1<<9; 				//CC1P=1 ����Ϊ�½��ز���
//			}		    
//		}			     	    					   
//	}
//	WAVE_TIM->SR=0;//����жϱ�־λ 	     
//}

//��ʱ��
#include "user_general_tim.h"
#include "user_pidcalculate.h"
#include "user_mpu6050.h"
#include "uw.h"
uint32_t Distance = 0;
uint32_t Distance_undisposed[10] = {0};
uint32_t wave_cnt;
uint16_t angle_pid = 0;
uint32_t mpu_time = 0;
PID_TypeDef DUOJI_pid;
uint16_t display_cnt;
void GENERAL_TIM_IRQHandler()
{
	if(TIM_GetITStatus(GENERAL_TIM,TIM_IT_Update) != RESET)
	{
		mpu_time++;
		
		if(mpu_time == 25)
		{
			mpu_time = 0;
			MPU6050_Pose();
			DUOJI_pid.Last_Ed = DUOJI_pid.Ep;
			DUOJI_pid.Ep =  (int)angle_v - Roll;
			DUOJI_pid.Ei += DUOJI_pid.Ep;
			DUOJI_pid.Ed = DUOJI_pid.Ep - DUOJI_pid.Last_Ed;
			angle_pid = PID_Calculate(DUOJI_pid);
			if(angle_pid >1200|| angle_pid <395)
			{
				angle_pid = 400;	
				DUOJI_pid.Last_Ed = 0;
				DUOJI_pid.Ed = 0;
				DUOJI_pid.Ei = 0;
				DUOJI_pid.Ep = 0;
			}
			
		}
		
		TIM_ClearITPendingBit(GENERAL_TIM,TIM_FLAG_Update);
	}
}

#include "user_gpio_interp.h"
extern uint8_t fashe_flag;
extern uint8_t fashe_flag1;
extern uint8_t fashe_flag2;
void Interp1_IRQHandler()
{
	if(EXTI_GetITStatus(SIG1_EXTILINE) != RESET)
	{
		fashe_flag1 = 1;
		fashe_flag = fashe_flag1+fashe_flag2;
		EXTI_ClearITPendingBit(SIG1_EXTILINE);
	}
}

void Interp2_IRQHandler()
{
	if(EXTI_GetITStatus(SIG2_EXTILINE) != RESET)
	{
		fashe_flag2 = 1;
		fashe_flag = fashe_flag1+fashe_flag2;
		EXTI_ClearITPendingBit(SIG2_EXTILINE);
	}
}

//״̬������,1ms
extern uint32_t LED_toogle_cnt;
extern float Pitch,Roll,Yaw; 
extern uint32_t	PreDistance;



#include "user_led.h"
#include "user_mpu6050.h"

void SysTick_Handler(void)
{
	LED_toogle_cnt++;
	wave_cnt++;
	if(display_cnt<50)
		display_cnt++;
	LED_Wenkle(100);
}


#include "user_duoji.h"
uint16_t DUOJI1_Speed_cnt = 0;
uint16_t DUOJI2_Speed_cnt = 0;
void DUOJI1_TIM_IRQHandler()
{
	if(TIM_GetITStatus(DUOJI1_TIM,TIM_IT_Update) != RESET)
	{
		DUOJI1_Speed_cnt--;
		DUOJI2_Speed_cnt--;
		if(DUOJI2_Speed_cnt == 0)
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				TIM_Cmd(DUOJI1_TIM,DISABLE);
		}
		if(DUOJI1_Speed_cnt == 0)
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
				TIM_Cmd(DUOJI1_TIM,DISABLE);
		}
		TIM_ClearITPendingBit(DUOJI1_TIM,TIM_FLAG_Update);
	}
}
