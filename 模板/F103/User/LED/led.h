#ifndef _LED_H
#define _LED_H
/*ͷ�ļ�*/
#include "stm32f10x.h"

/*���Ŷ���*/
#define LED_CLKCMD		RCC_APB2PeriphClockCmd
#define LED_CLK				RCC_APB2Periph_GPIOB
#define LED_PORT			GPIOB
#define LED_PIN				GPIO_Pin_5|GPIO_Pin_4
#define LED_ON				GPIO_ResetBits(LED_PORT,LED_PIN)
#define LED_OFF				GPIO_SetBits(LED_PORT,LED_PIN)

/*��������*/
void LED_Init(void);
void LED_Wenkle(uint32_t ms);
#endif

