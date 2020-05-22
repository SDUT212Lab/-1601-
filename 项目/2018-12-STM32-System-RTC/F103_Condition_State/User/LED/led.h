#ifndef _LED_H
#define _LED_H
/*头文件*/
#include "stm32f10x.h"

/*引脚定义*/
#define LED_CLKCMD		RCC_APB2PeriphClockCmd
#define LED_CLK				RCC_APB2Periph_GPIOA
#define LED_PORT			GPIOA
#define LED_PIN				GPIO_Pin_8
#define LED_ON				GPIO_ResetBits(LED_PORT,LED_PIN)
#define LED_OFF				GPIO_SetBits(LED_PORT,LED_PIN)

/*函数定义*/
void LED_Init(void);
void LED_Wenkle(uint32_t ms);
#endif

