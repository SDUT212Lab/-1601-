/*ͷ�ļ�*/
#include "user_system.h"
/*ȫ��״̬������*/
uint32_t LED_toogle_cnt = 0;
/*���õ���������*/
extern struct tm rtc_time;

/*������*/
int main(void)
{	
	System_Init();
	USARTLCD_Page(1);
	
	while(1)
	{
		/*write your code here*/
		
	}
}
