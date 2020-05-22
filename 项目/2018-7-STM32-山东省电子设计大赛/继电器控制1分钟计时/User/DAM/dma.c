#include "dma.h"


uint8_t sendBuffer[5000];

void MTP_DMA_Config()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//�ṹ���ʼ��
	//����DAMԴ���ڴ��ַ&�������ݼĴ�����ַ
	//���ݴ���������������ȥ
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_ADDRESS;//���Դ���������ADCͨ����Ҳ���Դ��ڴ���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sendBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
	//����Ҫ�����٣����ĵ�λ��ʲô
	DMA_InitStructure.DMA_BufferSize = 5000; 									//�������Ŀ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//���裨�ڲ���FLASH����ַ������USARTֻ��һ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ�� 8 16 32 ����
	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �ڴ��ַ�������ڴ�����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�洢�������ݿ��
	
	//ʲôʱ�������
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //Circularѭ����Normal��ѭ��
	
	//�������ȼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	//����MToMģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//Ĭ�Ϲر�
	
	//����ı�־��������룬������ɣ��������
	
	// ����DMA ͨ����M2M�������ѡ��
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	// ʹ��DMA
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC4);
	
}

/*void MTM_DMA_Config()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//�ṹ���ʼ��
	//����DAMԴ���ڴ��ַ&�������ݼĴ�����ַ
	//���ݴ���������������ȥ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;//���Դ���������ADCͨ����Ҳ���Դ��ڴ���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//����Ҫ�����٣����ĵ�λ��ʲô
	DMA_InitStructure.DMA_BufferSize = 32; 									//�������Ŀ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;			//���裨�ڲ���FLASH����ַ������USARTֻ��һ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//�������ݿ�� 8 16 32 ����
	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// �ڴ��ַ�������ڴ�����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//�洢�������ݿ��
	
	//ʲôʱ�������
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ; //Circularѭ����Normal��ѭ��
	
	//�������ȼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	//����MToMģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//Ĭ�Ϲر�
	
	//����ı�־��������룬������ɣ��������
	
	// ����DMA ͨ����M2M�������ѡ��
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	// ʹ��DMA
	DMA_Cmd(DMA1_Channel6,ENABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC6);
	
}
*/
//����ȽϺ���
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


/**�ʼ�
	1.DMA Data Menory Access ֱ�Ӵ洢������
	2.DMA�Ĺ���
	�ݴ�һ���ط����Ƶ������һ���ط�����ռcpu
	3.DMA ������DMA1��DMA2 
		DMA1���߸�ͨ��,�������ݵĹܵ���ʵ��P->M M->P M->M
		DMA2���߸�ͨ����ʵ��P->M M->P M->M
	4.��̲��裨M to M��
		1����FLASh�ж���Ҫ��������ݣ���SRAM�ж�����������FLASH�еı���
		2����ʼ��DMa����Ҫ������DMA�ṹ��
		3����д�ȽϺ���
		4����дmain����
	
**/


