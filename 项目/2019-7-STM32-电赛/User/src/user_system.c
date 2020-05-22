#include "user_system.h"

//一些简单的GPIO初始化

void FASHE_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	FASHE_GPIO_CLKCMD(FASHE_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = FASHE_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(FASHE_GPIO_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = CHARGE_GPIO_PIN;
	GPIO_Init(CHARGE_GPIO_PORT,&GPIO_InitStruct);
}
uint8_t jiaodu_data[21] = {33,33,32,27,26,25,24,23,22,21,21,20,20,19,18,18,17,17,16,16,15};
uint32_t Calculate_angle(uint32_t distance)
{
	if(distance>=295&&distance<=300)
		return jiaodu_data[0];
	else if(distance>=290&&distance<295)
		return jiaodu_data[1];
	else if(distance>=285&&distance<290)
		return jiaodu_data[2];
	else if(distance>=280&&distance<285)
		return jiaodu_data[3];
	else if(distance>=275&&distance<280)
		return jiaodu_data[4];
	else if(distance>=270&&distance<275)
		return jiaodu_data[5];
	else if(distance>=265&&distance<270)
		return jiaodu_data[6];
	else if(distance>=260&&distance<265)
		return jiaodu_data[7];
	else if(distance>=255&&distance<260)
		return jiaodu_data[8];
	else if(distance>=250&&distance<255)
		return jiaodu_data[9];
	else if(distance>=245&&distance<250)
		return jiaodu_data[10];
	else if(distance>=240&&distance<245)
		return jiaodu_data[11];
	else if(distance>=235&&distance<240)
		return jiaodu_data[12];
	else if(distance>=230&&distance<235)
		return jiaodu_data[13];
	else if(distance>=225&&distance<230)
		return jiaodu_data[14];
	else if(distance>=220&&distance<225)
		return jiaodu_data[15];
	else if(distance>=215&&distance<220)
		return jiaodu_data[16];
	else if(distance>=210&&distance<215)
		return jiaodu_data[17];
	else if(distance>=205&&distance<210)
		return jiaodu_data[18];
	else if(distance>=200&&distance<205)
		return jiaodu_data[19];
}
uint32_t Calculate_angle1(uint32_t distance)
{	
	if(distance<130)
	{
		return 18;
	}
	else if(distance>=130&&distance<=140)
	{
		return 21;
	}else if(distance>140&&distance<=157)
	{
		return 25;
	}else if(distance >157&&distance<162)
	{
		return 27;
	}
	else if(distance >=162&&distance<174)
	{
		return 33;
	}
}

/*
*name:void System_Init()
*fun :系统初始化函数，包含了一些系统端口初始化的定义
*para:void
*fun :void
*/
void System_Init()
{
	
	SysTick_Init(1000); //初始化状态机为1ms
	LED_Init();
	USARTLCD_Init();
	DUOJI_Init();
	CH_SR04_Init();
	MPU6050_Init();  //初始化陀螺仪
	GENERAL_TIM_Init();
//	FASHE_GPIO_Init();
//	CHARGE;
//	delay_ms(1000);
//	Interp_Init();
//	USARTLCD_SetVal("init_flag",1);
//	DUOJI2_Speed(38);
//	DUOJI1_Speed(28);
//	
}
