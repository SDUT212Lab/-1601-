#include "user_usartlcd.h"
#include <string.h>
/**
*���ƣ�USARTLCD��������������
*���ߣ��³�
*ʱ�䣺2018��11��
*�汾��1.0
*���£�1.0����
**/

/**
*name:void USARTLCD_Init()
*fun :��������ʼ����������ʼ��Ϊ������ɫ
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
*fun :��������������
*para:��ɫֵ
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
*fun :��ʾͼƬ
*para:x:���� y������ id��ͼƬ������
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
*fun :�߼���ͼ 	
*para:x_start����Ļ��ʼ��x����| y_start����Ļ��ʼ��y���� 		|pic_width�������� 
*			pic_hight������߶�  		|picx_start��ͼƬ��ʼ��x���� 	|picy_start��ͼƬ��ʼ��y���� |id��ͼƬ ID 
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
*fun :USARTLCDд�ַ�������
*para:x����ʼ��x���� 																|y����ʼ��y����																	
*			width��������																| height������߶� 
*			id���ֿ�ID color��������ɫ 										|bg_color������ɫ 
*			align��ˮƽ���뷽ʽ��0��Գƣ�1���У�2�ҶԳƣ�| alignV����ֱ���뷽ʽ��0�϶��룬1���У�2�¶��룩
*			bg_style�������������(0��ͼ��1��ɫ��2ͼƬ��3�ޱ�������ͼ����ͼƬʱbg_color��ͼƬid��
*			*str �ַ�������
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
*fun :USARTLCDд��������
*para:x����ʼ��x���� 																|y����ʼ��y����																	
*			width��������																| height������߶� 
*			id���ֿ�ID color��������ɫ 										|bg_color������ɫ 
*			align��ˮƽ���뷽ʽ��0��Գƣ�1���У�2�ҶԳƣ�| alignV����ֱ���뷽ʽ��0�϶��룬1���У�2�¶��룩
*			bg_style�������������(0��ͼ��1��ɫ��2ͼƬ��3�ޱ�������ͼ����ͼƬʱbg_color��ͼƬid��
*			num:Ҫ��ʾ������
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
*fun :USARTLCDд����������
*para:x����ʼ��x���� 																|y����ʼ��y����																	
*			width��������																| height������߶� 
*			id���ֿ�ID color��������ɫ 										|bg_color������ɫ 
*			align��ˮƽ���뷽ʽ��0��Գƣ�1���У�2�ҶԳƣ�| alignV����ֱ���뷽ʽ��0�϶��룬1���У�2�¶��룩
*			bg_style�������������(0��ͼ��1��ɫ��2ͼƬ��3�ޱ�������ͼ����ͼƬʱbg_color��ͼƬid��
*			num:Ҫ��ʾ������
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
*fun :���������
*para:x����ʼx	|y����ʼy|width�����|height���߶�|color����ɫ
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
*fun :���ߺ���
*para:start_x����ʼx	|start_y����ʼy|end_x���յ�x	|end_y���յ�y|color����ɫ
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
*fun :�����ľ���
*para:start_x����ʼx	|start_y����ʼy|end_x���յ�x	|end_y���յ�y|color����ɫ
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
*fun :������Բ
*para:cercle_x��Բ��x	|cercle_y��Բ��y|rayon���뾶	|end_y���յ�y|color����ɫ
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
*fun :ˢ��ҳ��
*para:page:ҳ�� ID ��ҳ������ʵ��
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
*fun :�ػ�ؼ� 
*para:id:�ؼ� ID ��ؼ�����ʵ��
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
*fun :����/�����¼� 
*para:str:�ؼ����� condition���¼����ͣ�0 Ϊ����1 Ϊ���� 
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
*fun :���ÿؼ���valֵ
*para:name:�ؼ����� val����ֵ
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
*fun :���ÿؼ���valֵ
*para:name:�ؼ����� val����ֵ
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
*fun :���ÿؼ���valֵ
*para:name:�ؼ����� val����ֵ
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
*fun :��ʾ�����ع���
*para:name:�ؼ����� 
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
���������ݴ���
#include "user_usartlcd.h"
#include "user_dc_moto.h"
uint8_t usart_1_receive_data[50];			//�������ݻ�������
uint8_t datapoint = 0;								//�������ݵĸ���
uint8_t Usartlcd_flag = 0;						//������Ϣ������ 1���ٶȿ��ơ�
void USARLCD_IRQHandler()
{
	if(USART_GetITStatus(USART_USARTLCD,USART_IT_RXNE) != RESET)
	{
		usart_1_receive_data[datapoint] = USART_ReceiveData(USART_USARTLCD);
		if(usart_1_receive_data[datapoint] == 0x0a)  //���ж��ǲ��ǽ��յ������һ���ַ�
		{
			if(usart_1_receive_data[datapoint-1] == 0x0d) //�жϽ��ܵĵ����ڶ����ַ�
			{
				usart_1_receive_data[datapoint+1] = '\0';  // ��������
				Usartlcd_flag = USARTLCD_DisposeData(usart_1_receive_data); //������Ϣ����
				
				/������Ϣ����
				if(Usartlcd_flag == 1) //˵���ǿ����ٶ��ź�
				{
					
				}
				for(uint8_t i = 0;i<datapoint+1;i++)			//�������
				{
					usart_1_receive_data[i] = 0x00;
				}
				datapoint = 55;
			}
		}
		if(datapoint == 55) 		//��ֹ�����㿪ʼ
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

