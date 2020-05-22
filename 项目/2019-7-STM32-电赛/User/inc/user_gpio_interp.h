#ifndef _TOUCH_KEY_H
#define _TOUCH_KEY_H

#include "stm32f10x.h"

#define SIG1_CLKCMD						RCC_APB2PeriphClockCmd
#define SIG1_CLK							RCC_APB2Periph_GPIOA
#define SIG1_PORT							GPIOA
#define SIG1_PIN							GPIO_Pin_5

#define SIG1_EXTILINE					EXTI_Line5
#define SIG1_IRQn							EXTI9_5_IRQn
#define SIG1_PORTSOURCE				GPIO_PortSourceGPIOA
#define SIG1_PINSOURCE				GPIO_PinSource5
#define Interp1_IRQHandler		EXTI9_5_IRQHandler


#define SIG1									GPIO_ReadInputDataBit(SIG2_PORT,SIG2_PIN)

//2
#define SIG2_CLKCMD						RCC_APB2PeriphClockCmd
#define SIG2_CLK							RCC_APB2Periph_GPIOA
#define SIG2_PORT							GPIOA
#define SIG2_PIN							GPIO_Pin_11

#define SIG2_EXTILINE					EXTI_Line11
#define SIG2_IRQn							EXTI15_10_IRQn
#define SIG2_PORTSOURCE				GPIO_PortSourceGPIOA
#define SIG2_PINSOURCE				GPIO_PinSource11


#define Interp2_IRQHandler		EXTI15_10_IRQHandler
#define SIG2									GPIO_ReadInputDataBit(SIG2_PORT,SIG2_PIN)

void Interp_Init(void);
uint8_t Interp_Read_Bit(void);

#endif
