#include <REGX52.H>
#include "delay.h"
sbit SCLK=P3^6;
sbit CE=P3^5;
sbit IO=P3^4;
#define unchar unsigned char

unchar a[7]={0,0,0,0,0,0,0};                              //用来存放初始时间或者读取初始时间


//实现在哪个地址上写数据
void ds1302_write(unsigned char address,unsigned char Date)
{
	unsigned char i;
	CE=0;           //相当于总开关只有再ce为1时才能工作
	SCLK=0;
	CE=1;
	for(i=0;i<8;i++)
	{
		SCLK=0;    //当给一个上升沿ds1302就会从IO口读出一位地址数据
		
		if((address&0x01)==1)//依次从低位开始读取地址数据
		{
			IO=1;
		}
		else
		{
			IO=0;
		}
		SCLK=1;
		address=address>>1;
	}
	
		for(i=0;i<8;i++)        //给ds1302写入要设置的数据
	{
		SCLK=0;                 //同为上升沿读取
		
		if(Date&0x01==1)
		{
			IO=1;
		}
		else
		{
			IO=0;
		}
		SCLK=1;
		Date=Date>>1;
	}
	CE=0;
	SCLK=0;
}

//读出一个地址上的数据
unsigned char ds1302_read(unsigned char address)
{
	unsigned char i;
	unsigned char Date=0x00;
	CE=0;
	SCLK=0;
	CE=1;
	for(i=0;i<8;i++)           //给ds1302写入要读取数据的地址
	{
		SCLK=0;                //同为上升沿
		
		if(address&0x01==1)
		{
			IO=1;
		}
		else
		{
			IO=0;
		}
		SCLK=1;
		address=address>>1;
	}

	for(i=0;i<8;i++)        //ds1302通过IO口返回数据，先用date接取
	{
		SCLK=1;             //下降沿有效
		SCLK=0;
		if(IO==1)
		{
			Date=Date|(0x01<<i);
		}
//		else
//		{
//			Date=Date|(0x00<<i);
//		}
	}
	CE=0;
//	IO=0;
	return Date;
	
}
//设置初始时间 年月日时分秒星期
void time_init(unchar year,unchar mon,unchar day,unchar h,unchar min,unchar s,unchar week)
{
	ds1302_write(0x8e,0x00);              //关闭写保护
	ds1302_write(0x8c,year/10*16+year%10);//转化为十六进制
	ds1302_write(0x88,mon/10*16+mon%10);
	ds1302_write(0x86,day/10*16+day%10);
	ds1302_write(0x84,h/10*16+h%10);
	ds1302_write(0x82,min/10*16+min%10);
	ds1302_write(0x80,s/10*16+s%10);
	ds1302_write(0x8a,week/10*16+week%10);
}
//将年月日时分秒星期地址上的数据读取到a【】数组里面
void time_read()
{
	a[0]=ds1302_read(0x8d)/16*10+ds1302_read(0x8d)%16;//转化为十进制
	a[1]=ds1302_read(0x89)/16*10+ds1302_read(0x89)%16;
	a[2]=ds1302_read(0x87)/16*10+ds1302_read(0x87)%16;
	a[3]=ds1302_read(0x85)/16*10+ds1302_read(0x85)%16;
	a[4]=ds1302_read(0x83)/16*10+ds1302_read(0x83)%16;
	a[5]=ds1302_read(0x81)/16*10+ds1302_read(0x81)%16;
	a[6]=ds1302_read(0x8b)/16*10+ds1302_read(0x8b)%16;
}