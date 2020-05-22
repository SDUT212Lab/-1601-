#include "SYSTICK.h"

#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	
	//�ж��Ƿ����2��24�η�
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
                           
	//����Sys��LOAD�Ĵ�������¼��ʼֵ
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	//����ϵͳ��ʱ�������ȼ���ͬ�������ó���ռ���ȼ�����Ӧ���ȼ�
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
	//����sys��ʱ�ӣ�0��72M 1��9M
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	//ʹ���жϣ�ʹ��SYs
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | //���ʱ��Դѡ��
                   SysTick_CTRL_TICKINT_Msk   | //������0ʱ��1
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}
//����ϵͳ�δ�ʱ����ʼ������

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
�ʼǣ�
	1.����һ��ϵͳ��ʱ�� 24λ ֻ�ܵݼ����������ں���1ms��ʱ
	2.��reload�ĳ�ֵ��ʼ�ݼ���0�������жϺ�COUNTFLAG

**/
