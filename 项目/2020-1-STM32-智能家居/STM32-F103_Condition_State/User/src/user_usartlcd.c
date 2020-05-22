#include "user_usartlcd.h"
#include <string.h>
/**
*名称：USARTLCD串口屏驱动函数
*作者：陈冲
*时间：2018年11月
*版本：1.0
*更新：1.0：无
**/

/**
*name:void USARTLCD_Init()
*fun :串口屏初始化函数，初始化为清屏白色
*para:void
*ret :void
**/
void USARTLCD_Init()
{
	USART_x_Init(USART_USARTLCD,9600);
//	USART_x_Send_String(USART_USARTLCD,"presbaud=115200\r\n");
//	USART_x_Init(USART_USARTLCD,19200);
	USART_x_Send_String(USART_USARTLCD,"cls 65535\r\n");
	USART_x_Send_String(USART_USARTLCD,"page ");
	USART_x_Send_Byte(USART_USARTLCD,(char)(MAIN+'0'));
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Cls(uint16_t color)
*fun :串口屏清屏函数
*para:颜色值
*ret :void
**/
void USARTLCD_Cls(uint16_t color)
{
	USART_x_Send_String(USART_USARTLCD,"cls ");
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Pic(uint16_t x,uint16_t y,uint8_t id)
*fun :显示图片
*para:x:坐标 y：坐标 id：图片的索引
*ret :void
**/
void USARTLCD_Pic(uint16_t x,uint16_t y,uint8_t id)
{
	USART_x_Send_String(USART_USARTLCD,"pic ");
	USART_x_Send_Num(USART_USARTLCD,x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Xpic
*fun :高级切图 	
*para:x_start：屏幕起始点x坐标| y_start：屏幕起始点y坐标 		|pic_width：区域宽度 
*			pic_hight：区域高度  		|picx_start：图片起始点x坐标 	|picy_start：图片起始点y坐标 |id：图片 ID 
*ret :void
**/
void USARTLCD_Xpic(uint16_t x_start,uint16_t y_start,uint16_t pic_width, uint16_t pic_hight,uint16_t picx_start,uint16_t picy_start,uint8_t id)
{
	USART_x_Send_String(USART_USARTLCD,"xpic ");
	USART_x_Send_Num(USART_USARTLCD,x_start);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,y_start);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,pic_width);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,pic_hight);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,picx_start);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,picy_start);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:USARTLCD_WriStr
*fun :USARTLCD写字符串函数
*para:x：起始点x坐标 																|y：起始点y坐标																	
*			width：区域宽度																| height：区域高度 
*			id：字库ID color：字体颜色 										|bg_color：背景色 
*			align：水平对齐方式（0左对称，1居中，2右对称）| alignV：垂直对齐方式（0上对齐，1居中，2下对齐）
*			bg_style：背景填充类型(0切图，1单色，2图片，3无背景，切图或者图片时bg_color是图片id）
*			*str 字符串内容
*ret :void
**/
void USARTLCD_WriStr(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,\
											 uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint8_t *str)
{
	USART_x_Send_String(USART_USARTLCD,"wristr ");
	USART_x_Send_Num(USART_USARTLCD,x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,width);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,height);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,bg_color);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,ailgn);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,align_V);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,bg_style);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Byte(USART_USARTLCD,'"');
	USART_x_Send_String(USART_USARTLCD,str);
	USART_x_Send_Byte(USART_USARTLCD,'"');
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_WriNum
*fun :USARTLCD写整数函数
*para:x：起始点x坐标 																|y：起始点y坐标																	
*			width：区域宽度																| height：区域高度 
*			id：字库ID color：字体颜色 										|bg_color：背景色 
*			align：水平对齐方式（0左对称，1居中，2右对称）| alignV：垂直对齐方式（0上对齐，1居中，2下对齐）
*			bg_style：背景填充类型(0切图，1单色，2图片，3无背景，切图或者图片时bg_color是图片id）
*			num:要显示的数字
*ret :void
**/
void USARTLCD_WriNum(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,\
											 uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,uint16_t num)
{
	USART_x_Send_String(USART_USARTLCD,"wristr ");
	USART_x_Send_Num(USART_USARTLCD,x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,width);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,height);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,bg_color);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,ailgn);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,align_V);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,bg_style);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Byte(USART_USARTLCD,'"');
	USART_x_Send_Num(USART_USARTLCD,num);
	USART_x_Send_Byte(USART_USARTLCD,'"');
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_WriFlo
*fun :USARTLCD写浮点数函数
*para:x：起始点x坐标 																|y：起始点y坐标																	
*			width：区域宽度																| height：区域高度 
*			id：字库ID color：字体颜色 										|bg_color：背景色 
*			align：水平对齐方式（0左对称，1居中，2右对称）| alignV：垂直对齐方式（0上对齐，1居中，2下对齐）
*			bg_style：背景填充类型(0切图，1单色，2图片，3无背景，切图或者图片时bg_color是图片id）
*			num:要显示的数字
*ret :void
**/
void USARTLCD_WriFlo(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t id,uint16_t color,\
											 uint16_t bg_color,uint8_t ailgn,uint8_t align_V,uint8_t bg_style,float num)
{
	USART_x_Send_String(USART_USARTLCD,"wristr ");
	USART_x_Send_Num(USART_USARTLCD,x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,width);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,height);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,bg_color);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,ailgn);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,align_V);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,bg_style);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Byte(USART_USARTLCD,'"');
	USART_x_Send_Float(USART_USARTLCD,num);
	USART_x_Send_Byte(USART_USARTLCD,'"');
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Fill
*fun :填充区域函数
*para:x：起始x	|y：起始y|width：宽度|height：高度|color：颜色
*ret :void
**/
void USARTLCD_Fill(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color)
{
	USART_x_Send_String(USART_USARTLCD,"fill ");
	USART_x_Send_Num(USART_USARTLCD,x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,width);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,height);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Line
*fun :划线函数
*para:start_x：起始x	|start_y：起始y|end_x：终点x	|end_y：终点y|color：颜色
*ret :void
**/
void USARTLCD_Line(uint16_t start_x,uint16_t strat_y,uint16_t end_x,uint16_t end_y,uint16_t color)
{
	USART_x_Send_String(USART_USARTLCD,"line ");
	USART_x_Send_Num(USART_USARTLCD,start_x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,strat_y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,end_x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,end_y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Drawrec
*fun :画空心矩形
*para:start_x：起始x	|start_y：起始y|end_x：终点x	|end_y：终点y|color：颜色
*ret :void
**/
void USARTLCD_Drawrec(uint16_t start_x,uint16_t strat_y,uint16_t end_x,uint16_t end_y,uint16_t color)
{
	USART_x_Send_String(USART_USARTLCD,"draw ");
	USART_x_Send_Num(USART_USARTLCD,start_x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,strat_y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,end_x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,end_y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Cir
*fun :画空心圆
*para:cercle_x：圆点x	|cercle_y：圆点y|rayon：半径	|end_y：终点y|color：颜色
*ret :void
**/
void USARTLCD_Cir(uint16_t cercle_x,uint16_t cercle_y,uint16_t rayon,uint16_t color,uint8_t fill)
{
	fill == 1? USART_x_Send_String(USART_USARTLCD,"cir "):USART_x_Send_String(USART_USARTLCD,"solcir ");
	USART_x_Send_Num(USART_USARTLCD,cercle_x);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,cercle_y);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,rayon);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,color);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Pag
*fun :刷新页面
*para:page:页面 ID 或页面名称实例
*ret :void
**/
void USARTLCD_Page(uint8_t page)
{
	USART_x_Send_String(USART_USARTLCD,"page ");
	if(page == MAIN)
		USART_x_Send_String(USART_USARTLCD,"main");
	else
		USART_x_Send_Num(USART_USARTLCD,page);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Ref(uint8_t id)
*fun :重绘控件 
*para:id:控件 ID 或控件名称实例
*ret :void
**/
void USARTLCD_Ref(uint8_t id)
{
	USART_x_Send_String(USART_USARTLCD,"ref ");
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_Click
*fun :按下/弹起事件 
*para:str:控件名称 condition：事件类型，0 为弹起，1 为按下 
*ret :void
**/
void USARTLCD_Click(uint8_t *str,uint8_t condition)
{
	USART_x_Send_String(USART_USARTLCD,"click ");
	USART_x_Send_String(USART_USARTLCD,str);
	USART_x_Send_Byte(USART_USARTLCD,',');
	USART_x_Send_Num(USART_USARTLCD,condition);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_SetVal
*fun :设置控件的val值
*para:name:控件名称 val：数值
*ret :void
**/
void USARTLCD_SetVal(uint8_t *name,uint16_t val)
{
	USART_x_Send_String(USART_USARTLCD,name);
	USART_x_Send_String(USART_USARTLCD,".val");
	USART_x_Send_Byte(USART_USARTLCD,'=');
	USART_x_Send_Num(USART_USARTLCD,val);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_SetVal
*fun :设置控件的val值
*para:name:控件名称 val：数值
*ret :void
**/
void USARTLCD_SetFlo(uint8_t *name,float val)
{
	USART_x_Send_String(USART_USARTLCD,name);
	USART_x_Send_Byte(USART_USARTLCD,'=');
	USART_x_Send_String(USART_USARTLCD,"\"");
	USART_x_Send_Float(USART_USARTLCD,val);
	USART_x_Send_String(USART_USARTLCD,"\"");
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}
/**
*name:void USARTLCD_SetVal
*fun :设置控件的val值
*para:name:控件名称 val：数值
*ret :void
**/
void USARTLCD_SetStr(uint8_t *name,uint8_t * str)
{
	USART_x_Send_String(USART_USARTLCD,name);
	USART_x_Send_Byte(USART_USARTLCD,'=');
	USART_x_Send_String(USART_USARTLCD,"\"");
	USART_x_Send_String(USART_USARTLCD,str);
	USART_x_Send_String(USART_USARTLCD,"\"");
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}

/**
*name:void USARTLCD_Vis
*fun :显示或隐藏构件
*para:name:控件名称 
*ret :void
**/
void USARTLCD_Vis(uint8_t *name ,uint8_t condition)
{
	USART_x_Send_String(USART_USARTLCD,"vis ");
	USART_x_Send_String(USART_USARTLCD,name);
	USART_x_Send_String(USART_USARTLCD,",");
	if(condition ==0)
		USART_x_Send_String(USART_USARTLCD,"0");
	else
		USART_x_Send_String(USART_USARTLCD,"1");
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}

void USARTLCD_Curve(uint8_t id,uint8_t channel,uint16_t data)
{
	USART_x_Send_String(USART_USARTLCD,"add ");
	USART_x_Send_Num(USART_USARTLCD,id);
	USART_x_Send_String(USART_USARTLCD,",");
	USART_x_Send_Num(USART_USARTLCD,channel);
	USART_x_Send_String(USART_USARTLCD,",");
	USART_x_Send_Num(USART_USARTLCD,data);
	USART_x_Send_String(USART_USARTLCD,"\r\n");
}


uint8_t USARTLCD_DisposeData(uint8_t *data)
{
	return 0;
}
/*
串口屏数据处理
#include "user_usartlcd.h"
#include "user_dc_moto.h"
uint8_t usart_1_receive_data[50];			//接受数据缓冲数组
uint8_t datapoint = 0;								//接受数据的个数
uint8_t Usartlcd_flag = 0;						//接受信息的种类 1：速度控制。
void USARLCD_IRQHandler()
{
	if(USART_GetITStatus(USART_USARTLCD,USART_IT_RXNE) != RESET)
	{
		usart_1_receive_data[datapoint] = USART_ReceiveData(USART_USARTLCD);
		if(usart_1_receive_data[datapoint] == 0x0a)  //先判断是不是接收到了组后一个字符
		{
			if(usart_1_receive_data[datapoint-1] == 0x0d) //判断接受的倒数第二个字符
			{
				usart_1_receive_data[datapoint+1] = '\0';  // 结束数组
				Usartlcd_flag = USARTLCD_DisposeData(usart_1_receive_data); //处理消息类型
				
				/处理消息内容
				if(Usartlcd_flag == 1) //说明是控制速度信号
				{
					
				}
				for(uint8_t i = 0;i<datapoint+1;i++)			//清空数组
				{
					usart_1_receive_data[i] = 0x00;
				}
				datapoint = 55;
			}
		}
		if(datapoint == 55) 		//防止不从零开始
			datapoint = 0;
		else
			datapoint++;
		if(datapoint==49)
		{
			datapoint = 0;
		}
		
		USART_ClearFlag(USART_USARTLCD,USART_FLAG_RXNE);
	}
}
*/

