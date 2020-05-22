#ifndef	_LCD12864_H
#define	_LCD12864_H

#include "stm32f10x.h"
#include <math.h>
#include <string.h>

/*宏定义*/
#define PSB_PIN		GPIO_Pin_6	//串并方式选择
#define PSB_PORT	GPIOB
#define PSB_CLK		RCC_APB2Periph_GPIOB
#define PSB_CLKCMD	RCC_APB2PeriphClockCmd

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

#define BLK_PIN		GPIO_Pin_13
#define BLK_PORT	GPIOC
#define BLK_CLK		RCC_APB2Periph_GPIOC
#define BLK_CLKCMD	RCC_APB2PeriphClockCmd


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
void LCD12864_Init(void);
void LCD12864_WriteStr(char *p,uint8_t x,uint8_t y); 
void LCD12864_WriteNum(uint32_t num,uint8_t x, uint8_t y);
void LCD12864_WriteData(uint8_t data,uint8_t is_command);
void LCD12864_RollDisPlay(char *p ,uint8_t x,uint8_t y);
void LCD12864_LED_ON(void);
void LCD12864_LED_OFF(void);
void Moto_GPIO_Init(void);

#endif
