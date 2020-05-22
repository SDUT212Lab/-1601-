#ifndef _INTERNAL_FLASH_H
#define _INTERNAL_FLASH_H

#include "stm32f10x.h"



/* STM32��������Ʒÿҳ��С2KByte���С�С������Ʒÿҳ��С1KByte */

  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)	//1024


//д�����ʼ��ַ�������ַ



typedef enum 
{
	FAILED = 0, 
  PASSED = !FAILED
} TestStatus;


int InternalFlash_Test(uint32_t *Data,uint32_t start_addr,uint32_t end_addr);
void Internal_Flash_Write_Data(uint32_t addr,uint8_t *p,uint16_t Byte_Num);
void Internal_Flash_Read_Data(uint32_t *Data,uint32_t start_addr,uint32_t end_addr);


#endif
