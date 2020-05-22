#include "internal_flash.h"

/**
  * @brief  InternalFlash_Test,���ڲ�FLASH���ж�д����
  * @param  None
  * @retval None
  */
int InternalFlash_Test(uint32_t *Data,uint32_t start_addr,uint32_t end_addr)
{
	uint32_t EraseCounter = 0x00; 	//��¼Ҫ��������ҳ
	uint32_t Address = 0x00;				//��¼д��ĵ�ַ
				//��¼д�������
	uint32_t NbrOfPage = 0x00;			//��¼д�����ҳ
	
	FLASH_Status FLASHStatus = FLASH_COMPLETE; //��¼ÿ�β����Ľ��	
	TestStatus MemoryProgramStatus = PASSED;//��¼�������Խ��
	
	
  FLASH_Unlock();

  /* ����Ҫ��������ҳ */
  NbrOfPage = (end_addr - start_addr) / FLASH_PAGE_SIZE;

  /* ������б�־λ */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* ��ҳ����*/
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(start_addr + (FLASH_PAGE_SIZE * EraseCounter));
  
	}
  
  /* ���ڲ�FLASHд������ */
  
  {
	  Address = start_addr;

	while((Address <= end_addr) && (FLASHStatus == FLASH_COMPLETE))
	{
    FLASHStatus = FLASH_ProgramWord(Address, *Data);
    Address = Address + 4;
	}
  }

  FLASH_Lock();
  
  /* ���д��������Ƿ���ȷ */
   while((Address < end_addr) && (MemoryProgramStatus != FAILED))
  {
    if((*(__IO uint32_t*) Address) != *Data)
    {
      MemoryProgramStatus = FAILED;
    }
    Address += 4;
  }
	return MemoryProgramStatus;
}

void Internal_Flash_Read_Data(uint32_t *Data,uint32_t start_addr,uint32_t end_addr)
{
	uint32_t Address = 0x00;
	Address = start_addr;
FLASH_Status FLASHStatus = FLASH_COMPLETE; //��¼ÿ�β����Ľ��	
	TestStatus MemoryProgramStatus = PASSED;
  while((Address < end_addr) && (MemoryProgramStatus != FAILED))
  {
	*Data = *(__IO uint32_t*)Address;
    if((*(__IO uint32_t*) Address) != *Data)
    {
      MemoryProgramStatus = FAILED;
    }
    Address += 4;
  }
  *Data++;
  /* ���� */
}
	


