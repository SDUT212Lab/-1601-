// bsp board surport package 板级支持包 只和这一个板子有关
#include "USART.h" //每次建立一个头文件都得用魔术棒包含进来

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
	
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
	
	//GPIO初始化
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//USART结构体初始化
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits =USART_StopBits_1;//不匹配可能会出现乱码
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStruct);
	
	//配置优先级初始化
	USART1_NVIC_Init();
	
	//中断初始化，这是库函数,接受中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//发送完成中断
//	USART_ITConfig(USART1,USART_IT_TC,ENABLE);
	//发送中断
//	USART_ITConfig(USART1,USART_IT_TC,ENABLE);
	//奇偶错误中断
//	USART_ITConfig(USART1,USART_IT_PE,ENABLE);
//	//总线空闲中断
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);

	
	USART_Cmd(USART1,ENABLE);
}
void USART1_SendByte(uint8_t ch)
{
	USART_SendData(USART1,ch);
	//等待发送数据存储器为空
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
//重新定向fputc
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(unsigned char) ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	return ch;
}

int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void Print_Menu()
{
	USART1_SendString("\
			//////////////////////////////////////////////////////\n\
			//                                                  //\n\
			//              欢迎使用控制系统                    //\n\
			//              作者：陈冲                          //\n\
			//              时间：2018年6月                     //\n\
			//                                                  //\n\
			//////////////////////////////////////////////////////\n\
			//                                                  //\n\
			//              数字0：转换LED0                     //\n\
			//              数字1：转换LED1                     //\n\
			//              数字2：转换LED2                     //\n\
			//              数字3：打开BEEP                     //\n\
			//              数字4：关闭BEEP                     //\n\
			//              数字5：开启按键IT                   //\n\
			//              数字6：关闭按键IT                   //\n\
			//              数字7：打印菜单                     //\n\
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
		printf("\r\n当前时间：%s%d:%s%d:%s%d\r\n",hour<10? "0":"",\
	hour,minute<10? "0":"",minute,second<10? "0":"",second);
	}
	
}
/**
笔记
	1.配置串口通信的参数：字长（一次性传输数据的长度） 波特率：每秒传输数据位的个数 奇偶校验位 停止位
	2.直通线和交叉线
		2接2 3接3 
		2-3 3-2
	3.串口工作过程
		1）波特率控制 2）收发控制 3）数据存储转移
	4.GPIO复用功能设置
		///////////////////////////////////////////////////
		//	TX	|	全双工	|		推挽复用输出		//
		//	  	|	半双工	|		推挽复用输出		//
		//	RX	|	全双工	|		浮空输入或者上拉输入//
		//		|	半双工	|			未用			//
		//////////////////////////////////////////////////
	5.USART初始化
		USART_WordLength = USART_WordLength_8b 也可以设置成9
		USART_StopBits = USART_StopBits_1 配置停止位，把通信协议中的停止位设置成1位，影响不大
		USART_Parity = USART_Parity_No 配置奇偶校验位
		USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 全双工打开
	6.USART是等待输入的
	7.串口中断
	#define USART_IT_PE		奇偶错误中断
	#define USART_IT_TXE 	发送中断
	#define USART_IT_TC		传输完成中断
	#define USART_IT_RXNE	
	#define USART_IT_IDLE	
	#define USART_IT_LBD	
	#define USART_IT_CTS	
	#define USART_IT_ERR	
	#define USART_IT_ORE	
	#define USART_IT_NE		
	#define USART_IT_FE	

**/




