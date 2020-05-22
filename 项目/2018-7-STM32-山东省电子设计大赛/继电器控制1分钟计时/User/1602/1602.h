#ifndef _1602_H
#define	_1602_H

#include "stm32f10x.h"
#include "delay.h"

#define RSH	GPIO_ModeIPU(GPIOB,GPIO_Pin_11);
#define RSL GPIO_ModeIPD(GPIOB,GPIO_Pin_11);

#define RWH GPIO_ModeIPU(GPIOB,GPIO_Pin_5);
#define RWL GPIO_ModeIPD(GPIOB,GPIO_Pin_5);

#define ENH	GPIO_ModeIPU(GPIOB,GPIO_Pin_10);
#define ENL GPIO_ModeIPD(GPIOB,GPIO_Pin_10);


void GPIO_ModeIPD(GPIO_TypeDef * GPIO_x,uint16_t GPIO_Pin);
void GPIO_ModeIPU(GPIO_TypeDef * GPIO_x,uint16_t GPIO_Pin);

void SMC_WriteData(uint8_t data);
void SMC_WriteCom(uint8_t com);
void SMC_Init(void);
#endif
