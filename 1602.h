#ifndef _1602_H_
#define _1602_H_
void LCD1602_Clear();    //LCD1602����
void LCD1602_AreaClear(unsigned char x,unsigned char y,unsigned char len);   //LCD1602��Χ������x�������꣬y�������꣬len���������ַ�����
void LCD1602_Show(unsigned char x,unsigned char y,unsigned char *dat,unsigned char len); //LCD1602��ʾ�ַ�����x�������꣬y�������꣬dat��Ҫ��ʾ���ַ����飬len��Ҫ��ʾ�ĳ��ȣ�
void LCD1602_ShowNum(unsigned char x,unsigned char y,unsigned int dat, unsigned char len, unsigned char lowlen);
void LCD1602_Init(); //LCD1602��ʼ������������������ͷ���á�
void LCD1602_SetLocation(unsigned char x,unsigned char y);	//����LCD1602���λ��
#endif