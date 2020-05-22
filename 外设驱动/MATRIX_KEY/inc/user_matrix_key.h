#ifndef _USER_MATRIX_H
#define _USER_MATRIX_H

#include "stm32f10x.h"

#define R1_CLKCMD					RCC_APB2PeriphClockCmd
#define R1_CLK						RCC_APB2Periph_GPIOA
#define R1_PORT						GPIOA
#define R1_PIN						GPIO_Pin_3
#define R1_H							GPIO_SetBits(R1_PORT,R1_PIN)
#define R1_L							GPIO_ResetBits(R1_PORT,R1_PIN)

#define R2_CLKCMD					RCC_APB2PeriphClockCmd
#define R2_CLK						RCC_APB2Periph_GPIOA
#define R2_PORT						GPIOA
#define R2_PIN						GPIO_Pin_2
#define R2_H							GPIO_SetBits(R2_PORT,R2_PIN)
#define R2_L							GPIO_ResetBits(R2_PORT,R2_PIN)

#define R3_CLKCMD					RCC_APB2PeriphClockCmd
#define R3_CLK						RCC_APB2Periph_GPIOA
#define R3_PORT						GPIOA
#define R3_PIN						GPIO_Pin_1
#define R3_H							GPIO_SetBits(R3_PORT,R3_PIN)
#define R3_L							GPIO_ResetBits(R3_PORT,R3_PIN)

#define R4_CLKCMD					RCC_APB2PeriphClockCmd
#define R4_CLK						RCC_APB2Periph_GPIOA
#define R4_PORT						GPIOA
#define R4_PIN						GPIO_Pin_0
#define R4_H							GPIO_SetBits(R4_PORT,R4_PIN)
#define R4_L							GPIO_ResetBits(R4_PORT,R4_PIN)


#define C1_CLKCMD					RCC_APB2PeriphClockCmd
#define C1_CLK						RCC_APB2Periph_GPIOA
#define C1_PORT						GPIOA
#define C1_PIN						GPIO_Pin_4
#define C1_DATA						GPIO_ReadInputDataBit(C1_PORT,C1_PIN)

#define C2_CLKCMD					RCC_APB2PeriphClockCmd
#define C2_CLK						RCC_APB2Periph_GPIOA
#define C2_PORT						GPIOA
#define C2_PIN						GPIO_Pin_5
#define C2_DATA						GPIO_ReadInputDataBit(C2_PORT,C2_PIN)

#define C3_CLKCMD					RCC_APB2PeriphClockCmd
#define C3_CLK						RCC_APB2Periph_GPIOA
#define C3_PORT						GPIOA
#define C3_PIN						GPIO_Pin_6
#define C3_DATA						GPIO_ReadInputDataBit(C3_PORT,C3_PIN)

#define C4_CLKCMD					RCC_APB2PeriphClockCmd
#define C4_CLK						RCC_APB2Periph_GPIOA
#define C4_PORT						GPIOA
#define C4_PIN						GPIO_Pin_7
#define C4_DATA						GPIO_ReadInputDataBit(C4_PORT,C4_PIN)


void Matrix_Init(void);
uint8_t Matrix_Scan(void);
#endif


