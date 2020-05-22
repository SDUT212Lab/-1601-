#ifndef _USER_MOTOR_H
#define _USER_MOTOR_H

#include "stm32f10x.h"
#include "user_motor.h"

#define MOTOR_IN_CLKCMD						RCC_APB2PeriphClockCmd
#define MOTOR_IN_CLK							RCC_APB2Periph_GPIOA

#define MOTOR1_IN1_PORT						GPIOA
#define MOTOR1_IN1_PIN						GPIO_Pin_4
#define MOTOR1_IN1_H							GPIO_SetBits(MOTOR1_IN1_PORT,MOTOR1_IN1_PIN)
#define MOTOR1_IN1_L							GPIO_ResetBits(MOTOR1_IN1_PORT,MOTOR1_IN1_PIN)

#define MOTOR1_IN2_PORT						GPIOA
#define MOTOR1_IN2_PIN						GPIO_Pin_5
#define MOTOR1_IN2_H							GPIO_SetBits(MOTOR1_IN2_PORT,MOTOR1_IN2_PIN)
#define MOTOR1_IN2_L							GPIO_ResetBits(MOTOR1_IN2_PORT,MOTOR1_IN2_PIN)

#define MOTOR2_IN1_PORT						GPIOA
#define MOTOR2_IN1_PIN						GPIO_Pin_6
#define MOTOR2_IN1_H							GPIO_SetBits(MOTOR2_IN1_PORT,MOTOR2_IN1_PIN)
#define MOTOR2_IN1_L							GPIO_ResetBits(MOTOR2_IN1_PORT,MOTOR2_IN1_PIN)

#define MOTOR2_IN2_PORT						GPIOA
#define MOTOR2_IN2_PIN						GPIO_Pin_7
#define MOTOR2_IN2_H							GPIO_SetBits(MOTOR2_IN2_PORT,MOTOR2_IN2_PIN)
#define MOTOR2_IN2_L							GPIO_ResetBits(MOTOR2_IN2_PORT,MOTOR2_IN2_PIN)

#define MOTOR_EN_CLKCMD						RCC_APB2PeriphClockCmd
#define MOTOR_EN_CLK							RCC_APB2Periph_GPIOB

#define MOTOR1_EN_PORT						GPIOB
#define MOTOR1_EN_PIN							GPIO_Pin_0
#define MOTOR1_EN_H								GPIO_SetBits(MOTOR1_EN_PORT,MOTOR1_EN_PIN)
#define MOTOR1_EN_L								GPIO_ResetBits(MOTOR1_EN_PORT,MOTOR1_EN_PIN)

#define MOTOR2_EN_PORT						GPIOB
#define MOTOR2_EN_PIN							GPIO_Pin_1
#define MOTOR2_EN_H								GPIO_SetBits(MOTOR2_EN_PORT,MOTOR2_EN_PIN)
#define MOTOR2_EN_L								GPIO_ResetBits(MOTOR2_EN_PORT,MOTOR2_EN_PIN)

void Motor_Init(void);
void Motor_Set_Speed(void);
void Motor_GO(uint8_t Speed1,uint8_t Speed2);
void Motor_Left(uint8_t Speed1,uint8_t Speed2);
void Motor_Right(uint8_t Speed1,uint8_t Speed2);
void Motor_Back(uint8_t Speed1,uint8_t Speed2);


#endif
