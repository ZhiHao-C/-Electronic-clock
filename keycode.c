#include <REGX52.H>
#include "delay.h"
unsigned char key()
{
	unsigned char num=0;
	if(P3_0==0)
	{
		delay_ms(5);
		if(P3_0==0)
		{
			num=2;
			while(P3_0==0);
			delay_ms(5);
		}
	}
	else if(P3_1==0)
	{
		delay_ms(5);
		if(P3_1==0)
		{
			num=1;
			while(P3_1==0);
			delay_ms(5);
		}
	}
	else if(P3_2==0)
	{
		delay_ms(5);
		if(P3_2==0)
		{
			num=3;
			while(P3_2==0);
			delay_ms(5);
		}
	}
	else if(P3_3==0)
	{
		delay_ms(5);
		if(P3_3==0)
		{
			num=4;
			while(P3_3==0);
			delay_ms(5);
		}
	}
	return num;
}