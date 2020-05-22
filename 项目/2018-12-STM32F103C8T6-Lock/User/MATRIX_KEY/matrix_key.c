#include "matrix_key.h"
#include "delay.h"

void Matrix_Key_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	R1_CLKCMD(R1_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = R1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(R1_PORT,&GPIO_InitStructure);
	
	R2_CLKCMD(R2_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = R2_PIN;
	GPIO_Init(R2_PORT,&GPIO_InitStructure);
	
	R3_CLKCMD(R3_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = R3_PIN;
	GPIO_Init(R3_PORT,&GPIO_InitStructure);

	R4_CLKCMD(R4_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = R4_PIN;
	GPIO_Init(R4_PORT,&GPIO_InitStructure);
	R1_L;R2_L;R3_L;R4_L;
	
	C1_CLKCMD(C1_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = C1_PIN;
	GPIO_Init(C1_PORT,&GPIO_InitStructure);
	
	C2_CLKCMD(C2_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = C2_PIN;
	GPIO_Init(C2_PORT,&GPIO_InitStructure);
	
	C3_CLKCMD(C3_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = C3_PIN;
	GPIO_Init(C3_PORT,&GPIO_InitStructure);
	
	C4_CLKCMD(C4_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = C4_PIN;
	GPIO_Init(C4_PORT,&GPIO_InitStructure);
	
}
void Matrix_Init()
{
	Matrix_Key_GPIO_Init();
}
extern uint32_t Matrix_KEY_cnt;
uint8_t Matrix_Scan()
{
	
	{
		R1_H;R2_L;R3_L;R4_L;
		if (C1_DATA ) { delay_ms(10); while(C1_DATA);return 1;}  else if  (C2_DATA ) { delay_ms(10);while(C2_DATA);return 2;} 
		else
		if (C3_DATA ) { delay_ms(10);while(C3_DATA);return 3;}  else if  (C4_DATA ) { delay_ms(10);while(C4_DATA);return 10;} 
		R1_L;R2_H;R3_L;R4_L;
		if (C1_DATA ) { delay_ms(10); while(C1_DATA);return 4;}   else if  (C2_DATA ) { delay_ms(10);while(C2_DATA);return 5;} 
		else
		if (C3_DATA ) { delay_ms(10);while(C3_DATA);return 6;}   else if  (C4_DATA ) { delay_ms(10);while(C4_DATA);return 11;} 
		R1_L;R2_L;R3_H;R4_L;
		if (C1_DATA ) { delay_ms(10);while(C1_DATA);return 7;}   else if  (C2_DATA ) { delay_ms(10);while(C2_DATA);return 8;} 
		else
		if (C3_DATA ) { delay_ms(10);while(C3_DATA);return 9;}   else if  (C4_DATA ) { delay_ms(10);while(C4_DATA);return 12;} 
		R1_L;R2_L;R3_L;R4_H;
		if (C1_DATA ) { delay_ms(10);while(C1_DATA);return 15;}  else if  (C2_DATA ) { delay_ms(10);while(C2_DATA);return 0;} 
		else
		if (C3_DATA ) { delay_ms(10);while(C3_DATA);return 14;}  else if  (C4_DATA ) { delay_ms(10);while(C4_DATA);return 13;}  
		
	}
	return  20;
}
	
	

