#ifndef _28BYJ_H
#define _28BYJ_H
#include "stm32f10x.h"
#include "delay.h"

#define COR		{GPIO_SetBits(GPIOA,GPIO_Pin_0);GPIO_ResetBits(GPIOA,GPIO_Pin_1);}
#define BACK	{GPIO_ResetBits(GPIOA,GPIO_Pin_0);GPIO_SetBits(GPIOA,GPIO_Pin_1);}

void Moto_Single(void);
void Stright_Moto(uint8_t Moto_x,uint8_t Dir,uint8_t pwm);



#endif

