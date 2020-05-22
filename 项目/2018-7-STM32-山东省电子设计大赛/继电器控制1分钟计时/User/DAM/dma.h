#ifndef _DMA_H
#define _DMA_H

#include "stm32f10x.h"

//void MTM_DMA_Config(void);
void MTP_DMA_Config(void);
uint8_t BufferCpy(const uint32_t* pBuffer,uint32_t *pBuffer1,uint32_t BufferLength);

//Õ‚…Ëºƒ¥Ê∆˜µÿ÷∑
#define USART1_DR_ADDRESS (USART1_BASE + 0x04)
#endif
