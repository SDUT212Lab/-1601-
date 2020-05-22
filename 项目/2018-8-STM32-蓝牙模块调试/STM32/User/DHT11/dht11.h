#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f10x.h"
#include "math.h"

#define DATA_CLKCMD			RCC_APB2PeriphClockCmd
#define DATA_CLK			RCC_APB2Periph_GPIOB
#define	DATA_PORT			GPIOB
#define DATA_PIN			GPIO_Pin_0

#define DATA				GPIO_ReadInputDataBit(DATA_PORT,DATA_PIN)
#define DATAH				GPIO_SetBits(DATA_PORT,DATA_PIN)
#define DATAL				GPIO_ResetBits(DATA_PORT,DATA_PIN)



void DHT11_Init(void);
uint8_t DHT11_Read_Data(void);
float DHT11_Read_Humidity(void);
float DHT11_Read_Temper(void);
#endif
