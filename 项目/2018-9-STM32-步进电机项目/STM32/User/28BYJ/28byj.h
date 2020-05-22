#ifndef _28BYJ_H
#define _28BYJ_H

#include "stm32f10x.h"

#define IN1_CLK			RCC_APB2Periph_GPIOB
#define IN1_CLKCMD		RCC_APB2PeriphClockCmd
#define IN1_PORT		GPIOB
#define IN1_PIN			GPIO_Pin_0

#define IN2_CLK			RCC_APB2Periph_GPIOB
#define IN2_CLKCMD		RCC_APB2PeriphClockCmd
#define IN2_PORT		GPIOB
#define IN2_PIN			GPIO_Pin_1

#define IN3_CLK			RCC_APB2Periph_GPIOB
#define IN3_CLKCMD		RCC_APB2PeriphClockCmd
#define IN3_PORT		GPIOB
#define IN3_PIN			GPIO_Pin_10

#define IN4_CLK			RCC_APB2Periph_GPIOB
#define IN4_CLKCMD		RCC_APB2PeriphClockCmd
#define IN4_PORT		GPIOB
#define IN4_PIN			GPIO_Pin_11

#define IN1H			GPIO_SetBits(IN1_PORT,IN1_PIN)
#define IN1L			GPIO_ResetBits(IN1_PORT,IN1_PIN)

#define IN2H			GPIO_SetBits(IN2_PORT,IN2_PIN)
#define IN2L			GPIO_ResetBits(IN2_PORT,IN2_PIN)

#define IN3H			GPIO_SetBits(IN3_PORT,IN3_PIN)
#define IN3L			GPIO_ResetBits(IN3_PORT,IN3_PIN)

#define IN4H			GPIO_SetBits(IN4_PORT,IN4_PIN)
#define IN4L			GPIO_ResetBits(IN4_PORT,IN4_PIN)

void Moto_28BYJ_Init(void);
void Moto_28BYJ_Run_Sin4(uint8_t speed);
void Moto_28BYJ_Run_Dou4(uint8_t speed);
void Moto_28BYJ_Run_Sin8(uint8_t speed);
void Moto_28BYJ_Run_xCri(uint8_t speed ,double x);

#endif
