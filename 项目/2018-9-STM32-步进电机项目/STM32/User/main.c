#include "stm32f10x.h"
#include "LCD12864.h"
#include "delay.h"
#include "touch_key.h"
#include "internal_flash.h"

uint32_t i;
uint32_t j;
int main(void)
{	
	LCD12864_Init();
	Touch_Key_Init();
	LCD12864_WriteStr("当前已转",1,1);
	LCD12864_WriteStr("圈",2,8);
	KEY_Init();
	uint8_t temp =1;
	while(1)
	{
		if(temp == 1)
		
		{
			Internal_Flash_Read_Data(&j,0x800A000,0x800B000);
			Internal_Flash_Read_Data(&i,0x8008000,0x8009000);
			temp++;
		}
		else 
		{
			{
				if(j == '.' || j <=10)
				j = i;
				InternalFlash_Test(&j,0x800A000,0x800B000);
				if(i == '.' || i <= 10)
				i = j;
				InternalFlash_Test(&i,0x8008000,0x8009000);
			}
			
			
			LCD12864_WriteNum(i,2,1);
			
		}
		
	
	}
	
}





