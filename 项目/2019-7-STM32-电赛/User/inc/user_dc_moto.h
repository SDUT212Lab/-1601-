#ifndef _USER_DC_MOTO_H
#define _USER_DC_MOTO_H

#include "stm32f10x.h"

//电机1的相关端口
#define DCMOTO1_IN0_CLKCMD						RCC_APB2PeriphClockCmd
#define DCMOTO1_IN0_CLK								RCC_APB2Periph_GPIOA
#define DCMOTO1_IN0_PORT							GPIOA
#define DCMOTO1_IN0_PIN								GPIO_Pin_0
#define DCMOTO1_IN1_CLKCMD						RCC_APB2PeriphClockCmd
#define DCMOTO1_IN1_CLK								RCC_APB2Periph_GPIOA
#define DCMOTO1_IN1_PORT							GPIOA
#define DCMOTO1_IN1_PIN								GPIO_Pin_1
#define DCMOTO1_CLKWISE								GPIO_ResetBits(DCMOTO1_IN0_PORT,DCMOTO1_IN0_PIN);GPIO_SetBits(DCMOTO1_IN1_PORT,DCMOTO1_IN1_PIN);
#define DCMOTO1_ANTICLKWISE						GPIO_SetBits(DCMOTO1_IN0_PORT,DCMOTO1_IN0_PIN);GPIO_ResetBits(DCMOTO1_IN1_PORT,DCMOTO1_IN1_PIN);
#define DCMOTO1_STOP									GPIO_SetBits(DCMOTO1_IN0_PORT,DCMOTO1_IN0_PIN);GPIO_SetBits(DCMOTO1_IN1_PORT,DCMOTO1_IN1_PIN);

#define MOTO_TIM                   		TIM3
#define MOTO_TIM_APBxClock_FUN    		RCC_APB1PeriphClockCmd
#define MOTO_TIM_CLK              		RCC_APB1Periph_TIM3
#define MOTO_TIM_Period            		5999 //最低15
#define MOTO_TIM_Prescaler         		71
#define MOTO_TIM_CH1_GPIO_CLK      		RCC_APB2Periph_GPIOA
#define MOTO_TIM_CH1_PORT          		GPIOA
#define MOTO_TIM_CH1_PIN           		GPIO_Pin_6

void DC_Moto_Init(void);
void DC_Moto_Speed(uint16_t speed);
#endif
