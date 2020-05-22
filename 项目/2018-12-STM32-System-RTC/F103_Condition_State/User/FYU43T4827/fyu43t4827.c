#include "fyu43t4827.h"
/**
*名称：FYU43T4827串口屏驱动函数
*作者：陈冲
*时间：2018年11月
*版本：1.0
*更新：1.0：无
**/
/**
*name:void FYU43T4827_Init()
*fun :串口屏初始化函数，初始化为清屏白色
*para:void
*ret :void
**/
void FYU43T4827_Init()
{
	USART_x_Init(USART_FYU43T4827);
	USART_x_Send_String(USART_FYU43T4827,"cls 65535\r\n");
}
/**
*name:void FYU43T4827_Cls(uint16_t color)
*fun :串口屏清屏函数
*para:颜色值
*ret :void
**/
void FYU43T4827_Cls(uint16_t color)
{
	USART_x_Send_String(USART_FYU43T4827,"cls ");
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Pic(uint16_t x,uint16_t y,uint8_t id)
*fun :显示图片
*para:x:坐标 y：坐标 id：图片的索引
*ret :void
**/
void FYU43T4827_Pic(uint16_t x,uint16_t y,uint8_t id)
{
	USART_x_Send_String(USART_FYU43T4827,"pic ");
	USART_x_Send_Num(USART_FYU43T4827,x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,id);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Xpic
*fun :高级切图 	
*para:x_start：屏幕起始点x坐标| y_start：屏幕起始点y坐标 		|pic_width：区域宽度 
*			pic_hight：区域高度  		|picx_start：图片起始点x坐标 	|picy_start：图片起始点y坐标 |id：图片 ID 
*ret :void
**/
void FYU43T4827_Xpic(uint16_t x_start,uint16_t y_start,uint16_t pic_width, uint16_t pic_hight,uint16_t picx_start,uint16_t picy_start,uint8_t id)
{
	USART_x_Send_String(USART_FYU43T4827,"xpic ");
	USART_x_Send_Num(USART_FYU43T4827,x_start);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,y_start);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,pic_width);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,pic_hight);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,picx_start);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,picy_start);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,id);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:FYU43T4827_WriStr
*fun :FYU43T4827写字符串函数
*para:x：起始点x坐标 																|y：起始点y坐标																	
*			width：区域宽度																| height：区域高度 
*			id：字库ID color：字体颜色 										|bg_color：背景色 
*			align：水平对齐方式（0左对称，1居中，2右对称）| alignV：垂直对齐方式（0上对齐，1居中，2下对齐）
*			bg_style：背景填充类型(0切图，1单色，2图片，3无背景，切图或者图片时bg_color是图片id）
*			*str 字符串内容
*ret :void
**/
void FYU43T4827_WriStr(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,\
											 uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint8_t *str)
{
	USART_x_Send_String(USART_FYU43T4827,"wristr ");
	USART_x_Send_Num(USART_FYU43T4827,x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,width);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,height);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,id);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,bg_color);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,ailgn);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,align_V);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,bg_style);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Byte(USART_FYU43T4827,'"');
	USART_x_Send_String(USART_FYU43T4827,str);
	USART_x_Send_Byte(USART_FYU43T4827,'"');
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_WriNum
*fun :FYU43T4827写整数函数
*para:x：起始点x坐标 																|y：起始点y坐标																	
*			width：区域宽度																| height：区域高度 
*			id：字库ID color：字体颜色 										|bg_color：背景色 
*			align：水平对齐方式（0左对称，1居中，2右对称）| alignV：垂直对齐方式（0上对齐，1居中，2下对齐）
*			bg_style：背景填充类型(0切图，1单色，2图片，3无背景，切图或者图片时bg_color是图片id）
*			num:要显示的数字
*ret :void
**/
void FYU43T4827_WriNum(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,\
											 uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint32_t num)
{
	USART_x_Send_String(USART_FYU43T4827,"wristr ");
	USART_x_Send_Num(USART_FYU43T4827,x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,width);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,height);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,id);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,bg_color);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,ailgn);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,align_V);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,bg_style);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Byte(USART_FYU43T4827,'"');
	USART_x_Send_Num(USART_FYU43T4827,num);
	USART_x_Send_Byte(USART_FYU43T4827,'"');
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_WriFlo
*fun :FYU43T4827写浮点数函数
*para:x：起始点x坐标 																|y：起始点y坐标																	
*			width：区域宽度																| height：区域高度 
*			id：字库ID color：字体颜色 										|bg_color：背景色 
*			align：水平对齐方式（0左对称，1居中，2右对称）| alignV：垂直对齐方式（0上对齐，1居中，2下对齐）
*			bg_style：背景填充类型(0切图，1单色，2图片，3无背景，切图或者图片时bg_color是图片id）
*			num:要显示的数字
*ret :void
**/
void FYU43T4827_WriFlo(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,\
											 uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,float num)
{
	USART_x_Send_String(USART_FYU43T4827,"wristr ");
	USART_x_Send_Num(USART_FYU43T4827,x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,width);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,height);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,id);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,bg_color);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,ailgn);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,align_V);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,bg_style);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Byte(USART_FYU43T4827,'"');
	USART_x_Send_Float(USART_FYU43T4827,num);
	USART_x_Send_Byte(USART_FYU43T4827,'"');
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Fill
*fun :填充区域函数
*para:x：起始x	|y：起始y|width：宽度|height：高度|color：颜色
*ret :void
**/
void FYU43T4827_Fill(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color)
{
	USART_x_Send_String(USART_FYU43T4827,"fill ");
	USART_x_Send_Num(USART_FYU43T4827,x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,width);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,height);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Line
*fun :划线函数
*para:start_x：起始x	|start_y：起始y|end_x：终点x	|end_y：终点y|color：颜色
*ret :void
**/
void FYU43T4827_Line(uint16_t start_x,uint16_t strat_y,uint16_t end_x,uint16_t end_y,uint16_t color)
{
		USART_x_Send_String(USART_FYU43T4827,"line ");
	USART_x_Send_Num(USART_FYU43T4827,start_x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,strat_y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,end_x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,end_y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Drawrec
*fun :画空心矩形
*para:start_x：起始x	|start_y：起始y|end_x：终点x	|end_y：终点y|color：颜色
*ret :void
**/
void FYU43T4827_Drawrec(uint16_t start_x,uint16_t strat_y,uint16_t end_x,uint16_t end_y,uint16_t color)
{
	USART_x_Send_String(USART_FYU43T4827,"draw ");
	USART_x_Send_Num(USART_FYU43T4827,start_x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,strat_y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,end_x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,end_y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Cir
*fun :画空心圆
*para:cercle_x：圆点x	|cercle_y：圆点y|rayon：半径	|end_y：终点y|color：颜色
*ret :void
**/
void FYU43T4827_Cir(uint16_t cercle_x,uint16_t cercle_y,uint16_t rayon,uint16_t color,uint8_t fill)
{
	fill == 1? USART_x_Send_String(USART_FYU43T4827,"cir "):USART_x_Send_String(USART_FYU43T4827,"solcir ");
	USART_x_Send_Num(USART_FYU43T4827,cercle_x);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,cercle_y);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,rayon);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,color);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Pag
*fun :刷新页面
*para:page:页面 ID 或页面名称实例
*ret :void
**/
void FYU43T4827_Page(uint8_t page)
{
	USART_x_Send_String(USART_FYU43T4827,"page ");
	if(page == MAIN)
		USART_x_Send_String(USART_FYU43T4827,"main");
	else
		USART_x_Send_Num(USART_FYU43T4827,page);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Ref(uint8_t id)
*fun :重绘控件 
*para:id:控件 ID 或控件名称实例
*ret :void
**/
void FYU43T4827_Ref(uint8_t id)
{
	USART_x_Send_String(USART_FYU43T4827,"ref ");
	USART_x_Send_Num(USART_FYU43T4827,id);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_Click
*fun :按下/弹起事件 
*para:str:控件名称 condition：事件类型，0 为弹起，1 为按下 
*ret :void
**/
void FYU43T4827_Click(uint8_t *str,uint8_t condition)
{
	USART_x_Send_String(USART_FYU43T4827,"click ");
	USART_x_Send_String(USART_FYU43T4827,str);
	USART_x_Send_Byte(USART_FYU43T4827,',');
	USART_x_Send_Num(USART_FYU43T4827,condition);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
/**
*name:void FYU43T4827_SetVal
*fun :设置控件的val值
*para:name:控件名称 val：数值
*ret :void
**/
void FYU43T4827_SetVal(uint8_t *name,uint16_t val)
{
	USART_x_Send_String(USART_FYU43T4827,name);
	USART_x_Send_String(USART_FYU43T4827,".val");
	USART_x_Send_Byte(USART_FYU43T4827,'=');
	USART_x_Send_Num(USART_FYU43T4827,val);
	USART_x_Send_String(USART_FYU43T4827,"\r\n");
}
