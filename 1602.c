#include<stc15.h>
#include<intrins.h>
#define LCD1602_DB P0
sbit LCD1602_RS=P3^2;   
sbit LCD1602_RW=P3^3;
sbit LCD1602_E=P3^4;
typedef unsigned char uint8;
typedef unsigned int uint16;
void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LCD1602_Wait()
{
	uint8 a;
	LCD1602_RS=0;
	LCD1602_RW=1;
	LCD1602_DB=0xFF;
	do
	{
		LCD1602_E=1;
		a=LCD1602_DB;
		LCD1602_E=0;
	}while(a&0x80);
}
void LCD1602_WriteData(uint8 dat)
{
	LCD1602_Wait();
	LCD1602_RW=0;
	LCD1602_RS=1;
	LCD1602_DB=dat;
	LCD1602_E=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	LCD1602_E=0;
}
void LCD1602_WriteCMD(uint8 cmd)
{
	LCD1602_Wait();
	LCD1602_RW=0;
	LCD1602_RS=0;
	LCD1602_DB=cmd;
	LCD1602_E=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	LCD1602_E=0;
}
void LCD1602_Clear()
{
	LCD1602_WriteCMD(0x01);
}
void LCD1602_SetLocation(uint8 x,uint8 y)
{
	uint8 temp;
	if(y==1)temp=0x40;
	else temp=0x00;
	temp+=x;
	LCD1602_WriteCMD(temp|0x80);
}
void LCD1602_AreaClear(uint8 x,uint8 y,uint8 len)
{
	LCD1602_SetLocation(x,y);
	while(len--)
	{
		LCD1602_WriteData(' ');
	}
}
void LCD1602_Show(uint8 x,uint8 y,uint8 *dat,uint8 len)
{
	LCD1602_SetLocation(x,y);
	while(len--)
	{
		LCD1602_WriteData(*dat++);
	}
}
void LCD1602_ShowNum(uint8 x,uint8 y,uint16 dat, uint8 len, uint8 lowlen)
{
	uint8 temp[10], i;
	if(lowlen == 0)
	{
		for(i = 0; i < len; i++)
		{
			temp[len - i - 1] = dat % 10 + '0';
			dat /= 10;
		}
		LCD1602_Show(x, y, temp, len);
	}
	else 
	{
		for(i = 0; i < lowlen; i++)
		{
			temp[len - i] = dat % 10 + '0';
			dat /= 10;
		}
		temp[len - lowlen] = '.';
		for(; i < len; i++)
		{
			temp[len - i - 1] = dat % 10 + '0';
			dat /= 10;
		}
		LCD1602_Show(x, y, temp, len + 1);
	}		
}
void LCD1602_Init()
{
	LCD1602_WriteCMD(0x38);
	Delay5ms();
	LCD1602_WriteCMD(0x38);
	Delay5ms();
	LCD1602_WriteCMD(0x38);
	Delay5ms();
	LCD1602_WriteCMD(0x38);
	LCD1602_WriteCMD(0x0C);
	LCD1602_WriteCMD(0x06);
	LCD1602_Clear();
}