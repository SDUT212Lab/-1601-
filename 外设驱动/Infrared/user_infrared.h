#ifndef _USER_INFRARED_H
#define _USER_INFRARED_H
/*头文件*/
#include "stm32f10x.h"
/*宏定义*/
#define INFRARED_DATA_CLKCMD					RCC_APB2PeriphClockCmd
#define INFRARED_DATA_CLK							RCC_APB2Periph_GPIOA
#define INFRARED_DATA_PORT						GPIOA
#define INFRARED_DATA_PIN							GPIO_Pin_8
#define INFRARED_IRQCHANNEL						EXTI9_5_IRQn
#define INFRARED_PORTSOURCE						GPIO_PortSourceGPIOA
#define INFRARED_PINSOURCE						GPIO_PinSource8
#define INFRARED_EXTILINE							EXTI_Line8
#define INFRARED_IRQHANDELER					EXTI9_5_IRQHandler
#define INFRARED_DATA									GPIO_ReadInputDataBit(INFRARED_DATA_PORT,INFRARED_DATA_PIN)

void Infrared_Init(void);
#endif
/*************************end line********************/
