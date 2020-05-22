#include "ILI9325.h"
#include "delay.h"
#include "math.h"
/**
*名称:启光2.4寸LCD驱动程序
*作者：陈冲
*时间：2018年10月
*版本：1.0
*更新：
*	   1.0：无
**/
#include "font.h"
#include "picture.h"
extern volatile uint32_t bit1;
void ILI9325_delay_us(uint32_t us)
{
	uint32_t i = 0;
	if(SysTick_Config(SystemCoreClock/1000000))
	{
		while(1);
	}
	for(i=0;i<us;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
}

void ILI9325_delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
}

void ILI9325_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//RD初始化
	ILI9325_RD_CLKCMD(ILI9325_RD_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = ILI9325_RD_PIN;
	GPIO_Init(ILI9325_RD_PORT,&GPIO_InitStruct);
	
	//RS初始化
	ILI9325_RS_CLKCMD(ILI9325_RS_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = ILI9325_RS_PIN;
	GPIO_Init(ILI9325_RS_PORT,&GPIO_InitStruct);
	
	//WR初始化
	ILI9325_WR_CLKCMD(ILI9325_WR_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = ILI9325_WR_PIN;
	GPIO_Init(ILI9325_WR_PORT,&GPIO_InitStruct);
	
	//BL初始化
	ILI9325_BL_CLKCMD(ILI9325_BL_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = ILI9325_BL_PIN;
	GPIO_Init(ILI9325_BL_PORT,&GPIO_InitStruct);
	ILI9325_BL_OFF;
	
	//CS初始化
	ILI9325_CS_CLKCMD(ILI9325_CS_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = ILI9325_CS_PIN;
	GPIO_Init(ILI9325_CS_PORT,&GPIO_InitStruct);
	ILI9325_CS_H;
	
	//RESET初始化
	ILI9325_RESET_CLKCMD(ILI9325_RESET_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = ILI9325_RESET_PIN;
	GPIO_Init(ILI9325_RESET_PORT,&GPIO_InitStruct);
	ILI9325_RESET_H;
	
	//PB初始化，关闭JTAG仿真
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	  //启动AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	ILI9325_DATA_CLKCMD(ILI9325_DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_Init(ILI9325_DATA_PORT,&GPIO_InitStruct);
	
}

void ILI9325_Reset()
{
	ILI9325_RESET_H;
	ILI9325_delay_ms(5);
	ILI9325_RESET_L;
	ILI9325_delay_ms(5);
	ILI9325_RESET_H;
}
void ILI9325_DATA_Mode(uint16_t data_mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	ILI9325_DATA_CLKCMD(ILI9325_DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = ILI9325_DATA_PIN;
	if(data_mode == GPIO_Mode_Out_PP)
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	else
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ILI9325_DATA_PORT,&GPIO_InitStruct);
}
void ILI9325_Write_Com(uint16_t command)
{
	ILI9325_RS_L;						//索引
	//写索引
	GPIO_Write(ILI9325_DATA_PORT,command);
	ILI9325_WR_L;						//写使能低	
	ILI9325_WR_H;						//写使能高	

}
void ILI9325_Write_Data(uint16_t data)
{
	ILI9325_RS_H;						//数据					
	GPIO_Write(ILI9325_DATA_PORT,data);
	ILI9325_WR_L;						//写使能低
	ILI9325_WR_H; 
}
void ILI9325_Write_Rigister(uint16_t regisiter,uint16_t data)
{
	ILI9325_Write_Com(regisiter);
	ILI9325_Write_Data(data);	
}


uint16_t ILI9325_Read_Rigister(uint16_t regisiter)
{
	uint16_t data = 0;
	
	ILI9325_CS_L;						//片选信号低
	ILI9325_RD_H;						//读使能高
	ILI9325_RS_H;
	ILI9325_WR_H;
	//写索引
	ILI9325_DATA_Mode(MODE_OUT);
	GPIO_Write(ILI9325_DATA_PORT,regisiter);
	ILI9325_RS_L;						//写索引
	ILI9325_WR_L;						//写使能低
	
	//读数据
	ILI9325_RS_H;						//数据
	ILI9325_WR_H;
	ILI9325_DATA_Mode(MODE_IN);
	ILI9325_RD_L;
	data = GPIO_ReadInputData(ILI9325_DATA_PORT);
	ILI9325_RD_H;
	ILI9325_CS_H; 
	return data;
}

void ILI9325_Init()
{
	ILI9325_GPIO_Init();

	ILI9325_Reset();
	
	ILI9325_CS_H;
	ILI9325_RD_H;
	ILI9325_WR_H;
	ILI9325_delay_ms(5);
	ILI9325_CS_L;

    ILI9325_Write_Rigister(0x0001,0x0100);	//Driver Output Contral.	
    ILI9325_Write_Rigister(0x0002,0x0700);	//LCD Driver Waveform Contral.
	ILI9325_Write_Rigister(0x0003,0x1030);	//Entry Mode Set.
	ILI9325_Write_Rigister(0x0004,0x0000);	//Scalling Contral.			
	ILI9325_Write_Rigister(0x0008,0x0202);	//Display Contral 2.(0x0207)		
	ILI9325_Write_Rigister(0x0009,0x0000);	//Display Contral 3.(0x0000)
	ILI9325_Write_Rigister(0x000A,0x0000);	//Frame Cycle Contal.(0x0000)
	ILI9325_Write_Rigister(0x000C,0x0000);	
	ILI9325_Write_Rigister(0x000D,0x0000);	//Frame Maker Position.
	ILI9325_Write_Rigister(0x000F,0x0000);	//Extern Display Interface Contral 2.

	ILI9325_Write_Rigister(0x0010,0x0000);	
	ILI9325_Write_Rigister(0x0011,0x0007);								//Power Control 2.(0x0001)				    //Power Control 3.(0x0138)
	ILI9325_Write_Rigister(0x0012,0x0000);	
	ILI9325_Write_Rigister(0x0013,0x0000);								//Power Control 4.
	ILI9325_Write_Rigister(0x0007,0x0001);								//Power Control 7.
	ILI9325_delay_ms(50);

    ILI9325_Write_Rigister(0x0010,0x1690);
	ILI9325_Write_Rigister(0x0011,0x0227);
	ILI9325_delay_ms(50);
	ILI9325_Write_Rigister(0x0012,0x009D);
	ILI9325_delay_ms(50);
	ILI9325_Write_Rigister(0x0013,0x1900);	
	ILI9325_delay_ms(50);
	ILI9325_Write_Rigister(0x0029,0x0025);	
	ILI9325_Write_Rigister(0x002B,0x000D);
	ILI9325_delay_ms(50);
	ILI9325_Write_Rigister(0x0020,0x0000);	
	ILI9325_Write_Rigister(0x0021,0x0000);
	ILI9325_delay_ms(50);
	ILI9325_Write_Rigister(0x0030,0x0007);	
	ILI9325_Write_Rigister(0x0031,0x0303);	
	ILI9325_Write_Rigister(0x0032,0x0003);	
	ILI9325_Write_Rigister(0x0035,0x0206);	
	ILI9325_Write_Rigister(0x0036,0x0008);	
	ILI9325_Write_Rigister(0x0037,0x0406);	
	ILI9325_Write_Rigister(0x0038,0x0304);
	ILI9325_Write_Rigister(0x0039,0x0007);	
	ILI9325_Write_Rigister(0x003C,0x0601);	
	ILI9325_Write_Rigister(0x003D,0x0008);			
				

	ILI9325_Write_Rigister(0x0050,0x0000);	
	ILI9325_Write_Rigister(0x0051,0x00EF);	
	ILI9325_Write_Rigister(0x0052,0x0000);	
	ILI9325_Write_Rigister(0x0053,0x013F);	
	ILI9325_Write_Rigister(0x0060,0xA700);	
	ILI9325_Write_Rigister(0x0061,0x0001);	
	ILI9325_Write_Rigister(0x006A,0x0000);	


	ILI9325_Write_Rigister(0x0080,0x0000);	//Display Position? Partial Display 1.
	ILI9325_Write_Rigister(0x0081,0x0000);	//RAM Address Start? Partial Display 1.
	ILI9325_Write_Rigister(0x0082,0x0000);	//RAM Address End-Partial Display 1.
	ILI9325_Write_Rigister(0x0083,0x0000);	//Displsy Position? Partial Display 2.
	ILI9325_Write_Rigister(0x0084,0x0000);	//RAM Address Start? Partial Display 2.
	ILI9325_Write_Rigister(0x0085,0x0000);	//RAM Address End? Partial Display 2.

	ILI9325_Write_Rigister(0x0090,0x0010);	
	ILI9325_Write_Rigister(0x0092,0x0600);	//Panel Interface Contral 2.(0x0000)

	ILI9325_Write_Rigister(0x0007,0x0133);	//(0x0173)                   
	ILI9325_Write_Com(0x0022);
	
}



/*
*name:void ILI9325_SetWindowArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
*fun :设置显示区域函数
*para:（x1,y1)矩形的左上点的坐标 （x2,y2)矩形的右下点的坐标
*ret :void 
*/
void ILI9325_Set_Window_Area(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	ILI9325_Write_Rigister(0x0050,x1);
	ILI9325_Write_Rigister(0x0051,x2);
	ILI9325_Write_Rigister(0x0052,y1);
	ILI9325_Write_Rigister(0x0053,y2);
}

/*
*name:void ILI9325_SetPointer(uint16_t x,uint16_t y)
*fun :设置当前坐标
*para:(x,y)当前点的坐标
*ret :void
*/
void ILI9325_Set_Pointer(uint16_t x,uint16_t y)
{
	ILI9325_Write_Rigister(0x0020,x);
	ILI9325_Write_Rigister(0x0021,y);
}
void ILI9325_Set_Window(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	ILI9325_Set_Window_Area(x1,y1,x2,y2);
	ILI9325_Set_Pointer(x1,y1);
	ILI9325_Write_Com(0x0022);
}

void ILI9325_Print_Rectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	ILI9325_Set_Window_Area(x1,y1,x2,y2);
	ILI9325_Set_Pointer(x1,y1);
	ILI9325_Write_Com(0x0022);
	for(uint16_t i = y1;i<=y2;i++)
		for(uint16_t j = x1;j<=x2;j++)
			ILI9325_Write_Data(color);	
}

void ILI9325_Print_Dot(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9325_Set_Pointer(x,y);
	ILI9325_Write_Com(0x0022);
	ILI9325_Write_Data(color);
}

void ILI9325_Print_Letter(uint16_t x,uint16_t y,uint8_t num,uint8_t word_size,uint16_t color)
{
	uint8_t word_width = 16; 
	uint8_t word_width1= 11; 
	uint8_t word_hight = 21; 
	
	switch(word_size)
	{
		case 1: word_width = 16; word_width1= 12; word_hight = 24;break;
	}
	
	for(uint16_t m = 0;m<word_hight;m++)
	{

		for(uint8_t n = 0;n<word_width/8;n++)// 0~24
		for(uint8_t i = 0;i<8;i++)
		{
			if((letter[word_size][num-32][m*word_width/8+n]>>(7-i))&0x01 == 0x01)
			{
				if(n !=(word_width/8-1) || i<(8-(word_width - word_width1)+1)) 
					ILI9325_Print_Dot(x+n*7+i,y+m,color);
				
			}
			else 
			{//显示文字底色
				if(n !=(word_width/8-1) || i<(8-(word_width - word_width1)+1)) 
				ILI9325_Print_Dot(x+n*7+i,y+m,0xffff);
			}
		}
	}
			
}


void ILI9325_Print_ENString(uint16_t x,uint16_t y,char *str,uint8_t word_size,uint16_t color)
{
	uint8_t word_width1 = 11;
	switch(word_size)
	{
		case 1:word_width1= 12;break;
	}
	while(*str != '\0')
	{
		ILI9325_Print_Letter(x,y,*str,word_size,color);
		x+= word_width1;
		str++;
	}
}

void ILI9325_Print_CNWord(uint16_t x,uint16_t y,uint8_t num,uint16_t color)
{
	uint8_t word_width = 48; //圆整后的字宽
	uint8_t word_width1= 48; //未圆整的字宽
	uint8_t word_hight = 48; //字的高度
	
	for(uint16_t m = 0;m<word_hight;m++)
	{

		for(uint8_t n = 0;n<word_width/8;n++)// 0~24
		for(uint8_t i = 0;i<8;i++)
		{
			if((cn_word[num][m*word_width/8+n]>>(7-i))&0x01 == 0x01)
			{
				if(n !=(word_width/8-1) || i<(8-(word_width - word_width1)+1)) 
					ILI9325_Print_Dot(x+n*7+i,y+m,color);
				
			}
			else 
			{//显示文字底色
				if(n !=(word_width/8-1) || i<(8-(word_width - word_width1)+1)) 
				ILI9325_Print_Dot(x+n*7+i,y+m,0xffff);
			}
		}
	}
			
}

void ILI9325_Print_CNString(uint16_t x,uint16_t y,uint16_t color)
{
	uint8_t word_width = 48; //wei圆整后的字宽
	uint8_t word_width1= 48; //圆整的字宽
	uint8_t word_hight = 48; //字的高度
	uint8_t num = 0;
	while(num!= 5 )
	{
		for(uint16_t m = 0;m<word_hight;m++)
		{

			for(uint8_t n = 0;n<word_width/8;n++)// 0~24
			for(uint8_t i = 0;i<8;i++)
			{
				if((cn_word[num][m*word_width/8+n]>>(7-i))&0x01 == 0x01)
				{
					if(n !=(word_width/8-1) || i<(8-(word_width - word_width1))) 
						ILI9325_Print_Dot(x+n*7+i,y+m,color);
					
				}
				else 
				{//显示文字底色
					if(n !=(word_width/8-1) || i<(8-(word_width - word_width1))) 
					ILI9325_Print_Dot(x+n*7+i,y+m,0xffff);
				}
			}
		}
		x+=word_width1;
		num++;
		if(num%9 == 0)
		{
			y+=27;
			x=0;
		}
		
	}
}
/**
*name:void USART_x_Send_Float(USART_TypeDef* USARTx,float num)
*fun :送浮点数
*para:USARTx：串口号   num：数字
*ret :void
**/
void ILI9325_Print_Float(uint16_t x,uint16_t y,float num,uint8_t word_size,uint16_t color)
{
	//ILI9325_Print_Letter(uint16_t x,uint16_t y,uint8_t num,uint8_t word_size,uint16_t color)
	uint8_t word_width1 = 11;
	switch(word_size)
	{
		case 1:word_width1= 12;break;
	}
	float zero_dot_one = 0.1;
	//整数部分
	uint32_t temp = (uint32_t)num;
	if(num<0)
	{
		ILI9325_Print_Letter(x,y,'-',word_size,color);
		x+=word_width1;
	}
	uint8_t i = 0;
	uint8_t j = 0;
	if(temp != 0)
	{
		while(temp != 0)
		{
			temp/= 10;
			i++;
		}
		temp = (uint32_t)num;
		while(j<i)
		{
			ILI9325_Print_Letter(x,y,temp/(uint32_t)pow(10,i-j-1)%10+'0',word_size,color);
			x += word_width1;
			j++;
		}
	}
	else
	{
		ILI9325_Print_Letter(x,y,'0',word_size,color);
		x += word_width1;
	}
	//小数点
	ILI9325_Print_Letter(x,y,'.',word_size,color);
	x += word_width1;
	//小数部分
	float temp1 = num - (uint32_t)num;
	float temp2 = temp1;
	uint8_t zero_num = 6;//显示小数的个数
	i = 0;
	temp1 *= pow(10,zero_num);
	while(temp2 < zero_dot_one && i< zero_num )
	{
		ILI9325_Print_Letter(x,y,'0',word_size,color);
		x += word_width1;
		zero_dot_one/=10.0;
		i++;
	}
	temp = (uint32_t)temp1;
	i = 0;j = 0;
	while(temp != 0)
	{
		temp/= 10;
		i++;
	}
	temp = (uint32_t)temp1;
	while(j<i)
	{
		ILI9325_Print_Letter(x,y,temp/(uint32_t)pow(10,i-j-1)%10+'0',word_size,color);
		x += word_width1;
		j++;
	}

}
void ILI9325_Print_Picture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	ILI9325_Set_Window(x1,y1,x2,y2);
	for(uint32_t i = 0;i<153600/2;i++)
		ILI9325_Write_Data((gImage_image1[i*2+1]<<8)+(gImage_image1[i*2]));
	ILI9325_Print_Picture(0,0,239,319);
	for(uint32_t i = 0;i<153600/2;i++)
		ILI9325_Write_Data((gImage_image2[i*2+1]<<8)+(gImage_image2[i*2]));
	ILI9325_delay_ms(1500);
			ILI9325_Set_Window(x1,y1,x2,y2);
	for(uint32_t i = 0;i<153600/2;i++)
		ILI9325_Write_Data((gImage_image3[i*2+1]<<8)+(gImage_image3[i*2]));
	ILI9325_delay_ms(1500);
}


