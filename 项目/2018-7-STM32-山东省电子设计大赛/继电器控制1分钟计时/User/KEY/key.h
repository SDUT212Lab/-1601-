#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

///////////////////////////////////////////////////////////////////////////////////
//宏定义
///////////////////////////////////////////////////////////////////////////////////

#define KEY0_GPIO_CLK RCC_APB2Periph_GPIOB
#define KEY0 GPIO_Pin_6
#define KEY1 GPIO_Pin_7
#define KEY2 GPIO_Pin_8

void KEY_Init(void);				//按键扫描函数

uint8_t KEY_Scan(uint8_t key_num); 	//按键操作函数，传入按键的编号，输出按键的状态


#endif
