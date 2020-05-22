#include "systick.h"
/**
*名称：滴答定时器初始化函数
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
void SysTick_Init(uint32_t cnt)
{
	if(SysTick_Config(SystemCoreClock/cnt))						//每72M/(cnt*SysTickClock)s进入一次中断，如果系统时钟配置为72 M，cnt = 1000，相当于1ms进入一次
	{
		while(1);
	}
	
}

