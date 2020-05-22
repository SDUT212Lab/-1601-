#include "systick.h"
/**
*名称：精确延时函数
*作者：陈冲
*时间：2018年9月
*版本：1.0
*更新：1.0：无
**/
/**
 *name:void SysTick_delay_us(uint32_t us)
 *fun :微秒延时
 *para:us:微秒数
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
 *fun :毫秒延时
 *para:ms:毫秒数
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
