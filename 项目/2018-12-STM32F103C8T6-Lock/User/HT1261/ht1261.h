#ifndef _HT1261_H
#define _HT1261_H

#include "stm32f10x.h"

#define sbi(x, y)  (x |= (1 << y))   /*��λ����x�ĵ�yλ*/
#define cbi(x, y)  (x &= ~(1 <<y ))  /*�������x�ĵ�yλ*/ 

#define DATA_CLKCMD			RCC_APB2PeriphClockCmd
#define DATA_CLK				RCC_APB2Periph_GPIOB
#define DATA_PORT				GPIOB
#define DATA_PIN				GPIO_Pin_13
#define DATA_H					GPIO_SetBits(DATA_PORT,DATA_PIN)
#define DATA_L					GPIO_ResetBits(DATA_PORT,DATA_PIN)

#define WR_CLKCMD				RCC_APB2PeriphClockCmd
#define WR_CLK					RCC_APB2Periph_GPIOB
#define WR_PORT					GPIOB
#define WR_PIN					GPIO_Pin_14
#define WR_H						GPIO_SetBits(WR_PORT,WR_PIN)
#define WR_L						GPIO_ResetBits(WR_PORT,WR_PIN)
	
#define CS_CLKCMD				RCC_APB2PeriphClockCmd
#define CS_CLK					RCC_APB2Periph_GPIOB
#define CS_PORT					GPIOB
#define CS_PIN					GPIO_Pin_15
#define CS_H						GPIO_SetBits(CS_PORT,CS_PIN)
#define CS_L						GPIO_ResetBits(CS_PORT,CS_PIN)

void HT1261_Init(void);
void HT1261_All_On(uint8_t num);
void HT1261_Displayall8(void);
void HT1261_Display_Data(long int t,int p,char bat1,char bat2,char bat3);

#endif
