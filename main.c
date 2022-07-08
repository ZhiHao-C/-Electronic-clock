#include <REGX52.H>
#include "ds1302.h"
#include "delay.h"
#include "LCD1602.h"
#include "keycode.h"
#define unchar unsigned char
unchar timemode=0;
unchar keynum;
unchar mode;
unchar n=0;
unchar c=0;
void time_show()   //��ʾʱ��
{
	LCD_ShowString(1,3,"-");
	LCD_ShowString(1,6,"-");
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,6,":");
	time_read();
	LCD_ShowNum(1,1,a[0],2);
	LCD_ShowNum(1,4,a[1],2);
	LCD_ShowNum(1,7,a[2],2);
	LCD_ShowNum(2,1,a[3],2);
	LCD_ShowNum(2,4,a[4],2);
	LCD_ShowNum(2,7,a[5],2);
	LCD_ShowNum(2,15,a[6],2);
	LCD_ShowString(2,10,"week:");
}


void time_set()                   //����ʱ�亯��
{
	if(keynum==2)                 //�ڶ�����������
	{
		n++;                      //n��Ϊѡ��������ĵڼ���������һ���൱��ѡ��a��1��Ȼ��ɸ��ĺͶ�ȡ
		n=n%7;                    //��nΪ7ʱ����
	}
	if(keynum==3)                 //��������������Ϊ��
	{
		a[n]=a[n]+1;
		if(a[0]>99){a[0]=0;}
		if(a[1]>12){a[1]=1;}
		                          //����Ϊ�ж��·ݣ��ִ��º�С�£����꣩
		if(a[1]==1 || a[1]==3 || a[1]==5 || a[1]==7 || a[1]==8 || a[1]==10 || a[1]==12)
		{
			if(a[2]>31){a[2]=1;}
		}
		else if(a[1]==4 || a[1]==6 || a[1]==9 || a[1]==11 )
		{
			if(a[2]>30){a[2]=1;}
		}
		else
		{
			if(a[0]%4==0||a[0]==0)
			{
				if(a[2]>29){a[2]=1;}
			}
			else
			{
				if(a[2]>28){a[2]=1;}
			}
		}
		if(a[3]>23){a[3]=0;}
		if(a[4]>59){a[4]=0;}
		if(a[5]>59){a[5]=0;}
		if(a[6]>7){a[6]=1;}
	}
	if(keynum==4)                       //���ĸ���������Ϊ��
	{
		a[n]=a[n]-1;
		if(a[0]>99){a[0]=99;}
		if(a[1]==0){a[1]=12;}
		if(a[1]==1 || a[1]==3 || a[1]==5 || a[1]==7 || a[1]==8 || a[1]==10 || a[1]==12)
		{
			if(a[2]==0){a[2]=31;}
		}
		else if(a[1]==4 || a[1]==6 || a[1]==9 || a[1]==11 )
		{
			if(a[2]==0){a[2]=30;}
			if(a[2]>30){a[2]=1;}
		}
		else
		{
			if(a[0]%4==0||a[0]==0)
			{
				if(a[2]==0){a[2]=29;}
				if(a[2]>29){a[2]=1;}
			}
			else
			{
				if(a[2]==0){a[2]=28;}
				if(a[2]>28){a[2]=1;} 
			}
		}
		if(a[3]>23){a[3]=23;}
		if(a[4]>59){a[4]=59;}
		if(a[5]>59){a[5]=59;}
		if(a[6]==0){a[6]=7;}
		
	}
//	LCD_ShowString(1,3,"-");
//	LCD_ShowString(1,6,"-");
//	LCD_ShowString(2,3,":");
//	LCD_ShowString(2,6,":");
//	time_read();
	time_init(a[0],a[1],a[2],a[3],a[4],a[5],a[6]);    //���޸ĺ��ֵ�ٴ�д��ds1302���ٴ��ж�ȡ����
	if(n==0&&timemode==1){LCD_ShowString(1,1,"  ");}  //����timemodeֵ����ʾ�ջ������ݣ��ٸ���n��ֵѡ��ڼ�λ����
	else {LCD_ShowNum(1,1,a[0],2);}
	if(n==1&&timemode==1){LCD_ShowString(1,4,"  ");}
	else {LCD_ShowNum(1,4,a[1],2);}
	if(n==2&&timemode==1){LCD_ShowString(1,7,"  ");}
	else {LCD_ShowNum(1,7,a[2],2);}
	if(n==3&&timemode==1){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,a[3],2);}
	if(n==4&&timemode==1){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,a[4],2);}
	if(n==5&&timemode==1){LCD_ShowString(2,7,"  ");}
	else {LCD_ShowNum(2,7,a[5],2);}
	if(n==6&&timemode==1){LCD_ShowString(2,15,"  ");}
	else {LCD_ShowNum(2,15,a[6],2);}
//	LCD_ShowNum(1,1,a[0],2);
//	LCD_ShowNum(1,4,a[1],2);
//	LCD_ShowNum(1,7,a[2],2);
//	LCD_ShowNum(2,1,a[3],2);
//	LCD_ShowNum(2,4,a[4],2);
//	LCD_ShowNum(2,7,a[5],2);
//	LCD_ShowNum(2,15,a[6],2);
//	LCD_ShowString(2,10,"week:");
	
}



void main()
{
	TMOD=0X01;      //��ʱ��0 ��ʽ1
	TL0 = 0x00;		//���ö�ʱ��ֵ50ms
	TH0 = 0x4C;
	EA=ET0=1;       //���ش�
	TR0=1;          //��ʼ��ʱ
	TF0=0;          //��־λ����
	time_init(22,7,7,20,36,55,4);// ������ʼֵ�ֱ�Ϊ������ʱ��������
	LCD_Init();     //��Ļ��ʼ��
	while(1)
	{
		
		keynum= key();  //��ȡ����ֵ�ж��ĸ���������
		if(keynum==1)   //�����һ����������modeȡ��һ��
		{
			mode=!mode;
		}
		switch(mode)    //����mode��ѡ������ʾ��������
		{
			case 0:time_show();break;
			case 1:time_set();break;
		}
	}
}

void timing()interrupt 1
{

	TL0 = 0x00;		//���ö�ʱ��ֵ50ms
	TH0 = 0x4C;
	c++;
	if(c>=10)
	{
		c=0;
		timemode=!timemode;
	}
}
