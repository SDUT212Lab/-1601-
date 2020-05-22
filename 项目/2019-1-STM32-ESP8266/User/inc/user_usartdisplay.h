#ifndef _USER_DISPLAY_H
#define _USER_DISPLAY_H
/*head file*/
#include "stm32f10x.h"
#include "user_usart.h"

/*宏定义*/
#define USART_FYU43T4827		USART_1
#define MAIN								256

/*funtion define*/
void FYU43T4827_Init(void);
void FYU43T4827_Cls(uint16_t color);
void FYU43T4827_Pic(uint16_t x,uint16_t y,uint8_t id);
void FYU43T4827_Xpic(uint16_t x_start,uint16_t y_start,uint16_t pic_width, uint16_t pic_hight,uint16_t picx_start,uint16_t picy_start,uint8_t id);
void FYU43T4827_WriStr(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint8_t *str);
void FYU43T4827_WriNum(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color, uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint32_t num);
void FYU43T4827_WriFlo(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,float num);
void FYU43T4827_Fill(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color);
void FYU43T4827_Line(uint16_t start_x,uint16_t strat_y,uint16_t end_x,uint16_t end_y,uint16_t color);
void FYU43T4827_Cir(uint16_t cercle_x,uint16_t cercle_y,uint16_t rayon,uint16_t color,uint8_t fill);
void FYU43T4827_Page(uint8_t page);
void FYU43T4827_Ref(uint8_t id);
void FYU43T4827_Click(uint8_t *str,uint8_t condition);
void FYU43T4827_SetVal(uint8_t *name,uint16_t val);
void FYU43T4827_SetBK(uint8_t light);

#endif

