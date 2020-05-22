#ifndef _ILI9325_H
#define _ILI9325_H
/*头文件*/
#include "stm32f10x.h"


/*引脚定义*/
/*RD: PC0：读数据信号，低电平有效*/
#define ILI9325_RD_CLKCMD		RCC_APB2PeriphClockCmd
#define ILI9325_RD_CLK			RCC_APB2Periph_GPIOC
#define ILI9325_RD_PORT			GPIOC
#define ILI9325_RD_PIN			GPIO_Pin_0

/*WR: PC2：写数据信号，低电平有效*/
#define ILI9325_WR_CLKCMD		RCC_APB2PeriphClockCmd
#define ILI9325_WR_CLK			RCC_APB2Periph_GPIOC
#define ILI9325_WR_PORT			GPIOC
#define ILI9325_WR_PIN			GPIO_Pin_2

/*RS: PC6：数据/命令信号，高电平是数据（RGB像素数据，或是命令数据），低电平控制命令*/
#define ILI9325_RS_CLKCMD		RCC_APB2PeriphClockCmd
#define ILI9325_RS_CLK			RCC_APB2Periph_GPIOC
#define ILI9325_RS_PORT			GPIOC
#define ILI9325_RS_PIN			GPIO_Pin_4

/*CS: PC2：片选信号，低电平有效*/
#define ILI9325_CS_CLKCMD		RCC_APB2PeriphClockCmd
#define ILI9325_CS_CLK			RCC_APB2Periph_GPIOE
#define ILI9325_CS_PORT			GPIOE
#define ILI9325_CS_PIN			GPIO_Pin_0

/*BL： PE2：背光*/
#define ILI9325_BL_CLKCMD		RCC_APB2PeriphClockCmd
#define ILI9325_BL_CLK			RCC_APB2Periph_GPIOE
#define ILI9325_BL_PORT			GPIOE
#define ILI9325_BL_PIN			GPIO_Pin_2


/*RESET: PC2：复位引脚*/
#define ILI9325_RESET_CLKCMD	RCC_APB2PeriphClockCmd
#define ILI9325_RESET_CLK		RCC_APB2Periph_GPIOE
#define ILI9325_RESET_PORT		GPIOE
#define ILI9325_RESET_PIN		GPIO_Pin_4

/*DATA: PB:*/
#define ILI9325_DATA_CLKCMD		RCC_APB2PeriphClockCmd
#define ILI9325_DATA_CLK		RCC_APB2Periph_GPIOD
#define ILI9325_DATA_PORT		GPIOD
#define ILI9325_DATA_PIN		GPIO_Pin_All

#define USING_REGISTOR_MODE  1
/*使用库函数*/
#if USING_REGISTOR_MODE
#define ILI9325_RD_H			ILI9325_RD_PORT->BSRR |= ILI9325_RD_PIN
#define ILI9325_RD_L			ILI9325_RD_PORT->BRR  |= ILI9325_RD_PIN
#define ILI9325_WR_H			ILI9325_WR_PORT->BSRR |= ILI9325_WR_PIN
#define ILI9325_WR_L			ILI9325_WR_PORT->BRR  |= ILI9325_WR_PIN
#define ILI9325_RS_H			ILI9325_RS_PORT->BSRR |= ILI9325_RS_PIN
#define ILI9325_RS_L			ILI9325_RS_PORT->BRR  |= ILI9325_RS_PIN
#define ILI9325_CS_H			ILI9325_CS_PORT->BSRR |= ILI9325_CS_PIN
#define ILI9325_CS_L			ILI9325_CS_PORT->BRR  |= ILI9325_CS_PIN
#define ILI9325_BL_ON			ILI9325_BL_PORT->BSRR |= ILI9325_BL_PIN
#define ILI9325_BL_OFF			ILI9325_BL_PORT->BRR  |= ILI9325_BL_PIN
#define ILI9325_RESET_H			ILI9325_RESET_PORT->BSRR |= ILI9325_RESET_PIN
#define ILI9325_RESET_L			ILI9325_RESET_PORT->BRR  |= ILI9325_RESET_PIN
#define ILI9325_DATA			GPIO_ReadInputData(ILI9325_DATA_PORT)
/*使用寄存器*/
#else 
#define ILI9325_RD_H			GPIO_SetBits(ILI9325_RD_PORT,ILI9325_RD_PIN)
#define ILI9325_RD_L			GPIO_ResetBits(ILI9325_RD_PORT,ILI9325_RD_PIN)
#define ILI9325_WR_H			GPIO_SetBits(ILI9325_WR_PORT,ILI9325_WR_PIN)
#define ILI9325_WR_L			GPIO_ResetBits(ILI9325_WR_PORT,ILI9325_WR_PIN)
#define ILI9325_RS_H			GPIO_SetBits(ILI9325_RS_PORT,ILI9325_RS_PIN)
#define ILI9325_RS_L			GPIO_ResetBits(ILI9325_RS_PORT,ILI9325_RS_PIN)
#define ILI9325_CS_ON			GPIO_SetBits(ILI9325_CS_PORT,ILI9325_CS_PIN)
#define ILI9325_CS_OFF			GPIO_ResetBits(ILI9325_CS_PORT,ILI9325_CS_PIN)
#define ILI9325_BL_H			GPIO_SetBits(ILI9325_BL_PORT,ILI9325_BL_PIN)
#define ILI9325_BL_L			GPIO_ResetBits(ILI9325_BL_PORT,ILI9325_BL_PIN)
#define ILI9325_RESET_H			GPIO_SetBits(ILI9325_RESET_PORT,ILI9325_RESET_PIN)
#define ILI9325_RESET_L			GPIO_ResetBits(ILI9325_RESET_PORT,ILI9325_RESET_PIN)
#define ILI9325_DATA			GPIO_ReadInputData(ILI9325_DATA_PORT)
#endif




/*一些宏定义*/
//引脚模式
#define MODE_OUT				GPIO_Mode_Out_PP
#define MODE_IN					GPIO_Mode_IPU
//屏幕尺寸
#define ILI9325_XMAX       239
#define ILI9325_YMAX       319


/*函数定义*/
void ILI9325_Init(void);
void ILI9325_Print_Rectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void ILI9325_Print_Dot(uint16_t x,uint16_t y,uint16_t color);
void ILI9325_Print_Letter(uint16_t x,uint16_t y,uint8_t num,uint8_t word_size,uint16_t color);
void ILI9325_Print_Float(uint16_t x,uint16_t y,float num,uint8_t word_size,uint16_t color);
void ILI9325_Print_ENString(uint16_t x,uint16_t y,char *str,uint8_t word_size,uint16_t color);
void ILI9325_Print_CNString(uint16_t x,uint16_t y,uint16_t color);
void ILI9325_Print_Picture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void ILI9325_Clear(unsigned int bgcolor);



/*下面包含一些常用数字和字母的定义*/


#endif
