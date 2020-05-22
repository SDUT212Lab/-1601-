#include "RCC.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	//将RCC外设初始化为复位状态，这句话是必须的
	RCC_DeInit();
	
	//使能HSE，打开HSE,如果HSE被关了的话，将使用HSI作为系统时钟，时钟非常慢，只有8MHz
	RCC_HSEConfig(RCC_HSE_ON);
	
	//等待HSE起振
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(HSEStatus == SUCCESS)
	{
		//开启FLASH预读缓冲功能，加速FLASH的读取。所有程序中必须的
		//用法：FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		//FLASH的读写均需要时间，设置等待周期是为了确保正确的读写。
		//因为cpu的速度远远大于FLASH的操作速度。用库函数FLASH_SetLatency(FLASH_Latency_2)来设置。
		//所以不要放在循环中反复执行读写操作
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK ：AHB总线时钟，由系统时钟SYSCLK 分频得到，一般不分频，
		//等于系统时钟，HCLK是高速外设时钟，是给外部设备的，比如内存，flash。
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//配置HSE*倍频因子
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//使能PLL
		RCC_PLLCmd(ENABLE);
		//等待PLL时钟稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//选择系统时钟
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
		//开启FLASH预读缓冲功能，加速FLASH的读取。所有程序中必须的
		//用法：FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable)
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		//FLASH的读写均需要时间，设置等待周期是为了确保正确的读写。
		//因为cpu的速度远远大于FLASH的操作速度。用库函数FLASH_SetLatency(FLASH_Latency_2)来设置。
		//所以不要放在循环中反复执行读写操作
		FLASH_SetLatency(FLASH_Latency_2);
		
		//HCLK ：AHB总线时钟，由系统时钟SYSCLK 分频得到，一般不分频，
		//等于系统时钟，HCLK是高速外设时钟，是给外部设备的，比如内存，flash。
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//配置HSE*倍频因子
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		//使能PLL
		RCC_PLLCmd(ENABLE);
		//等待PLL时钟稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//选择系统时钟
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
	
	//通过GPIO A8显示出来
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

