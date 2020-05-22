#ifndef _HT1261_H
#define _HT1261_H

#include "stm32f10x.h"

#define sbi(x, y)  (x |= (1 << y))   /*置位寄器x的第y位*/
#define cbi(x, y)  (x &= ~(1 <<y ))  /*清零寄器x的第y位*/ 

#define DATA_CLKCMD			RCC_APB2PeriphClockCmd
#define DATA_CLK			RCC_APB2Periph_GPIOA
#define DATA_PORT			GPIOA
#define DATA_PIN			GPIO_Pin_0
#define DATA_H				GPIO_SetBits(DATA_PORT,DATA_PIN)
#define DATA_L				GPIO_ResetBits(DATA_PORT,DATA_PIN)

#define WR_CLKCMD			RCC_APB2PeriphClockCmd
#define WR_CLK				RCC_APB2Periph_GPIOA
#define WR_PORT				GPIOA
#define WR_PIN				GPIO_Pin_1
#define WR_H				GPIO_SetBits(WR_PORT,WR_PIN)
#define WR_L				GPIO_ResetBits(WR_PORT,WR_PIN)

#define CS_CLKCMD			RCC_APB2PeriphClockCmd
#define CS_CLK				RCC_APB2Periph_GPIOA
#define CS_PORT				GPIOA
#define CS_PIN				GPIO_Pin_2
#define CS_H				GPIO_SetBits(CS_PORT,CS_PIN)
#define CS_L				GPIO_ResetBits(CS_PORT,CS_PIN)

void HT1261_Init(void);
void HT1261_All_On(uint8_t num);
void HT1261_Displayall8(void);
void HT1261_Display_Data(long int t,int p,char bat1,char bat2,char bat3);

#endif
