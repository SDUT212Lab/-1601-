#include "fyu43t4827.h"
/**
*���ƣ�FYU43T4827��������������
*���ߣ��³�
*ʱ�䣺2018��11��
*�汾��1.0
*���£�1.0����
**/
/**
*name:void FYU43T4827_Init()
*fun :��������ʼ����������ʼ��Ϊ������ɫ
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
*fun :��������������
*para:��ɫֵ
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
*fun :��ʾͼƬ
*para:x:���� y������ id��ͼƬ������
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
*fun :�߼���ͼ 	
*para:x_start����Ļ��ʼ��x����| y_start����Ļ��ʼ��y���� 		|pic_width�������� 
*			pic_hight������߶�  		|picx_start��ͼƬ��ʼ��x���� 	|picy_start��ͼƬ��ʼ��y���� |id��ͼƬ ID 
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
*fun :FYU43T4827д�ַ�������
*para:x����ʼ��x���� 																|y����ʼ��y����																	
*			width��������																| height������߶� 
*			id���ֿ�ID color��������ɫ 										|bg_color������ɫ 
*			align��ˮƽ���뷽ʽ��0��Գƣ�1���У�2�ҶԳƣ�| alignV����ֱ���뷽ʽ��0�϶��룬1���У�2�¶��룩
*			bg_style�������������(0��ͼ��1��ɫ��2ͼƬ��3�ޱ�������ͼ����ͼƬʱbg_color��ͼƬid��
*			*str �ַ�������
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
*fun :FYU43T4827д��������
*para:x����ʼ��x���� 																|y����ʼ��y����																	
*			width��������																| height������߶� 
*			id���ֿ�ID color��������ɫ 										|bg_color������ɫ 
*			align��ˮƽ���뷽ʽ��0��Գƣ�1���У�2�ҶԳƣ�| alignV����ֱ���뷽ʽ��0�϶��룬1���У�2�¶��룩
*			bg_style�������������(0��ͼ��1��ɫ��2ͼƬ��3�ޱ�������ͼ����ͼƬʱbg_color��ͼƬid��
*			num:Ҫ��ʾ������
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
*fun :FYU43T4827д����������
*para:x����ʼ��x���� 																|y����ʼ��y����																	
*			width��������																| height������߶� 
*			id���ֿ�ID color��������ɫ 										|bg_color������ɫ 
*			align��ˮƽ���뷽ʽ��0��Գƣ�1���У�2�ҶԳƣ�| alignV����ֱ���뷽ʽ��0�϶��룬1���У�2�¶��룩
*			bg_style�������������(0��ͼ��1��ɫ��2ͼƬ��3�ޱ�������ͼ����ͼƬʱbg_color��ͼƬid��
*			num:Ҫ��ʾ������
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
*fun :���������
*para:x����ʼx	|y����ʼy|width�����|height���߶�|color����ɫ
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
*fun :���ߺ���
*para:start_x����ʼx	|start_y����ʼy|end_x���յ�x	|end_y���յ�y|color����ɫ
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
*fun :�����ľ���
*para:start_x����ʼx	|start_y����ʼy|end_x���յ�x	|end_y���յ�y|color����ɫ
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
*fun :������Բ
*para:cercle_x��Բ��x	|cercle_y��Բ��y|rayon���뾶	|end_y���յ�y|color����ɫ
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
*fun :ˢ��ҳ��
*para:page:ҳ�� ID ��ҳ������ʵ��
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
*fun :�ػ�ؼ� 
*para:id:�ؼ� ID ��ؼ�����ʵ��
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
*fun :����/�����¼� 
*para:str:�ؼ����� condition���¼����ͣ�0 Ϊ����1 Ϊ���� 
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
*fun :���ÿؼ���valֵ
*para:name:�ؼ����� val����ֵ
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
