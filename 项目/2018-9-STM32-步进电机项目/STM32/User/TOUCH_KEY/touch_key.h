#ifndef _TOUCH_KEY_H
#define _TOUCH_KEY_H

#include "stm32f10x.h"

#define SIG_CLKCMD				RCC_APB2PeriphClockCmd
#define SIG_CLK					RCC_APB2Periph_GPIOA
#define SIG_PORT				GPIOA
#define SIG_PIN					GPIO_Pin_8

#define SIG_EXTILINE			EXTI_Line8
#define SIG_IRQn				EXTI9_5_IRQn
#define SIG_PORTSOURCE			GPIO_PortSourceGPIOA
#define SIG_PINSOURCE			GPIO_PinSource8 
#define Touch_Key_IRQHandler	EXTI9_5_IRQHandler

#define KEY1_CLKCMD				RCC_APB2PeriphClockCmd
#define KEY1_CLK				RCC_APB2Periph_GPIOA
#define KEY1_PORT				GPIOA
#define KEY1_PIN				GPIO_Pin_10

#define KEY1_EXTILINE			EXTI_Line10
#define KEY1_IRQn				EXTI15_10_IRQn
#define KEY1_PORTSOURCE			GPIO_PortSourceGPIOA
#define KEY1_PINSOURCE			GPIO_PinSource10
#define KEY1_IRQHandler			EXTI15_10_IRQHandler


#define SIG						GPIO_ReadInputDataBit(SIG_PORT,SIG_PIN)
#define KEY1					GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)


void Touch_Key_Init(void);
uint8_t Touch_Key_Read_Bit(void);
void KEY_Init(void);

#endif
