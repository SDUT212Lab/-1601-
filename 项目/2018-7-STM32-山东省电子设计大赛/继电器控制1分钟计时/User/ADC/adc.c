#include "adc.h"
//PA1 ADC通道

__IO  uint32_t  ADC1_Value;

//static 防止被其他程序调用,表示当前文件调用
static void ADC2_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
}

static void ADC2_NVIC()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
}

static void ADC2_Mode_Init()
{
	ADC2_NVIC();
	ADC_InitTypeDef ADC_InitStruct;
	
	//打开时钟，ADC2不能用DMA，时钟挂在APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);

	//ADC配置
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//独立模式，还是双通道模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//开启连续转换模式，不停的进行adc转换，
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//外部触发
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//采集数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//要求转换的通道数目

	ADC_Init(ADC2,&ADC_InitStruct);
	
	//配置ADC时钟，为PCLK2的八分频，即9Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//配置ADC的规则通道配置，rank表示转换顺序，最后一个参数为采样时间
	ADC_RegularChannelConfig(ADC2,ADC_Channel_2,1,ADC_SampleTime_55Cycles5);

	//中断配置
	ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);
	//开启ADC
	ADC_Cmd(ADC2,ENABLE);
	//校准ADC
	ADC_StartCalibration(ADC2);
	
	//等待完成信号
	while(ADC_GetCalibrationStatus(ADC2));
	
	//软件触发
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	
}
//魔术棒可以选择C99 mode
static void ADC1_DMA_Init()
{
	DMA_InitTypeDef DMA_InitStruct;
	
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_AHBPeriphClockCmd(AHB_CLK_DMA,ENABLE);
	//打开时钟，ADC2不能用DMA，时钟挂在APB2
	RCC_APB2PeriphClockCmd(APB_ADC_CLK,ENABLE);
	DMA_DeInit(DMAm_CHANNEL_n);
	//form and to
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) &ADC1_Value;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//穿多少，单位是什么
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	//传输的模式是什么
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMAm_CHANNEL_n,&DMA_InitStruct);
	
	DMA_Cmd(DMAm_CHANNEL_n,ENABLE);

	
/*---------------------------------------------------------------------*/	


	//ADC配置
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//独立模式，还是双通道模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//开启连续转换模式，不停的进行adc转换，
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//外部触发
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//采集数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//要求转换的通道数目

	ADC_Init(ADC_x,&ADC_InitStruct);
	
	//配置ADC时钟，为PCLK2的八分频，即9Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//配置ADC的规则通道配置，rank表示转换顺序，最后一个参数为采样时间
	ADC_RegularChannelConfig(ADC_x,ADC_Channel_m,1,ADC_SampleTime_55Cycles5);

	ADC_DMACmd(ADC_x,ENABLE);
	//开启ADC
	ADC_Cmd(ADC_x,ENABLE);
	//校准ADC
	ADC_StartCalibration(ADC_x);
	// 初始化ADC 校准寄存器  
	ADC_ResetCalibration(ADC_x);
	// 等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	//等待完成信号
	while(ADC_GetCalibrationStatus(ADC_x));
	
	//软件触发
	ADC_SoftwareStartConvCmd(ADC_x,ENABLE);
		
	
}

static void ADC_DMADouble_Init()
{
	DMA_InitTypeDef DMA_InitStruct;
	
	ADC_InitTypeDef ADC_InitStruct;
	//只有ADC1有DMA功能
	RCC_AHBPeriphClockCmd(AHB_CLK_DMA,ENABLE);
	//打开时钟，ADC2不能用DMA，时钟挂在APB2
	RCC_APB2PeriphClockCmd(APB_ADC_CLK,ENABLE);
	DMA_DeInit(DMAm_CHANNEL_n);
	//form and to
	DMA_InitStruct.DMA_PeripheralBaseAddr =(uint32_t)(&( ADC_x->DR ));
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) &ADC1_Value;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//穿多少，单位是什么
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	//传输的模式是什么
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMAm_CHANNEL_n,&DMA_InitStruct);
	
	DMA_Cmd(DMAm_CHANNEL_n,ENABLE);

	
/*---------------------------------------------------------------------*/	


	//ADC1配置
	ADC_InitStruct.ADC_Mode = ADC_Mode_RegSimult;		//独立模式，还是双通道模式,可以打开双通道模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//禁止扫描模式，每个ADC都有多个通道时，扫描模式用于多通道采集
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//开启连续转换模式，不停的进行adc转换，
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//外部触发
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//采集数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//要求转换的通道数目

	ADC_Init(ADC_x,&ADC_InitStruct);
	
	//配置ADC时钟，为PCLK2的八分频，即9Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//配置一次就可以
	
	//配置ADC的规则通道配置，rank表示转换顺序，最后一个参数为采样时间
	ADC_RegularChannelConfig(ADC_x,ADC_Channel_m,1,ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADC_x,ENABLE);
	//开启ADC
	ADC_Cmd(ADC_x,ENABLE);
	ADC_ResetCalibration(ADC_x);
	while(ADC_GetResetCalibrationStatus(ADC_x));	
	ADC_StartCalibration(ADC_x); 
	while(ADC_GetCalibrationStatus(ADC_x));

	//ADC2配置
	ADC_InitStruct.ADC_Mode = ADC_Mode_RegSimult;		//独立模式，还是双通道模式,可以打开双通道模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//禁止扫描模式，每个ADC都有多个通道时，扫描模式用于多通道采集
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//开启连续转换模式，不停的进行adc转换，
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//外部触发
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//采集数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//要求转换的通道数目

	ADC_Init(ADC_y,&ADC_InitStruct);
	
	
	//配置ADC的规则通道配置，rank表示转换顺序，最后一个参数为采样时间
	ADC_RegularChannelConfig(ADC_y,ADC_Channel_n,1,ADC_SampleTime_55Cycles5);

	//开启ADC
	ADC_Cmd(ADC_y,ENABLE);
	

	
	/*校准ADC*/
	// 初始化ADC 校准寄存器, 等待校准寄存器初始化完成 
	ADC_ResetCalibration(ADC_y);
	while(ADC_GetResetCalibrationStatus(ADC_y)); 

	
	//开始校准，等待完成信号
	ADC_StartCalibration(ADC_y); 
	while(ADC_GetCalibrationStatus(ADC_y));

	
	//软件触发
	ADC_ExternalTrigConvCmd(ADC_y,ENABLE);
	ADC_SoftwareStartConvCmd(ADC_x,ENABLE);//采用多路模式时，ADC1为主采用软件触发，ADC为从采用外部触发

	/*----------这个地方必须先进行配置ADC2的外部触发，再配置ADC1
				的软件触发，因为ADC2的触发是ADC1的一个寄存器出发
				的；											---------------------*/

}




void ADC2_Init()
{
	ADC2_GPIO_Init();

	ADC2_Mode_Init();
}

void ADC1_Init() //使用DMA模式
{
	ADC2_GPIO_Init();
	ADC1_DMA_Init();
}
void ADC12_Init()
{
	ADC2_GPIO_Init();
	ADC_DMADouble_Init();
}

/**笔记
	1.ADC需要关注的地方
		1)分辨率 
			12位分辨率。不能直接测量负电压，最小的量化单位为LSB= Vref+/12
		2）转换时间
			转换时间是可以编程的。采样一次至少用法14个adc时钟周期，ADC的时钟频率最高为14MHz采样最短时间是1Us
		3）ADC的类型
			ADC的类型决定了其性能的极限，STM32使用的是依次比较性型ADC
		4）参考电压的范围
	2.编程要点
		1）初始化ADC和GPIO结构体
		2）配置ADC的时钟，转换顺序和转换时间
		3）使能ADC转换完成中断，配置优先级
		4)使能ADc，准备开始转换
		5）校准ADC
		6）软件触发ADC，开始转换
		7)编写中断服务函数
	3.DMA模式
		1）开启DMA时钟和ADC时钟
		2）DMA结构体
		3）开启Cmd使能控制
		4）初始化ADC结构体
		5）开启ADCDMA模式
		5）CmdADC
	4.双重DMA读取高16位存ADC2 低十六位存ADC1，但是数据对其方式都是右对齐
**/
