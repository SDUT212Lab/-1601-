
#include "stm32f10x.h"
#include "ht1261.h"
#include "delay.h"
#include "group_key.h"
#include "dht11.h"

int main(void)
{	
	HT1261_Init();
	DHT11_Init();
	HT1621_LED_ON();
	float Temper;
	while(1)
	{
		DHT11_Read_Data();
		Temper = DHT11_Read_Temper()-5.5;
		HT1261_Display_Data(Temper*100,2,1,1,1);
		delay_ms(1000);
	}
}
