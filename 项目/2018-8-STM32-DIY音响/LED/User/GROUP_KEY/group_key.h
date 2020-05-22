#ifndef _GROUP_KEY_H
#define _GROUP_KEY_H

#include "stm32f10x.h"
void Group_KEY_Mode_IN_FLOATING(GPIO_TypeDef* GPIO_x,uint16_t GPIO_Pin_x);
#define C1_CLKCMD			RCC_APB2PeriphClockCmd
#define C1_CLK				RCC_APB2Periph_GPIOA
#define C1_PORT				GPIOA
#define C1_PIN				GPIO_Pin_0
#define C1_H				GPIO_SetBits(C1_PORT,C1_PIN)
#define C1_L				GPIO_ResetBits(C1_PORT,C1_PIN)
#define C1					GPIO_ReadInputDataBit(C1_PORT,C1_PIN)
#define C1_F				Group_KEY_Mode_IN_FLOATING(C1_PORT,C1_PIN)

#define C2_CLKCMD			RCC_APB2PeriphClockCmd
#define C2_CLK				RCC_APB2Periph_GPIOA
#define C2_PORT				GPIOA
#define C2_PIN				GPIO_Pin_1
#define C2_H				GPIO_SetBits(C2_PORT,C2_PIN)
#define C2_L				GPIO_ResetBits(C2_PORT,C2_PIN)
#define C2					GPIO_ReadInputDataBit(C2_PORT,C2_PIN)
#define C2_F			Group_KEY_Mode_IN_FLOATING(C2_PORT,C2_PIN)

#define C3_CLKCMD			RCC_APB2PeriphClockCmd
#define C3_CLK				RCC_APB2Periph_GPIOA
#define C3_PORT				GPIOA
#define C3_PIN				GPIO_Pin_2
#define C3_H				GPIO_SetBits(C3_PORT,C3_PIN)
#define C3_L				GPIO_ResetBits(C3_PORT,C3_PIN)
#define C3					GPIO_ReadInputDataBit(C3_PORT,C3_PIN)
#define C3_F				Group_KEY_Mode_IN_FLOATING(C3_PORT,C3_PIN)

#define C4_CLKCMD			RCC_APB2PeriphClockCmd
#define C4_CLK				RCC_APB2Periph_GPIOA
#define C4_PORT				GPIOA
#define C4_PIN				GPIO_Pin_3
#define C4_H				GPIO_SetBits(C4_PORT,C4_PIN)
#define C4_L				GPIO_ResetBits(C4_PORT,C4_PIN)
#define C4					GPIO_ReadInputDataBit(C4_PORT,C4_PIN)
#define C4_F				Group_KEY_Mode_IN_FLOATING(C4_PORT,C4_PIN)

#define C5_CLKCMD			RCC_APB2PeriphClockCmd
#define C5_CLK				RCC_APB2Periph_GPIOA
#define C5_PORT				GPIOA
#define C5_PIN				GPIO_Pin_4
#define C5_H				GPIO_SetBits(C5_PORT,C5_PIN)
#define C5_L				GPIO_ResetBits(C5_PORT,C5_PIN)
#define C5					GPIO_ReadInputDataBit(C5_PORT,C5_PIN)
#define C5_F				Group_KEY_Mode_IN_FLOATING(C5_PORT,C5_PIN)

#define C6_CLKCMD			RCC_APB2PeriphClockCmd
#define C6_CLK				RCC_APB2Periph_GPIOA
#define C6_PORT				GPIOA
#define C6_PIN				GPIO_Pin_5
#define C6_H				GPIO_SetBits(C6_PORT,C6_PIN)
#define C6_L				GPIO_ResetBits(C6_PORT,C6_PIN)
#define C6					GPIO_ReadInputDataBit(C6_PORT,C6_PIN)
#define C6_F				Group_KEY_Mode_IN_FLOATING(C6_PORT,C6_PIN)

#define C7_CLKCMD			RCC_APB2PeriphClockCmd
#define C7_CLK				RCC_APB2Periph_GPIOA
#define C7_PORT				GPIOA
#define C7_PIN				GPIO_Pin_6
#define C7_H				GPIO_SetBits(C7_PORT,C7_PIN)
#define C7_L				GPIO_ResetBits(C7_PORT,C7_PIN)
#define C7					GPIO_ReadInputDataBit(C7_PORT,C7_PIN)
#define C7_F				Group_KEY_Mode_IN_FLOATING(C7_PORT,C7_PIN)

#define C8_CLKCMD			RCC_APB2PeriphClockCmd
#define C8_CLK				RCC_APB2Periph_GPIOA
#define C8_PORT				GPIOA
#define C8_PIN				GPIO_Pin_7
#define C8_H				GPIO_SetBits(C8_PORT,C8_PIN)
#define C8_L				GPIO_ResetBits(C8_PORT,C8_PIN)
#define C8					GPIO_ReadInputDataBit(C8_PORT,C8_PIN)
#define C8_F				Group_KEY_Mode_IN_FLOATING(C8_PORT,C8_PIN)

void Group_KEY_Init(void);
uint8_t Group_KEY_Scan(void);

#endif
