#ifndef __DS1302_H__
#define __DS1302_H__
#define unchar unsigned char
void ds1302_write(unsigned char address,unsigned char Date);
unsigned char ds1302_read(unsigned char address);
void time_read();
void time_init(unchar year,unchar mon,unchar day,unchar h,unchar min,unchar s,unchar week);
extern unchar a[];
#endif