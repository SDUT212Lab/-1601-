#include "user_wave.h"
#include "user_delay.h"


void Wave_Cap_Init(u16 arr,u16 psc)	
{	 
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	WAVE_TIM_CLKCMD(WAVE_TIM_CLK, ENABLE);	
 	WAVE_GPIO_CLKCMD(WAVE_GPIO_CLK, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin  = WAVE_TIM_Channel_Pin; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   
	GPIO_Init(WAVE_TIM_Channel_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = WAVE_GPIO_Trigger_Pin;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     
	GPIO_Init(WAVE_GPIO_Trigger_Prot, &GPIO_InitStructure);
	
	//��ʼ����ʱ�� 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(WAVE_TIM, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3���벶�����
	TIM_ICInitStructure.TIM_Channel = WAVE_TIM_Channel; //CC1S=01 	ѡ������� IC3ӳ�䵽TI3��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;//���������˲��� ���˲�
	TIM_ICInit(WAVE_TIM, &TIM_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = WAVE_TIM_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 	
	TIM_ITConfig(WAVE_TIM,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC3IE�����ж�	
	TIM_Cmd(WAVE_TIM,ENABLE ); 	//ʹ�ܶ�ʱ��3
}

/*�������ز����պ���*/
uint32_t PreDistance;
uint16_t TIM3CH3_CAPTURE_STA,TIM3CH3_CAPTURE_VAL;
void Read_Distane(void)
{   
	GPIO_SetBits(WAVE_GPIO_Trigger_Prot,WAVE_GPIO_Trigger_Pin);
	delay_us(15);  
	GPIO_ResetBits(WAVE_GPIO_Trigger_Prot,WAVE_GPIO_Trigger_Pin);
	if(TIM3CH3_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
	{
		PreDistance=TIM3CH3_CAPTURE_STA&0X3F;
		PreDistance*=65536;					        //���ʱ���ܺ�
		PreDistance+=TIM3CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
		PreDistance=PreDistance*170/1000;
		TIM3CH3_CAPTURE_STA=0;			//������һ�β���
	}			
}

