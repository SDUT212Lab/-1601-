
#include "stm32f10x.h"
#include "ht1261.h"
#include "delay.h"

int main(void)
{	
	HT1261_Init();
	uint16_t i = 0;
	while(1)
	{
		HT1261_Display_Data(i,3,1,0,0);
		delay_ms(333);
		HT1261_Display_Data(i,0,1,1,0);
		delay_ms(333);
		HT1261_Display_Data(i,0,1,1,1);
		delay_ms(333);
		i++;
	}
}
