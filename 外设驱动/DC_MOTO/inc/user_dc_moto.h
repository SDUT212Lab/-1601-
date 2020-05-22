#ifndef _USER_DC_MOTO_H
#define _USER_DC_MOTO_H

#include "stm32f10x.h"

#define IN1 1
#define IN2 1
#define IN3 1
#define IN4 1
#define EN1 1
#define EN2 1

#if IN1

#define IN1_CLKCMD			RCC_APB2PeriphClockCmd
#define IN1_CLK				RCC_APB2Periph_GPIOA
#define IN1_PORT			GPIOA
#define IN1_PIN				GPIO_Pin_0
#define IN1_H				GPIO_SetBits(IN1_PORT,IN1_PIN);
#define IN1_L				GPIO_ResetBits(IN1_PORT,IN1_PIN);

#endif


#if IN2

#define IN2_CLKCMD			RCC_APB2PeriphClockCmd
#define IN2_CLK				RCC_APB2Periph_GPIOA
#define IN2_PORT			GPIOA
#define IN2_PIN				GPIO_Pin_1
#define IN2_H				GPIO_SetBits(IN2_PORT,IN2_PIN);
#define IN2_L				GPIO_ResetBits(IN2_PORT,IN2_PIN);

#endif

#if EN1

#define EN1_CLKCMD			RCC_APB2PeriphClockCmd
#define EN1_CLK				RCC_APB2Periph_GPIOA
#define EN1_PORT			GPIOA
#define EN1_PIN				GPIO_Pin_4
#define EN1_H				GPIO_SetBits(EN1_PORT,EN1_PIN);
#define EN1_L				GPIO_ResetBits(EN1_PORT,EN1_PIN);

#endif


#if IN3

#define IN3_CLKCMD			RCC_APB2PeriphClockCmd
#define IN3_CLK				RCC_APB2Periph_GPIOA
#define IN3_PORT			GPIOA
#define IN3_PIN				GPIO_Pin_3
#define IN3_H				GPIO_SetBits(IN3_PORT,IN3_PIN);
#define IN3_L				GPIO_ResetBits(IN3_PORT,IN3_PIN);

#endif


#if IN4

#define IN4_CLKCMD			RCC_APB2PeriphClockCmd
#define IN4_CLK				RCC_APB2Periph_GPIOA
#define IN4_PORT			GPIOA
#define IN4_PIN				GPIO_Pin_2
#define IN4_H				GPIO_SetBits(IN4_PORT,IN4_PIN);
#define IN4_L				GPIO_ResetBits(IN4_PORT,IN4_PIN);

#endif


#if EN2

#define EN2_CLKCMD			RCC_APB2PeriphClockCmd
#define EN2_CLK				RCC_APB2Periph_GPIOA
#define EN2_PORT			GPIOA
#define EN2_PIN				GPIO_Pin_5
#define EN2_H				GPIO_SetBits(EN2_PORT,EN2_PIN);
#define EN2_L				GPIO_ResetBits(EN2_PORT,EN2_PIN);

#endif

#define TIM3_CH1 1
#define TIM3_CH2 1

#define GENERAL_TIM					TIM3
#define GENERAL_TIMCLKCMD			RCC_APB1PeriphClockCmd
#define GENERAL_TIMCLK				RCC_APB1Periph_TIM3
#define GENERAL_TIMPeriod			999 //+1是配置的周期数，us
#define GENERAL_TIMPrescaler		710 //时钟分频数

#if TIM3_CH1

//TIM3通用比较通道1
#define PWM_CH1CLKCMD				RCC_APB2PeriphClockCmd
#define PWM_CH1CLK					RCC_APB2Periph_GPIOA
#define PWM_CH1PORT					GPIOA
#define PWM_CH1PIN					GPIO_Pin_6
#define PWM_CH1_H_Time				400	//高电平时间

#endif

#if TIM3_CH2
//TIM3通用比较通道2
#define PWM_CH2CLKCMD				RCC_APB2PeriphClockCmd
#define PWM_CH2CLK					RCC_APB2Periph_GPIOA
#define PWM_CH2PORT					GPIOA
#define PWM_CH2PIN					GPIO_Pin_7
#define PWM_CH2_H_Time				430	//高电平时间

#endif


void DC_Moto_GO(void);
void DC_Moto_Right(void);
void DC_Moto_Left(void);
void DC_Moto_Back(void);
void DC_Moto_Stop(void);
void DC_Moto_Init(uint16_t speed1,uint16_t speed2);
#endif
