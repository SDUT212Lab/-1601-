#include "RCC.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	//��RCC�����ʼ��Ϊ��λ״̬����仰�Ǳ����
	RCC_DeInit();
	
	//ʹ��HSE����HSE,���HSE�����˵Ļ�����ʹ��HSI��Ϊϵͳʱ�ӣ�ʱ�ӷǳ�����ֻ��8MHz
	RCC_HSEConfig(RCC_HSE_ON);
	
	//�ȴ�HSE����
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStatus == SUCCESS)
	{
		//����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б����
		//�÷���FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		//FLASH�Ķ�д����Ҫʱ�䣬���õȴ�������Ϊ��ȷ����ȷ�Ķ�д��
		//��Ϊcpu���ٶ�ԶԶ����FLASH�Ĳ����ٶȡ��ÿ⺯��FLASH_SetLatency(FLASH_Latency_2)�����á�
		//���Բ�Ҫ����ѭ���з���ִ�ж�д����
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK ��AHB����ʱ�ӣ���ϵͳʱ��SYSCLK ��Ƶ�õ���һ�㲻��Ƶ��
		//����ϵͳʱ�ӣ�HCLK�Ǹ�������ʱ�ӣ��Ǹ��ⲿ�豸�ģ������ڴ棬flash��
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//����HSE*��Ƶ����
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//ʹ��PLL
		RCC_PLLCmd(ENABLE);
		//�ȴ�PLLʱ���ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//ѡ��ϵͳʱ��
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		while(RCC_GetSYSCLKSource() != 0x08);
	}
	else
	{
		HSI_SetSysClk(RCC_PLLMul_9);
	}
	
}


void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	volatile uint32_t HSIStartUpStatus = 0;
	RCC_DeInit();
	
	RCC_HSICmd(ENABLE);
	
	HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if(HSIStartUpStatus == RCC_CR_HSIRDY)
	{
		//����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б����
		//�÷���FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable)
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		//FLASH�Ķ�д����Ҫʱ�䣬���õȴ�������Ϊ��ȷ����ȷ�Ķ�д��
		//��Ϊcpu���ٶ�ԶԶ����FLASH�Ĳ����ٶȡ��ÿ⺯��FLASH_SetLatency(FLASH_Latency_2)�����á�
		//���Բ�Ҫ����ѭ���з���ִ�ж�д����
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK ��AHB����ʱ�ӣ���ϵͳʱ��SYSCLK ��Ƶ�õ���һ�㲻��Ƶ��
		//����ϵͳʱ�ӣ�HCLK�Ǹ�������ʱ�ӣ��Ǹ��ⲿ�豸�ģ������ڴ棬flash��
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//����HSE*��Ƶ����
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		//ʹ��PLL
		RCC_PLLCmd(ENABLE);
		//�ȴ�PLLʱ���ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//ѡ��ϵͳʱ��
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		while(RCC_GetSYSCLKSource() != 0x08);
	}
	else
	{
	
	}
}

void MCO_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_50MHz;
	
	//ͨ��GPIO A8��ʾ����
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

