#include "dma.h"


uint8_t sendBuffer[5000];

void MTP_DMA_Config()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//结构体初始化
	//设置DAM源：内存地址&串口数据寄存器地址
	//数据从哪里来，到哪里去
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;//可以从外设来，ADC通道，也可以从内存来
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sendBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
	//数据要传多少，传的单位是什么
	DMA_InitStructure.DMA_BufferSize = 5000; 									//传输的数目
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//外设（内部的FLASH）地址递增，USART只有一个
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据宽度 8 16 32 保留
	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 内存地址递增，内存自增
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//存储器的数据宽度
	
	//什么时候传输结束
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //Circular循环和Normal不循环
	
	//配置优先级
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	//配置MToM模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//默认关闭
	
	//传输的标志，传输过半，传出完成，传输出错
	
	// 配置DMA 通道，M2M可以随便选择
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	// 使能DMA
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC4);
	
}

/*void MTM_DMA_Config()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//结构体初始化
	//设置DAM源：内存地址&串口数据寄存器地址
	//数据从哪里来，到哪里去
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;//可以从外设来，ADC通道，也可以从内存来
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//数据要传多少，传的单位是什么
	DMA_InitStructure.DMA_BufferSize = 32; 									//传输的数目
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;			//外设（内部的FLASH）地址递增，USART只有一个
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//外设数据宽度 8 16 32 保留
	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// 内存地址递增，内存自增
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//存储器的数据宽度
	
	//什么时候传输结束
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ; //Circular循环和Normal不循环
	
	//配置优先级
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	//配置MToM模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//默认关闭
	
	//传输的标志，传输过半，传出完成，传输出错
	
	// 配置DMA 通道，M2M可以随便选择
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	// 使能DMA
	DMA_Cmd(DMA1_Channel6,ENABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC6);
	
}
*/
//数组比较函数
uint8_t BufferCpy(const uint32_t* pBuffer,uint32_t *pBuffer1,uint32_t BufferLength)
{
	while(BufferLength--)
	{
		if(*pBuffer != *pBuffer1)
		{
			return 0;
		}
		else 
		{
			pBuffer++;
			pBuffer1++;
		}
	}
	return 1;
}


/**笔记
	1.DMA Data Menory Access 直接存储器访问
	2.DMA的功能
	据从一个地方搬移到另外的一个地方而不占cpu
	3.DMA 有连个DMA1和DMA2 
		DMA1有七个通道,搬运数据的管道：实现P->M M->P M->M
		DMA2有七个通道：实现P->M M->P M->M
	4.编程步骤（M to M）
		1）在FLASh中定义要传输的数据，在SRAM中定义用来接收FLASH中的变量
		2）初始化DMa，主要是配置DMA结构体
		3）编写比较函数
		4）编写main函数
	
**/


