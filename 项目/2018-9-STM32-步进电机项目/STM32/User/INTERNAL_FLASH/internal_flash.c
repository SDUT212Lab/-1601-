#include "internal_flash.h"

/**
  * @brief  InternalFlash_Test,对内部FLASH进行读写测试
  * @param  None
  * @retval None
  */
int InternalFlash_Test(uint32_t *Data,uint32_t start_addr,uint32_t end_addr)
{
	uint32_t EraseCounter = 0x00; 	//记录要擦除多少页
	uint32_t Address = 0x00;				//记录写入的地址
				//记录写入的数据
	uint32_t NbrOfPage = 0x00;			//记录写入多少页
	
	FLASH_Status FLASHStatus = FLASH_COMPLETE; //记录每次擦除的结果	
	TestStatus MemoryProgramStatus = PASSED;//记录整个测试结果
	
	
  FLASH_Unlock();

  /* 计算要擦除多少页 */
  NbrOfPage = (end_addr - start_addr) / FLASH_PAGE_SIZE;

  /* 清空所有标志位 */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* 按页擦除*/
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(start_addr + (FLASH_PAGE_SIZE * EraseCounter));
  
	}
  
  /* 向内部FLASH写入数据 */
  
  {
	  Address = start_addr;

	while((Address <= end_addr) && (FLASHStatus == FLASH_COMPLETE))
	{
    FLASHStatus = FLASH_ProgramWord(Address, *Data);
    Address = Address + 4;
	}
  }

  FLASH_Lock();
  
  /* 检查写入的数据是否正确 */
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
FLASH_Status FLASHStatus = FLASH_COMPLETE; //记录每次擦除的结果	
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
  /* 解锁 */
}
	


