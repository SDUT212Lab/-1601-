#ifndef _ADC_H
#define	_ADC_H

#include "stm32f10x.h"

#define ADC1_DR_ADDRESS	(ADC1_BASE+0x4c)
#define ADC_x ADC1
#define ADC_y ADC2
#define ADC_Channel_m ADC_Channel_1
#define ADC_Channel_n ADC_Channel_2
#define APB_ADC_CLK RCC_APB2Periph_ADC1 |RCC_APB2Periph_ADC2

#define DMAm_CHANNEL_n DMA1_Channel1
#define AHB_CLK_DMA RCC_AHBPeriph_DMA1

void ADC2_Init(void);
void ADC1_Init(void);
void ADC12_Init(void);

#endif
