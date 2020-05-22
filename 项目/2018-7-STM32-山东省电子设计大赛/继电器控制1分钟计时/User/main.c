
#include "stm32f10x.h"
#include "bsp_led.h"
# include "key.h"
#include "DS18B20.h"
#include "USART.h"
#include "delay.h"
#include "RCC.h"
#include <string.h>
#include "beep.h"
#include "exit.h"
#include "dma.h"
#include "adc.h"
#include "1602.h"
#include "28byj.h"
#include "SYSTICK.h"
extern uint32_t ADC1_Value;
extern uint32_t ADC2_Value;
float ADC1_ValueConv;
float ADC2_ValueConv;
int main()
{
	LED_Init();
	KEY_Init();
	BEEP_Init();
	JDQ_Init();
	
	while(1)
	{	
		JDQ_ON;		
		if(KEY_Scan(0) == 1)
		{
			System_Init();
		}
		
	}
}


