#ifndef _BSP_LED_H //���������Ļ��������ظ�����
#define _BSP_LED_H

#include "stm32f10x.h"
#include "SYSTICK.h"


/*
�궨��
*/

#define LED0 GPIO_Pin_0
#define LED1 GPIO_Pin_1
#define LED2 GPIO_Pin_2

#define LED_GPIO_CLK RCC_APB2Periph_GPIOB

							
/**
*��������
**/
void LED_Init(void); 								//LED�Ƴ�ʼ������
void LED(uint8_t LED,uint8_t condition);			//LED��������������LED�ı�ţ�LED��״̬�����ء���������ת��	
void LED_Wenkle(void);								//LED��˸����
void KEY_LED(void);									//����LED����
void JDQ_Init(void);
void System_Init(void);
void System_Recover(void);


#define JDQ_ON	GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define JDQ_OFF	GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#endif
