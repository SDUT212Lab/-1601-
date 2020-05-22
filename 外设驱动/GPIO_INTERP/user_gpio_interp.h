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
#define Interp_IRQHandler		EXTI9_5_IRQHandler

#define SIG						GPIO_ReadInputDataBit(SIG_PORT,SIG_PIN)

void Interp_Init(void);
uint8_t Interp_Read_Bit(void);

#endif
