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
void time_show()   //显示时间
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


void time_set()                   //设置时间函数
{
	if(keynum==2)                 //第二个按键按下
	{
		n++;                      //n作为选定数组里的第几个数，按一下相当于选中a【1】然后可更改和读取
		n=n%7;                    //当n为7时置零
	}
	if(keynum==3)                 //第三个按键按下为加
	{
		a[n]=a[n]+1;
		if(a[0]>99){a[0]=0;}
		if(a[1]>12){a[1]=1;}
		                          //下面为判断月份（分大月和小月，闰年）
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
	if(keynum==4)                       //第四个按键按下为减
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
	time_init(a[0],a[1],a[2],a[3],a[4],a[5],a[6]);    //将修改后的值再次写入ds1302，再从中读取出来
	if(n==0&&timemode==1){LCD_ShowString(1,1,"  ");}  //根据timemode值来显示空还是数据，再根据n的值选择第几位出现
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
	TMOD=0X01;      //定时器0 方式1
	TL0 = 0x00;		//设置定时初值50ms
	TH0 = 0x4C;
	EA=ET0=1;       //开关打开
	TR0=1;          //开始计时
	TF0=0;          //标志位清零
	time_init(22,7,7,20,36,55,4);// 设立初始值分别为年月日时分秒星期
	LCD_Init();     //屏幕初始化
	while(1)
	{
		
		keynum= key();  //读取按键值判断哪个按键按下
		if(keynum==1)   //如果第一个按键按下mode取反一次
		{
			mode=!mode;
		}
		switch(mode)    //根据mode来选择是显示还是设置
		{
			case 0:time_show();break;
			case 1:time_set();break;
		}
	}
}

void timing()interrupt 1
{

	TL0 = 0x00;		//设置定时初值50ms
	TH0 = 0x4C;
	c++;
	if(c>=10)
	{
		c=0;
		timemode=!timemode;
	}
}
