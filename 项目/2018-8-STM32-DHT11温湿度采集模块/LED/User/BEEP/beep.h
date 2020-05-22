#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f10x.h"

#define BEEP_CLKCMD			RCC_APB2PeriphClockCmd
#define BEEP_CLK			RCC_APB2Periph_GPIOB
#define BEEP_PORT			GPIOB
#define BEEP_PIN			GPIO_Pin_10

#define BEEP_ON				GPIO_ResetBits(BEEP_PORT,BEEP_PIN)
#define BEEP_OFF			GPIO_SetBits(BEEP_PORT,BEEP_PIN)
void BEEP_Init(void);
void BEEP_DIDI(uint16_t num,uint16_t time);

#endif
