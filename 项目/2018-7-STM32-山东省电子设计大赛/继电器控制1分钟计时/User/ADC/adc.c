#include "adc.h"
//PA1 ADCͨ��

__IO  uint32_t  ADC1_Value;

//static ��ֹ�������������,��ʾ��ǰ�ļ�����
static void ADC2_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//ģ������
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
	
	//��ʱ�ӣ�ADC2������DMA��ʱ�ӹ���APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);

	//ADC����
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//����ģʽ������˫ͨ��ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//��ֹɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//��������ת��ģʽ����ͣ�Ľ���adcת����
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//�ⲿ����
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//�ɼ������Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//Ҫ��ת����ͨ����Ŀ

	ADC_Init(ADC2,&ADC_InitStruct);
	
	//����ADCʱ�ӣ�ΪPCLK2�İ˷�Ƶ����9Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//����ADC�Ĺ���ͨ�����ã�rank��ʾת��˳�����һ������Ϊ����ʱ��
	ADC_RegularChannelConfig(ADC2,ADC_Channel_2,1,ADC_SampleTime_55Cycles5);

	//�ж�����
	ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);
	//����ADC
	ADC_Cmd(ADC2,ENABLE);
	//У׼ADC
	ADC_StartCalibration(ADC2);
	
	//�ȴ�����ź�
	while(ADC_GetCalibrationStatus(ADC2));
	
	//�������
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	
}
//ħ��������ѡ��C99 mode
static void ADC1_DMA_Init()
{
	DMA_InitTypeDef DMA_InitStruct;
	
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_AHBPeriphClockCmd(AHB_CLK_DMA,ENABLE);
	//��ʱ�ӣ�ADC2������DMA��ʱ�ӹ���APB2
	RCC_APB2PeriphClockCmd(APB_ADC_CLK,ENABLE);
	DMA_DeInit(DMAm_CHANNEL_n);
	//form and to
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) &ADC1_Value;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//�����٣���λ��ʲô
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	//�����ģʽ��ʲô
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMAm_CHANNEL_n,&DMA_InitStruct);
	
	DMA_Cmd(DMAm_CHANNEL_n,ENABLE);

	
/*---------------------------------------------------------------------*/	


	//ADC����
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		//����ģʽ������˫ͨ��ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//��ֹɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//��������ת��ģʽ����ͣ�Ľ���adcת����
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//�ⲿ����
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//�ɼ������Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//Ҫ��ת����ͨ����Ŀ

	ADC_Init(ADC_x,&ADC_InitStruct);
	
	//����ADCʱ�ӣ�ΪPCLK2�İ˷�Ƶ����9Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//����ADC�Ĺ���ͨ�����ã�rank��ʾת��˳�����һ������Ϊ����ʱ��
	ADC_RegularChannelConfig(ADC_x,ADC_Channel_m,1,ADC_SampleTime_55Cycles5);

	ADC_DMACmd(ADC_x,ENABLE);
	//����ADC
	ADC_Cmd(ADC_x,ENABLE);
	//У׼ADC
	ADC_StartCalibration(ADC_x);
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	//�ȴ�����ź�
	while(ADC_GetCalibrationStatus(ADC_x));
	
	//�������
	ADC_SoftwareStartConvCmd(ADC_x,ENABLE);
		
	
}

static void ADC_DMADouble_Init()
{
	DMA_InitTypeDef DMA_InitStruct;
	
	ADC_InitTypeDef ADC_InitStruct;
	//ֻ��ADC1��DMA����
	RCC_AHBPeriphClockCmd(AHB_CLK_DMA,ENABLE);
	//��ʱ�ӣ�ADC2������DMA��ʱ�ӹ���APB2
	RCC_APB2PeriphClockCmd(APB_ADC_CLK,ENABLE);
	DMA_DeInit(DMAm_CHANNEL_n);
	//form and to
	DMA_InitStruct.DMA_PeripheralBaseAddr =(uint32_t)(&( ADC_x->DR ));
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) &ADC1_Value;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//�����٣���λ��ʲô
	DMA_InitStruct.DMA_BufferSize = 1;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	//�����ģʽ��ʲô
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMAm_CHANNEL_n,&DMA_InitStruct);
	
	DMA_Cmd(DMAm_CHANNEL_n,ENABLE);

	
/*---------------------------------------------------------------------*/	


	//ADC1����
	ADC_InitStruct.ADC_Mode = ADC_Mode_RegSimult;		//����ģʽ������˫ͨ��ģʽ,���Դ�˫ͨ��ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//��ֹɨ��ģʽ��ÿ��ADC���ж��ͨ��ʱ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//��������ת��ģʽ����ͣ�Ľ���adcת����
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//�ⲿ����
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//�ɼ������Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//Ҫ��ת����ͨ����Ŀ

	ADC_Init(ADC_x,&ADC_InitStruct);
	
	//����ADCʱ�ӣ�ΪPCLK2�İ˷�Ƶ����9Mhz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����һ�ξͿ���
	
	//����ADC�Ĺ���ͨ�����ã�rank��ʾת��˳�����һ������Ϊ����ʱ��
	ADC_RegularChannelConfig(ADC_x,ADC_Channel_m,1,ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADC_x,ENABLE);
	//����ADC
	ADC_Cmd(ADC_x,ENABLE);
	ADC_ResetCalibration(ADC_x);
	while(ADC_GetResetCalibrationStatus(ADC_x));	
	ADC_StartCalibration(ADC_x); 
	while(ADC_GetCalibrationStatus(ADC_x));

	//ADC2����
	ADC_InitStruct.ADC_Mode = ADC_Mode_RegSimult;		//����ģʽ������˫ͨ��ģʽ,���Դ�˫ͨ��ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; 			//��ֹɨ��ģʽ��ÿ��ADC���ж��ͨ��ʱ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		//��������ת��ģʽ����ͣ�Ľ���adcת����
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//�ⲿ����
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//�ɼ������Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;				//Ҫ��ת����ͨ����Ŀ

	ADC_Init(ADC_y,&ADC_InitStruct);
	
	
	//����ADC�Ĺ���ͨ�����ã�rank��ʾת��˳�����һ������Ϊ����ʱ��
	ADC_RegularChannelConfig(ADC_y,ADC_Channel_n,1,ADC_SampleTime_55Cycles5);

	//����ADC
	ADC_Cmd(ADC_y,ENABLE);
	

	
	/*У׼ADC*/
	// ��ʼ��ADC У׼�Ĵ���, �ȴ�У׼�Ĵ�����ʼ����� 
	ADC_ResetCalibration(ADC_y);
	while(ADC_GetResetCalibrationStatus(ADC_y)); 

	
	//��ʼУ׼���ȴ�����ź�
	ADC_StartCalibration(ADC_y); 
	while(ADC_GetCalibrationStatus(ADC_y));

	
	//�������
	ADC_ExternalTrigConvCmd(ADC_y,ENABLE);
	ADC_SoftwareStartConvCmd(ADC_x,ENABLE);//���ö�·ģʽʱ��ADC1Ϊ���������������ADCΪ�Ӳ����ⲿ����

	/*----------����ط������Ƚ�������ADC2���ⲿ������������ADC1
				�������������ΪADC2�Ĵ�����ADC1��һ���Ĵ�������
				�ģ�											---------------------*/

}




void ADC2_Init()
{
	ADC2_GPIO_Init();

	ADC2_Mode_Init();
}

void ADC1_Init() //ʹ��DMAģʽ
{
	ADC2_GPIO_Init();
	ADC1_DMA_Init();
}
void ADC12_Init()
{
	ADC2_GPIO_Init();
	ADC_DMADouble_Init();
}

/**�ʼ�
	1.ADC��Ҫ��ע�ĵط�
		1)�ֱ��� 
			12λ�ֱ��ʡ�����ֱ�Ӳ�������ѹ����С��������λΪLSB= Vref+/12
		2��ת��ʱ��
			ת��ʱ���ǿ��Ա�̵ġ�����һ�������÷�14��adcʱ�����ڣ�ADC��ʱ��Ƶ�����Ϊ14MHz�������ʱ����1Us
		3��ADC������
			ADC�����;����������ܵļ��ޣ�STM32ʹ�õ������αȽ�����ADC
		4���ο���ѹ�ķ�Χ
	2.���Ҫ��
		1����ʼ��ADC��GPIO�ṹ��
		2������ADC��ʱ�ӣ�ת��˳���ת��ʱ��
		3��ʹ��ADCת������жϣ��������ȼ�
		4)ʹ��ADc��׼����ʼת��
		5��У׼ADC
		6���������ADC����ʼת��
		7)��д�жϷ�����
	3.DMAģʽ
		1������DMAʱ�Ӻ�ADCʱ��
		2��DMA�ṹ��
		3������Cmdʹ�ܿ���
		4����ʼ��ADC�ṹ��
		5������ADCDMAģʽ
		5��CmdADC
	4.˫��DMA��ȡ��16λ��ADC2 ��ʮ��λ��ADC1���������ݶ��䷽ʽ�����Ҷ���
**/
