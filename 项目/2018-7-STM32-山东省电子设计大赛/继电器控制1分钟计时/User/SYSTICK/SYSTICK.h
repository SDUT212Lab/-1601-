#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"
#include "core_cm3.h" //°üº¬ÄÚÉè
#include "bsp_led.h"

void SysTick_delay_us(uint32_t us);
void SysTick_delay_ms(uint32_t ms);

#endif
