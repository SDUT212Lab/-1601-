#ifndef _USER_USARTLCD_H
#define _USER_USARTLCD_H
/*head file*/
#include "stm32f10x.h"
#include "user_usart.h"

/*宏定义*/
#define USART_USARTLCD					USART_1
#define MAIN										0
#define USARLCD_IRQHandler			USART1_IRQHandler
/*funtion define*/
void USARTLCD_Init(void);
void USARTLCD_Cls(uint16_t color);
void USARTLCD_Pic(uint16_t x,uint16_t y,uint8_t id);
void USARTLCD_Xpic(uint16_t x_start,uint16_t y_start,uint16_t pic_width, uint16_t pic_hight,uint16_t picx_start,uint16_t picy_start,uint8_t id);
void USARTLCD_WriStr(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint8_t *str);
void USARTLCD_WriNum(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color, uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint16_t num);
void USARTLCD_WriFlo(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,float num);
void USARTLCD_Fill(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color);
void USARTLCD_Line(uint16_t start_x,uint16_t strat_y,uint16_t end_x,uint16_t end_y,uint16_t color);
void USARTLCD_Cir(uint16_t cercle_x,uint16_t cercle_y,uint16_t rayon,uint16_t color,uint8_t fill);
void USARTLCD_Page(uint8_t page);
void USARTLCD_Ref(uint8_t id);
void USARTLCD_Click(uint8_t *str,uint8_t condition);
void USARTLCD_SetVal(uint8_t *name,uint16_t val);
void USARTLCD_SetFlo(uint8_t *name,float val);
void USARTLCD_SetStr(uint8_t *name,uint8_t * str);
void USARTLCD_Vis(uint8_t *name ,uint8_t condition);
void USARTLCD_Curve(uint8_t id,uint8_t channel,uint16_t data);
uint8_t USARTLCD_DisposeData(uint8_t *data);

#endif

