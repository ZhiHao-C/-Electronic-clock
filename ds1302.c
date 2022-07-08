#include <REGX52.H>
#include "delay.h"
sbit SCLK=P3^6;
sbit CE=P3^5;
sbit IO=P3^4;
#define unchar unsigned char

unchar a[7]={0,0,0,0,0,0,0};                              //������ų�ʼʱ����߶�ȡ��ʼʱ��


//ʵ�����ĸ���ַ��д����
void ds1302_write(unsigned char address,unsigned char Date)
{
	unsigned char i;
	CE=0;           //�൱���ܿ���ֻ����ceΪ1ʱ���ܹ���
	SCLK=0;
	CE=1;
	for(i=0;i<8;i++)
	{
		SCLK=0;    //����һ��������ds1302�ͻ��IO�ڶ���һλ��ַ����
		
		if((address&0x01)==1)//���δӵ�λ��ʼ��ȡ��ַ����
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
	
		for(i=0;i<8;i++)        //��ds1302д��Ҫ���õ�����
	{
		SCLK=0;                 //ͬΪ�����ض�ȡ
		
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

//����һ����ַ�ϵ�����
unsigned char ds1302_read(unsigned char address)
{
	unsigned char i;
	unsigned char Date=0x00;
	CE=0;
	SCLK=0;
	CE=1;
	for(i=0;i<8;i++)           //��ds1302д��Ҫ��ȡ���ݵĵ�ַ
	{
		SCLK=0;                //ͬΪ������
		
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

	for(i=0;i<8;i++)        //ds1302ͨ��IO�ڷ������ݣ�����date��ȡ
	{
		SCLK=1;             //�½�����Ч
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
//���ó�ʼʱ�� ������ʱ��������
void time_init(unchar year,unchar mon,unchar day,unchar h,unchar min,unchar s,unchar week)
{
	ds1302_write(0x8e,0x00);              //�ر�д����
	ds1302_write(0x8c,year/10*16+year%10);//ת��Ϊʮ������
	ds1302_write(0x88,mon/10*16+mon%10);
	ds1302_write(0x86,day/10*16+day%10);
	ds1302_write(0x84,h/10*16+h%10);
	ds1302_write(0x82,min/10*16+min%10);
	ds1302_write(0x80,s/10*16+s%10);
	ds1302_write(0x8a,week/10*16+week%10);
}
//��������ʱ�������ڵ�ַ�ϵ����ݶ�ȡ��a������������
void time_read()
{
	a[0]=ds1302_read(0x8d)/16*10+ds1302_read(0x8d)%16;//ת��Ϊʮ����
	a[1]=ds1302_read(0x89)/16*10+ds1302_read(0x89)%16;
	a[2]=ds1302_read(0x87)/16*10+ds1302_read(0x87)%16;
	a[3]=ds1302_read(0x85)/16*10+ds1302_read(0x85)%16;
	a[4]=ds1302_read(0x83)/16*10+ds1302_read(0x83)%16;
	a[5]=ds1302_read(0x81)/16*10+ds1302_read(0x81)%16;
	a[6]=ds1302_read(0x8b)/16*10+ds1302_read(0x8b)%16;
}