#ifndef _HT1261_H
#define _HT1261_H

#include "stm32f10x.h"

#define sbi(x, y)  (x |= (1 << y))   /*置位寄器x的第y位*/
#define cbi(x, y)  (x &= ~(1 <<y ))  /*清零寄器x的第y位*/ 

#define DATA_CLKCMD			RCC_APB2PeriphClockCmd
#define DATA_CLK			RCC_APB2Periph_GPIOC
#define DATA_PORT			GPIOC
#define DATA_PIN			GPIO_Pin_9
#define DATA_H				GPIO_SetBits(DATA_PORT,DATA_PIN)
#define DATA_L				GPIO_ResetBits(DATA_PORT,DATA_PIN)

#define WR_CLKCMD			RCC_APB2PeriphClockCmd
#define WR_CLK				RCC_APB2Periph_GPIOC
#define WR_PORT				GPIOC
#define WR_PIN				GPIO_Pin_11
#define WR_H				GPIO_SetBits(WR_PORT,WR_PIN)
#define WR_L				GPIO_ResetBits(WR_PORT,WR_PIN)

#define CS_CLKCMD			RCC_APB2PeriphClockCmd
#define CS_CLK				RCC_APB2Periph_GPIOC
#define CS_PORT				GPIOC
#define CS_PIN				GPIO_Pin_14
#define CS_H				GPIO_SetBits(CS_PORT,CS_PIN)
#define CS_L				GPIO_ResetBits(CS_PORT,CS_PIN)

void HT1261_Init(void);
void HT1261_Display_Data(long int num,int place,char bat1,char bat2,char bat3);

#endif
