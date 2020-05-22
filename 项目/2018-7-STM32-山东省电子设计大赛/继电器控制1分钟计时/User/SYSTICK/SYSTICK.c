#include "SYSTICK.h"

#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	
	//判断是否大于2的24次方
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
                           
	//配置Sys的LOAD寄存器，记录初始值
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	//配置系统定时器的优先级，同样的设置成抢占优先级和响应优先级
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
	//配置sys的时钟，0是72M 1是9M
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	//使能中断，使能SYs
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | //这个时钟源选择
                   SysTick_CTRL_TICKINT_Msk   | //倒数到0时置1
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}
//配置系统滴答定时器初始化函数

#endif
void SysTick_delay_us(uint32_t us)
{
	uint32_t i = 0;
	SysTick_Config(72);
	
	for(i=0;i<us;i++)
	{
		while(!((SysTick->CTRL) &(1<<16)));
		
	}
	
	SysTick ->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
void SysTick_delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	
	SysTick_Config(72000);
	
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL) &(1<<16)));
		
	}
	
	SysTick ->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


/**
笔记：
	1.这是一个系统定时器 24位 只能递减，存在于内核中1ms定时
	2.从reload的初值开始递减到0，产生中断和COUNTFLAG

**/
