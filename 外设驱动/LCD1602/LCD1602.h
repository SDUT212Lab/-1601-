#ifndef	_LCD1602_H
#define	_LCD1602_H

#include "stm32f10x.h"
#include <math.h>
/*宏定义*/
#define RS_PIN		GPIO_Pin_7
#define RS_PORT		GPIOB
#define RS_CLK		RCC_APB2Periph_GPIOB
#define RS_CLKCMD	RCC_APB2PeriphClockCmd

#define RW_PIN		GPIO_Pin_8
#define RW_PORT		GPIOB
#define RW_CLK		RCC_APB2Periph_GPIOB
#define RW_CLKCMD	RCC_APB2PeriphClockCmd

#define EN_PIN		GPIO_Pin_9
#define EN_PORT		GPIOB
#define EN_CLK		RCC_APB2Periph_GPIOB
#define EN_CLKCMD	RCC_APB2PeriphClockCmd

#define D0			GPIO_Pin_0
#define D1			GPIO_Pin_1
#define D2			GPIO_Pin_2
#define D3			GPIO_Pin_3
#define D4			GPIO_Pin_4
#define D5			GPIO_Pin_5
#define D6			GPIO_Pin_6
#define D7			GPIO_Pin_7
#define DX_PORT		GPIOA
#define DX_CLK		RCC_APB2Periph_GPIOA
#define DX_CLKCMD	RCC_APB2PeriphClockCmd

/*函数定义*/
void LCD1602_Init(void);
void LCD1602_WriteStr(char *p,uint8_t x,uint8_t y); 
void LCD1602_WriteNum(float num,uint8_t x, uint8_t y);

#endif
