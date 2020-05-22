#include "user_motor.h"

void Motor_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	MOTOR_IN_CLKCMD(MOTOR_IN_CLK,ENABLE);
	MOTOR_EN_CLKCMD(MOTOR_EN_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR1_IN1_PIN | MOTOR1_IN2_PIN | MOTOR2_IN1_PIN | MOTOR2_IN2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(MOTOR1_IN1_PORT ,&GPIO_InitStructure);
	GPIO_Init(MOTOR1_IN2_PORT ,&GPIO_InitStructure);
	GPIO_Init(MOTOR2_IN1_PORT ,&GPIO_InitStructure);
	GPIO_Init(MOTOR2_IN2_PORT ,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = MOTOR1_EN_PIN | MOTOR2_EN_PIN;
	
	GPIO_Init(MOTOR1_EN_PORT,&GPIO_InitStructure);
	GPIO_Init(MOTOR2_EN_PORT,&GPIO_InitStructure);
}

void Motor_Init()
{
	Motor_GPIO_Init();
	MOTOR1_IN1_H;
	MOTOR1_IN2_H;
	MOTOR2_IN1_H;
	MOTOR2_IN2_H;
	MOTOR1_EN_L;
	MOTOR2_EN_L;
}
extern uint32_t Motor1_cnt;
extern uint32_t Motor2_cnt;
extern uint32_t Motor1_Speed;
extern uint32_t Motor2_Speed;

void Motor_Speed(uint8_t Motor1_Speed_tmp,uint8_t Motor2_Speed_tmp)
{
	Motor1_Speed = Motor1_Speed_tmp;
	Motor2_Speed = Motor2_Speed_tmp;
}

void Motor_Set_Speed()
{
	if(Motor1_cnt>=Motor1_Speed && Motor1_cnt<30)
		MOTOR1_EN_L;
	else
		MOTOR1_EN_H;
	if(Motor2_cnt>=Motor2_Speed && Motor2_cnt<30)
		MOTOR2_EN_L;
	else
		MOTOR2_EN_H;

}
void Motor_GO(uint8_t Speed1,uint8_t Speed2)
{
	MOTOR1_IN1_H;
	MOTOR1_IN2_L;
	MOTOR2_IN1_H;
	MOTOR2_IN2_L;
	Motor_Speed(Speed1,Speed2);
}

void Motor_Left(uint8_t Speed1,uint8_t Speed2)
{
	MOTOR1_IN1_L;
	MOTOR1_IN2_H;
	MOTOR2_IN1_H;
	MOTOR2_IN2_L;
	Motor_Speed(Speed1,Speed2);
}

void Motor_Right(uint8_t Speed1,uint8_t Speed2)
{
	MOTOR1_IN1_H;
	MOTOR1_IN2_L;
	MOTOR2_IN1_L;
	MOTOR2_IN2_H;
	Motor_Speed(Speed1,Speed2);
}

void Motor_Back(uint8_t Speed1,uint8_t Speed2)
{
	MOTOR1_IN1_L;
	MOTOR1_IN2_H;
	MOTOR2_IN1_L;
	MOTOR2_IN2_H;
	Motor_Speed(Speed1,Speed2);
}


