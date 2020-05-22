// bsp board surport package �弶֧�ְ� ֻ����һ�������й�
#include "USART.h" //ÿ�ν���һ��ͷ�ļ�������ħ������������

extern uint32_t cnt;

void USART1_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}


void USART1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
	
	//GPIO��ʼ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//USART�ṹ���ʼ��
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;//��ƥ����ܻ��������
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStruct);
	
	//�������ȼ���ʼ��
	USART1_NVIC_Init();
	
	//�жϳ�ʼ�������ǿ⺯��,�����ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//��������ж�
//	USART_ITConfig(USART1,USART_IT_TC,ENABLE);
	//�����ж�
//	USART_ITConfig(USART1,USART_IT_TC,ENABLE);
	//��ż�����ж�
//	USART_ITConfig(USART1,USART_IT_PE,ENABLE);
//	//���߿����ж�
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);

	
	USART_Cmd(USART1,ENABLE);
}
void USART1_SendByte(uint8_t ch)
{
	USART_SendData(USART1,ch);
	//�ȴ��������ݴ洢��Ϊ��
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void USART1_SendString(char *str)
{
	unsigned int k = 0;
	do {
			USART1_SendByte(*(str+k));
			k++;
			delay_ms(10);
		}while(*(str+k) != '\0');
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}
//���¶���fputc
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(unsigned char) ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	return ch;
}

int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void Print_Menu()
{
	USART1_SendString("\
			//////////////////////////////////////////////////////\n\
			//                                                  //\n\
			//              ��ӭʹ�ÿ���ϵͳ                    //\n\
			//              ���ߣ��³�                          //\n\
			//              ʱ�䣺2018��6��                     //\n\
			//                                                  //\n\
			//////////////////////////////////////////////////////\n\
			//                                                  //\n\
			//              ����0��ת��LED0                     //\n\
			//              ����1��ת��LED1                     //\n\
			//              ����2��ת��LED2                     //\n\
			//              ����3����BEEP                     //\n\
			//              ����4���ر�BEEP                     //\n\
			//              ����5����������IT                   //\n\
			//              ����6���رհ���IT                   //\n\
			//              ����7����ӡ�˵�                     //\n\
			//                                                  //\n\
			//////////////////////////////////////////////////////\n");
}


void USART1_SendTime()
{

	static uint8_t second;
	static uint8_t minute;
	static uint8_t hour;
	if(cnt ==10)
	{
		cnt = 0;
		second++;
		if(second>=60)
		{
			second = 0;
			minute++;
			if(minute ==60)
			{
				hour++;
				if(hour==24)
				{
					hour =0;
				}
			}
		}
		printf("\r\n��ǰʱ�䣺%s%d:%s%d:%s%d\r\n",hour<10? "0":"",\
	hour,minute<10? "0":"",minute,second<10? "0":"",second);
	}
	
}
/**
�ʼ�
	1.���ô���ͨ�ŵĲ������ֳ���һ���Դ������ݵĳ��ȣ� �����ʣ�ÿ�봫������λ�ĸ��� ��żУ��λ ֹͣλ
	2.ֱͨ�ߺͽ�����
		2��2 3��3 
		2-3 3-2
	3.���ڹ�������
		1�������ʿ��� 2���շ����� 3�����ݴ洢ת��
	4.GPIO���ù�������
		///////////////////////////////////////////////////
		//	TX	|	ȫ˫��	|		���츴�����		//
		//	  	|	��˫��	|		���츴�����		//
		//	RX	|	ȫ˫��	|		�������������������//
		//		|	��˫��	|			δ��			//
		//////////////////////////////////////////////////
	5.USART��ʼ��
		USART_WordLength = USART_WordLength_8b Ҳ�������ó�9
		USART_StopBits = USART_StopBits_1 ����ֹͣλ����ͨ��Э���е�ֹͣλ���ó�1λ��Ӱ�첻��
		USART_Parity = USART_Parity_No ������żУ��λ
		USART_Mode = USART_Mode_Tx | USART_Mode_Rx; ȫ˫����
	6.USART�ǵȴ������
	7.�����ж�
	#define USART_IT_PE		��ż�����ж�
	#define USART_IT_TXE 	�����ж�
	#define USART_IT_TC		��������ж�
	#define USART_IT_RXNE	
	#define USART_IT_IDLE	
	#define USART_IT_LBD	
	#define USART_IT_CTS	
	#define USART_IT_ERR	
	#define USART_IT_ORE	
	#define USART_IT_NE		
	#define USART_IT_FE	

**/




