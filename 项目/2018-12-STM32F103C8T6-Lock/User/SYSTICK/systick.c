#include "systick.h"
/**
*���ƣ��δ�ʱ����ʼ������
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
void SysTick_Init(uint32_t cnt)
{
	if(SysTick_Config(SystemCoreClock/cnt))						//ÿ72M/(cnt*SysTickClock)s����һ���жϣ����ϵͳʱ������Ϊ72 M��cnt = 1000���൱��1ms����һ��
	{
		while(1);
	}
	
}

