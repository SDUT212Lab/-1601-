/*ͷ�ļ�*/
#include "user_system.h"

/*ȫ��״̬������*/
uint32_t LED_toogle_cnt = 0;
uint8_t fashe_flag = 0;
uint8_t fashe_flag1 = 0;
uint8_t fashe_flag2 = 0;
uint8_t xuanzhuan_flag = 0;
/*���õ���������*/
extern struct tm rtc_time;
extern uint32_t Distance;			//���������
extern uint16_t distance_v;		//����ľ���
extern uint16_t angle_v;			//����ĽǶ�
extern uint16_t angle_pid;
extern uint8_t test_flag;			//��Ŀflag
extern uint8_t start_flag;		//��ʼ��ť
extern PID_TypeDef DUOJI_pid;
extern uint8_t dir_flag;
extern uint8_t dir;
extern float Pitch,Roll,Yaw;
//-30  26 0 45  30 68
//duoji1 10-50
/*������*/
extern uint16_t angle_pid ;
extern uint32_t mpu_time ;
extern PID_TypeDef DUOJI_pid;
extern uint16_t display_cnt;
extern uint16_t DUOJI1_Speed_cnt;
extern uint16_t DUOJI2_Speed_cnt;
extern uint16_t duoji1_i ;
extern uint16_t duoji2_i ;
int main(void)
{	
	
	System_Init();
	while(1)
	{ 
	
//		switch(test_flag)
//		{
//			case 1: Test1();break;
//			case 2: Test2();break;
//			case 3: Test3();break;
//			case 4: Test4();break;
//			case 5: Test5();break;
//		}
//		if(display_cnt >= 50)
//		{
//			Distance = Senor_Using();	
//			display_cnt=0;
//			USARTLCD_SetFlo("var0.txt",Distance);
//			USARTLCD_SetFlo("var1.txt",Roll);
//			USARTLCD_SetFlo("var2.txt",test_flag);
//			USARTLCD_SetFlo("var4.txt",duoji2_i);	
//			USARTLCD_SetFlo("var5.txt",duoji1_i);	
//			USARTLCD_SetFlo("var6.txt",dir);	
//		}
		delay_ms(500);
//		MPU6050_Pose();
		USART_x_Send_Float(USART1,Pitch);
	} 
}


//�����Ѿ�ʵ�ֵĹ�����
/*
1.��������࣬��SysTick�У�ÿ50ms��ȡһ��

*/

