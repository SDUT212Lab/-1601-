#ifndef _BSP_LED_H //如果编译过的话，不再重复编译
#define _BSP_LED_H

#include "stm32f10x.h"
#include "SYSTICK.h"


/*
宏定义
*/

#define LED0 GPIO_Pin_0
#define LED1 GPIO_Pin_1
#define LED2 GPIO_Pin_2

#define LED_GPIO_CLK RCC_APB2Periph_GPIOB

							
/**
*函数定义
**/
void LED_Init(void); 								//LED灯初始化函数
void LED(uint8_t LED,uint8_t condition);			//LED操作函数，参数LED的编号，LED的状态　０关　１开　２转换	
void LED_Wenkle(void);								//LED闪烁函数
void KEY_LED(void);									//按键LED函数
void JDQ_Init(void);
void System_Init(void);
void System_Recover(void);


#define JDQ_ON	GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define JDQ_OFF	GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#endif
