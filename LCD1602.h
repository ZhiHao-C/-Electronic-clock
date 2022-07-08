#ifndef __LCD1602_H__
#define __LCD1602_H__

//用户调用函数：
//初始化
void LCD_Init();
//显示字符如：LCD_ShowChar(1,1,'A')
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
//显示字符串如：LCD_ShowString(1,3,"Hello");
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
//显示数字如：LCD_ShowNum(1,9,123,3)
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
//显示有符号数字如：LCD_ShowSignedNum(1,13,-66,2)
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
//显示十六位进制数如：LCD_ShowHexNum(2,1,0xA8,2)
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
//显示二位进制数如：LCD_ShowBinNum(2,4,0xAA,8)
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif