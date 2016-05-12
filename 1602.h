#ifndef _1602_H_
#define _1602_H_
void LCD1602_Clear();    //LCD1602清屏
void LCD1602_AreaClear(unsigned char x,unsigned char y,unsigned char len);   //LCD1602范围清屏（x：横坐标，y：纵坐标，len：清屏的字符数）
void LCD1602_Show(unsigned char x,unsigned char y,unsigned char *dat,unsigned char len); //LCD1602显示字符串（x：横坐标，y：纵坐标，dat：要显示的字符数组，len：要显示的长度）
void LCD1602_ShowNum(unsigned char x,unsigned char y,unsigned int dat, unsigned char len, unsigned char lowlen);
void LCD1602_Init(); //LCD1602初始化函数，在主函数开头调用。
void LCD1602_SetLocation(unsigned char x,unsigned char y);	//设置LCD1602光标位置
#endif