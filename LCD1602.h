#ifndef __LCD1602_H__
#define __LCD1602_H__

//�û����ú�����
//��ʼ��
void LCD_Init();
//��ʾ�ַ��磺LCD_ShowChar(1,1,'A')
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
//��ʾ�ַ����磺LCD_ShowString(1,3,"Hello");
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
//��ʾ�����磺LCD_ShowNum(1,9,123,3)
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
//��ʾ�з��������磺LCD_ShowSignedNum(1,13,-66,2)
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
//��ʾʮ��λ�������磺LCD_ShowHexNum(2,1,0xA8,2)
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
//��ʾ��λ�������磺LCD_ShowBinNum(2,4,0xAA,8)
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif