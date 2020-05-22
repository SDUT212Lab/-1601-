#ifndef _DS18B20_H
#define _DS18B20_H
#include "stm32f10x.h"

void Temper_Init(void);
void Temper_Mode_IPU(void);
void Temper_Mode_Out_PP(void);
uint8_t Temper_GetACK(void);

//void Temper_WriteBit(uint8_t bit);
//uint8_t Temper_ReadBit(void);

void Temper_Write(uint8_t data);
uint8_t Temper_Read(void);
uint8_t Temper_Start(void);
uint32_t Temper_Get(void);
float Temper_Deal(uint32_t data);

#define Temper_Out_Low GPIO_ResetBits(GPIOA,GPIO_Pin_8);
#define Temper_Out_High GPIO_SetBits(GPIOA,GPIO_Pin_8);

#endif
