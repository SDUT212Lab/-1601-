#ifndef _USER_LED_H
#define _USER_LED_H
/*ͷ�ļ�*/
#include "stm32f10x.h"

/*���Ŷ���*/
#define LED_CLKCMD		RCC_APB2PeriphClockCmd
#define LED_CLK				RCC_APB2Periph_GPIOE
#define LED_PORT			GPIOE
#define LED_PIN				GPIO_Pin_5
#define LED_ON				GPIO_ResetBits(LED_PORT,LED_PIN)
#define LED_OFF				GPIO_SetBits(LED_PORT,LED_PIN)

/*��������*/
void LED_Init(void);
void LED_Wenkle(uint32_t ms);
#endif

