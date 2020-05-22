#include "exit.h"

static void MyNVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	//配置NVIC为优先组1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//配置中断源1
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	//配置抢占优先级1，打断其他的中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	
	//配置中断通道，开启关闭中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	

	
}	

void EXIT_PB6_Init(FunctionalState Flag)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//打开APB2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	MyNVIC_Init();
	
	/*GPIO配置*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line6;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStruct.EXTI_LineCmd = Flag;
	
	EXTI_Init(&EXTI_InitStruct);
}

void EXIT_PB7_Init(FunctionalState Flag)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//打开APB2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	MyNVIC_Init();
	
	/*GPIO配置*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line7;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStruct.EXTI_LineCmd = Flag;
	
	EXTI_Init(&EXTI_InitStruct);
}

void EXIT_PB8_Init(FunctionalState Flag)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//打开APB2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	MyNVIC_Init();
	
	/*GPIO配置*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line8;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStruct.EXTI_LineCmd = Flag;
	
	EXTI_Init(&EXTI_InitStruct);
}
/**笔记
	
	1.抢占优先级和响应优先级
		配置响应优先级1，相应优先级是指在抢占优先级相同的情况下，
		如果两个中断同时到达，那么先处理相应优先级高的中断
		////////////////////////////////////////////////////////////////
		//中断向量		|		抢占优先级			|	相应优先级	  //
		//      A		|			0 				|		0		  //
		//      B		|			1 				|		0		  //
		//      C		|			1 				|		1		  //
		////////////////////////////////////////////////////////////////
		
		如果内核正在执行C中断服务函数，那么它能被优先级更高的中断A打断由
		于B和C的前后只能优先级相同，C不能被B打断，但是如果B和C是同时到达
		的，内核先相应B中断。
	2.NVIC的优先级组
		在配置优先级的时候，要注意中断种类的数量。NVIC只可以配置16种中断
		向量的数量，也就是说，抢占优先级和响应优先级由一个四位数字决定。
		把这个四位数字分配成抢占优先级和响应优先级。有五种分配模式
		1）四位全部是响应优先级
		2）最高位是抢占优先级，其他三位是响应优先级，16中中断向量之中，
		0级抢占，0-7级相应，1级抢占，0-7级相应
		3）。。。
	3.EXTI外部中断
		STM的所有GPIO都引入到EXTI的外部中断线上，使得所有的GPIO都能作为外部中断
		的输入源PA0-PG0 连接到EXIT0，PA1-PG1 连接到 EXTI1 .。。。，EXITx只能相应
		一个端口的事件触发。最普通的应用就是接上一个按键，设置为下降沿触发，用
		中断检测按键。
		EXTI_InitStruct.EXTI_Line = EXTI_Line5;  给EXTI
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;选择中断还是选择事件
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;选择中断触发的方式
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;打开或者关闭中断
	4.AFIO时钟
		RCC_APB2PeriphClockCmd()；是还输入了参数RCC_APB2Periph_AFIO表示开启了AFIO
		时钟。
		GPIO除了用作输入输出外，还可以作为片上外设的复用输入输出，如串口、ADC等
		大多数的GPIO都有一个默认的复用功能，有的GPIO还有重映射功能。重映射功能是指
		能把原来属于A引脚的默认复用功能转移到B引脚进行使用，前提是B引脚具有重映射
		功能
		当把GPIO用作EXTI外部中断或者使用重映射功能时，就必须打开AFIO时钟，使用默认
		复用功能时，就不需要打开AFIO时钟
	5.建立GPIO中断的步骤
		1）设置NVIC控制器初始化（配置优先组NVIC_PriorityGroupConfig）
		打开时钟
		2）GPIO初始化
		3）外部中断初始化
	
**/
