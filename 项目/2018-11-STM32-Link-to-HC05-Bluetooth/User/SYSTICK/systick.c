#include "systick.h"
/**
*���ƣ���ȷ��ʱ����
*���ߣ��³�
*ʱ�䣺2018��9��
*�汾��1.0
*���£�1.0����
**/
/**
 *name:void SysTick_delay_us(uint32_t us)
 *fun :΢����ʱ
 *para:us:΢����
 *ret :void
**/
void SysTick_delay_us(uint32_t us)
{
	uint32_t i = 0;
	if(SysTick_Config(SystemCoreClock/1000000))
	{
		while(1);
	}
	for(i = 0;i<us;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
	
}
/**
 *name:void SysTick_delay_ms(uint32_t ms)
 *fun :������ʱ
 *para:ms:������
 *ret :void
**/
void SysTick_delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
	for(i = 0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
}
