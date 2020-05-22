#ifndef _USER_SYSTEM_H
#define _USER_SYSTEM_H
/*头文件*/
#include "stm32f10x.h"
#include "user_delay.h"
#include "user_led.h"
#include "user_systick.h"
#include "user_usart.h"
#include "user_rtc.h"
#include "user_dc_moto.h"
#include "user_wave.h"
#include "user_usartlcd.h"
#include "user_step_moto.h"
#include "user_mpu6050.h"
#include "user_iic.h"
#include "user_duoji.h"
#include "user_general_tim.h"
#include "user_pidcalculate.h"
#include "user_gpio_interp.h"
#include "user_test.h"
#include "uw.h"

/*宏定义*/

#define FASHE_GPIO_CLKCMD		RCC_APB2PeriphClockCmd
#define FASHE_GPIO_CLK			RCC_APB2Periph_GPIOA
#define FASHE_GPIO_PORT			GPIOA
#define FASHE_GPIO_PIN			GPIO_Pin_4
#define FASHE_H							GPIO_SetBits(FASHE_GPIO_PORT,FASHE_GPIO_PIN)
#define FASHE_L							GPIO_ResetBits(FASHE_GPIO_PORT,FASHE_GPIO_PIN)

#define CHARGE_GPIO_CLKCMD	RCC_APB2PeriphClockCmd
#define CHARGE_GPIO_CLK			RCC_APB2Periph_GPIOA
#define CHARGE_GPIO_PORT		GPIOA
#define CHARGE_GPIO_PIN			GPIO_Pin_0
#define CHARGE_H						GPIO_SetBits(CHARGE_GPIO_PORT,CHARGE_GPIO_PIN)
#define CHARGE_L						GPIO_ResetBits(CHARGE_GPIO_PORT,CHARGE_GPIO_PIN)

#define CHARGE							FASHE_H;delay_ms(5);CHARGE_H
#define FASHE								CHARGE_L;delay_ms(5);FASHE_L
/*函数定义*/
void System_Init(void);
uint32_t Calculate_angle(uint32_t distance);
uint32_t Calculate_angle1(uint32_t distance);
#endif
