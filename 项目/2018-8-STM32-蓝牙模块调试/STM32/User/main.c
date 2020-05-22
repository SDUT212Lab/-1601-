#include "stm32f10x.h"
#include "blue_tooth.h"
#include "stdio.h"
#include "delay.h"
#include "dht11.h"

int main(void)
{	
	Blue_Tooth_Init();
	DHT11_Init();
	while(1)
	{
		
	}
}
