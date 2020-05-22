#include "user_test.h"

extern uint8_t fashe_flag;
extern uint8_t xuanzhuan_flag;
extern struct tm rtc_time;
extern uint32_t Distance;			//超声波测距
extern uint16_t distance_v;		//输入的距离
extern uint16_t angle_v;			//输入的角度
extern uint16_t angle_pid;
extern uint8_t test_flag;			//题目flag
extern uint8_t start_flag;		//开始按钮
extern uint8_t dir_flag;
extern PID_TypeDef DUOJI_pid;


uint16_t duoji1_i = 0;
uint16_t duoji2_i = 0;
//输入距离模式
void Test1()
{
	USARTLCD_SetFlo("var3.txt",distance_v);
	DUOJI2_Speed(39);
	if(distance_v != 0)
	{
		DUOJI1_Speed(Calculate_angle(distance_v));
		delay_ms(500);
		FASHE;
		delay_ms(3000);
		CHARGE;
		test_flag = 0;
		USARTLCD_Page(0);
		distance_v = 0;
	}
}
//输入距离和角度模式
uint8_t test2_flag = 0;
void Test2()
{
	duoji2_i = angle_v;
	if(duoji2_i != 0)
	{
		DUOJI2_Speed(duoji2_i);
		delay_ms(500);
		test2_flag = 1;
	}
	if(distance_v != 0 && test2_flag == 1)
	{
		USARTLCD_SetFlo("var3.txt",distance_v);
		DUOJI1_Speed(Calculate_angle(distance_v));
		delay_ms(1000);
		DUOJI2_Speed(39);
		delay_ms(3000);
		FASHE;
		delay_ms(3000);
		CHARGE;
		test_flag = 0;
		USARTLCD_Page(0);
		distance_v = 0;
		angle_v = 0;
		test2_flag = 0;
	}
}
//自由射击1
void Test3()
{
	fashe_flag = 0;
	DUOJI2_Speed(26);
	delay_ms(1000);
	for(uint8_t i = 26;i<=68;i++)
	{
		DUOJI2_Speed(i);
		delay_ms(200);
		if(fashe_flag == 2)
		{
			DUOJI1_Speed(Calculate_angle1(Distance));
			delay_ms(500);
			FASHE;
			delay_ms(3000);
			CHARGE;
			test_flag = 0;
			USARTLCD_SetFlo("var3.txt",fashe_flag);
			while(1);
		}
	}
}
//自由射击2
void Test4()
{
	fashe_flag = 0;
	DUOJI2_Speed(26);
	delay_ms(1000);
	for(uint8_t i = 26;i<=68;i++)
	{
		DUOJI2_Speed(i);
		delay_ms(150);
		if(fashe_flag == 2)
		{
			DUOJI1_Speed(Calculate_angle1(Distance));
			delay_ms(500);
			FASHE;
			delay_ms(3000);
			CHARGE;
			test_flag = 0;
			USARTLCD_SetFlo("var3.txt",fashe_flag);
			while(1);
		}
	}
}
//自动控制
void Test5()
{
	switch(dir_flag)
	{
		case 1:  duoji2_i+=1;DUOJI2_Speed(duoji2_i);dir_flag = 0;break;
		case 2:  duoji1_i+=1;DUOJI1_Speed(duoji1_i);dir_flag = 0;break;
		case 3:  duoji2_i-=1;DUOJI2_Speed(duoji2_i);dir_flag = 0;break;
		case 4:  duoji1_i-=1;DUOJI1_Speed(duoji1_i);dir_flag = 0;break;
	}
	if(fashe_flag == 2)
	{
		fashe_flag = 0;
		FASHE;
		delay_ms(3000);
		CHARGE;
	}
}


