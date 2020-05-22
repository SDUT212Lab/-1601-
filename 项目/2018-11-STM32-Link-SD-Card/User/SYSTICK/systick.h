#ifndef __SYSTICK_H
#define __SYSTICK_H


#include "stm32f10x.h"


void SysTick_delay_us(uint32_t us);
void SysTick_delay_ms(uint32_t ms);


#endif /* __SYSTICK_H */
