/**
 *���ƣ�STM32VET6ģ��
 *���ߣ��³�
 *ʱ�䣺2018��9��
 *�汾��1.3
 *���£�1.0����
	    1.1���޸Ĳ���Reset and Run
	    1.2�����ϵͳ�δ���ʱ
			1.3�����LED�������������
			1.4�����USART�⣬�������
**/

/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "systick.h"
#include "usart.h"
#include "matrix_key.h"
#include "math.h"
#include "lock_display.h"
#include "28byj.h"
#include "general_tim.h"
#include "gpio_interp.h"
#include "ht1261.h"
#include "mg90s.h"

extern uint32_t input_time;

/*ȫ��״̬������*/
uint32_t LED_toogle_cnt = 0;
uint32_t MG90S_toogle_cnt = 0;
uint32_t Matrix_KEY_cnt = 0;

/*������*/
int main(void)
{	
	SysTick_Init(1000); //��ʼ��״̬��
//	NVIC_SetPriority(SysTick_IRQn,(1<<__NVIC_PRIO_BITS)-15);
	MG90S_Init();
	GENERAL_TIM_Init();
	HT1261_Init();
	HT1261_Display_Data(0,5,0,0,0);
	LED_Init();
	Matrix_Init();
	while(1)
	{

		/*write your code here*/
		/*LED��˸*/
		LED_Wenkle(50);
	}
	
}

