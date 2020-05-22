/*头文件*/
#include "user_system.h"
/*全局状态机变量*/
uint32_t LED_toogle_cnt = 0;
uint32_t Motor1_cnt = 0;
uint32_t Motor2_cnt = 0;
uint32_t Motor1_Speed = 0;
uint32_t Motor2_Speed = 0;
uint32_t mpu6050_cnt = 0;
/*引用的其他变量*/
extern struct tm rtc_time;
extern PID_TypeDef DUOJI_pid;
/*主函数*/
int main(void)
{	
	DUOJI_pid.Kp = 0.1;
	DUOJI_pid.Kd = 0.5;
	DUOJI_pid.Ki = 0.5;
	System_Init();
	while(1)
	{
		delay_Ms(500);
	

	}	
}
