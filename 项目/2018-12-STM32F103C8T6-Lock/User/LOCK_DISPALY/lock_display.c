#include "lock_display.h"
#include "delay.h"
#include "string.h"
#include "28byj.h"
#include "general_tim.h"
#include "ht1261.h"
#include "mg90s.h"
/**
*名称：LED驱动函数
*作者：陈冲
*时间：2018年10月
*版本：1.0
*更新：1.0：无
**/
extern uint16_t password_lock_cnt;
extern uint32_t time;
extern uint32_t input_time;



uint8_t Lock_Button_Start()
{
	uint8_t j = 0;
	
	j = Matrix_Scan();
	return j;
}

uint8_t Lock_Dislay_Input()
{
	uint32_t password = 0;
	uint8_t i = 0;
	uint8_t j = 0;
	TIM_Cmd(GENERAL_TIM,ENABLE);
	while(j!= LOCK_OK)
	{
		if(input_time> 2000)
		{
			TIM_Cmd(GENERAL_TIM,DISABLE);
			input_time = 0;
			return  2;
		}
		j = Matrix_Scan();
		if(j<=9)
		{
			password += j*pow(10,5-i);
			HT1261_Display_Data(password,5,0,0,0);
			i++;
		}
	
		if(j == LOCK_BACKSPACE&& i != 0 )
		{
			
			password -=((uint32_t)(password/pow(10,6-i))%10)*pow(10,6-i) ;//123

			HT1261_Display_Data(password,5,0,0,0);
			i--;
			
		}
		if(j == LOCK_CANCEL)
		{
			TIM_Cmd(GENERAL_TIM,DISABLE);
			input_time = 0;
			return  2;
		}
	}
	if(password==PASSWORD)
	{
		
		TIM_Cmd(GENERAL_TIM,DISABLE);
		input_time = 0;
		return 1;
	}
	else
	{
		
		TIM_Cmd(GENERAL_TIM,DISABLE);
		input_time = 0;
	}	
	return 0;
}

uint8_t Lock_Judge()
{
	uint8_t j = 0;
	while(j ==0)
	{
		j = Lock_Dislay_Input();
		if(j == 1)
		{
			HT1261_Display_Data(888888,5,0,0,0);
			return 1;
		}
		else if(j == 0)
		{
			HT1261_Display_Data(0,5,0,0,0);
		}
		else if( j== 2)
		{
			HT1261_Display_Data(0,5,0,0,0);
			return 0;
		}
	}
	HT1261_Display_Data(0,5,0,0,0);
	return 0;
}
void Lock_Open()
{
	MG90S_Wenkle(3000,1);
	
	MG90S_Wenkle(500,0);
}
void Lock_Dispaly()
{
	if(Lock_Button_Start() == LOCK_START)
	{
		if(Lock_Judge() == 1)
		{
			Lock_Open();
			delay_ms(300);
			HT1261_Display_Data(0,5,0,0,0);
		}
	}
}

