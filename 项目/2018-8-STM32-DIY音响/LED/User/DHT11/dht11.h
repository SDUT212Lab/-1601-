#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f10x.h"
#include "math.h"

#define DHT11_DATA_CLKCMD		RCC_APB2PeriphClockCmd
#define DHT11_DATA_CLK			RCC_APB2Periph_GPIOA
#define	DHT11_DATA_PORT			GPIOA
#define DHT11_DATA_PIN			GPIO_Pin_0

#define DHT11_DATA				GPIO_ReadInputDataBit(DHT11_DATA_PORT,DHT11_DATA_PIN)
#define DHT11_DATAH				GPIO_SetBits(DHT11_DATA_PORT,DHT11_DATA_PIN)
#define DHT11_DATAL				GPIO_ResetBits(DHT11_DATA_PORT,DHT11_DATA_PIN)



void DHT11_Init(void);
uint8_t DHT11_Read_Data(void);
float DHT11_Read_Humidity(void);
float DHT11_Read_Temper(void);
#endif
