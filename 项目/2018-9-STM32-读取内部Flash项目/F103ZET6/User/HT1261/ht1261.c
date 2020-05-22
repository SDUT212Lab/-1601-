#include "ht1261.h"

char dispnum[6]={0x00,0x00,0x00,0x00,0x00,0x00};

	  
char num[]={
0x7D,0x60,0x3E,0x7A,0x63,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x4F,
/* 0,	1,	 2,	  3,   4,   5,   6,   7,   8,   9,   A,   b*/
0x1D,0x0E,0x6E,0x1F,0x17,0x67,0x47,0x0D,0x46,0x75,0x37,0x06,
/* C,	c,   d,   E,   F,   H,   h,   L,   n,   N,   o,   P*/
0x0F,0x6D,0x02,0x00,}; 
/* r,	t,   U,   -, ,*/	
void HT1261_delay_us(uint16_t us)
	
{
	for(int i=0;i<us;i++)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}
void HT1261_delay_ms(uint16_t ms)
{
	for(int i=0;i<ms;i++)
	{
		HT1261_delay_us(1000);
	}

}
void HT1261_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	DATA_CLKCMD(DATA_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = DATA_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DATA_PORT,&GPIO_InitStruct);
	
	WR_CLKCMD(WR_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = WR_PIN;
	GPIO_Init(WR_PORT,&GPIO_InitStruct);
	
	CS_CLKCMD(CS_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = CS_PIN;
	GPIO_Init(CS_PORT,&GPIO_InitStruct);
	CS_H;WR_H;DATA_H;
}

void HT1261_Write_Bit(uint8_t data,uint8_t cnt)
{
	for(int i=0;i<cnt;i++)
	{
		WR_L;
		HT1261_delay_us(20);
		if(data &0x80)
			DATA_H;
		else
			DATA_L;
		WR_H;
		HT1261_delay_us(20);
		data<<= 1;
		HT1261_delay_us(20);
	}
	HT1261_delay_us(20);
	
}

void HT1261_Write_Command(uint8_t command)
{
	CS_L;
	HT1261_Write_Bit(0x80,4);
	HT1261_Write_Bit(command,8);
	CS_H;
}

void HT1261_Write_Data(uint8_t addr,uint8_t data)
{
	addr<<=2;
	CS_L;
	HT1261_Write_Bit(0xa0,3);
	HT1261_Write_Bit(addr,6);
	HT1261_Write_Bit(data,8);
	CS_H;
}

void HT1261_All_Off(uint8_t num)
{
	uint8_t addr = 0;
	for(uint8_t i=0;i<num;i++)
	{
		HT1261_Write_Data(addr,0x00);
		addr+=2;
	}
}

void HT1261_All_On(uint8_t num)
{
	uint8_t addr = 0;
	for(uint8_t i=0;i<num;i++) 
	{ 
		HT1261_Write_Data(addr,0xff); 
		addr+=2; 
    } 
}

void HT1261_All_On_Num(uint8_t num,uint8_t xx)
{
	uint8_t addr =0;
	for(uint8_t i=0;i<num;i++)
	{
		HT1261_Write_Data(addr,xx);
		addr+=2;
	}
}

void HT1261_Init()
{
	HT1261_GPIO_Init();
	HT1261_Write_Command(0x02);
	HT1261_Write_Command(0x30);
	HT1261_Write_Command(0x52);
	HT1261_Write_Command(0x06);
}

void Ht1261_Off()
{
	HT1261_Write_Command(0x04);
}

void Ht1261_On()
{
	HT1261_Write_Command(0x06);
}


void HT1261_Write_Bihua() 
{ 
	HT1261_Write_Data(2,0x01);
	HT1261_delay_ms(350);
	HT1261_Write_Data(2,0x02);
	HT1261_delay_ms(350);
	HT1261_Write_Data(2,0x04);
	HT1261_delay_ms(350) ;
	HT1261_Write_Data(2,0x08);
	HT1261_delay_ms(350) ;
	HT1261_Write_Data(2,0x10);
	HT1261_delay_ms(350) ;
	HT1261_Write_Data(2,0x20);
	HT1261_delay_ms(350) ;
	HT1261_Write_Data(2,0x40);
	HT1261_delay_ms(350) ;
	HT1261_Write_Data(2,0x80);
	HT1261_delay_ms(350) ; 
}

void HT1261_Displayall8(void)
{
    HT1261_All_Off(6);
	for(uint8_t i=0;i<6;i++)
	{
		HT1261_Write_Data(2*i,0xff);
		HT1261_delay_ms(50) ;
	}
}

void HT1261_Display_Data(long int num1,int place,char bat1,char bat2,char bat3)//ÆÁÏÔÊ¾£¬bat1£¬bat2£¬bat3 ÓÒ²àµç³Ø
{
	uint8_t i;
	dispnum[5]=num[num1/100000];
	dispnum[4]=num[(num1/10000)%10];
	dispnum[3]=num[(num1/1000)%10];
	dispnum[2]=num[(num1/100)%10];
	dispnum[1]=num[(num1/10)%10];
	dispnum[0]=num[num1%10];
	switch(place)
	{
		case 1:sbi(dispnum[0], 7);break;
		case 2:sbi(dispnum[1], 7);break;
		case 3:sbi(dispnum[2], 7);break;
		default:break;
	}
	if(bat1==1)  sbi(dispnum[3], 7);
	if(bat2==1)  sbi(dispnum[4], 7);
	if(bat3==1)  sbi(dispnum[5], 7);

	for(i=0;i<6;i++) 
	{
		HT1261_Write_Data(i*2,dispnum[i]);
	}
}  
