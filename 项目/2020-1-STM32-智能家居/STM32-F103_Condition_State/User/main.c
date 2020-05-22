/*头文件*/
#include "user_system.h"
/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;
/*引用的其他变量*/
extern struct tm rtc_time;

/*主函数*/
int main(void)
{	
	System_Init();
	USARTLCD_Page(1);
	
	while(1)
	{
		/*write your code here*/
		
	}
}
