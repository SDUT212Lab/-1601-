#ifndef _GPIO_INTERP_H
#define _GPIO_INTERP_H

#include "stm32f10x.h"

#define SIG_CLKCMD						RCC_APB2PeriphClockCmd
#define SIG_CLK								RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO
#define SIG_PORT							GPIOA
#define SIG_PIN								GPIO_Pin_7

#define SIG_EXTILINE					EXTI_Line7
#define SIG_IRQn							EXTI9_5_IRQn
#define SIG_PORTSOURCE				GPIO_PortSourceGPIOA
#define SIG_PINSOURCE					GPIO_PinSource7
#define Touch_Key_IRQHandler	EXTI9_5_IRQHandler

#define SIG										GPIO_ReadInputDataBit(SIG_PORT,SIG_PIN)

void Touch_Key_Init(void);
uint8_t Touch_Key_Read_Bit(void);

#endif
