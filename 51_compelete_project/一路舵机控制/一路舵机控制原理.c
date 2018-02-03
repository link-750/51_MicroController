#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit PWM=P2^0;

uint flag=0;
uint TH0_H,TL0_H,TH0_L,TL0_L;
void delay(uint z)
{
  uint x,y;
  for(x=z;x>0;x--)
     for(y=110;y>0;y--);
} 
void init()
{
	TMOD=0x01;
    TH0=0;
    TL0=0;
	EA=1;
    ET0=1;
	TR0=1;  
}

void duoji(int jd)
{
	TH0_H=(65536-500-(100*jd)/9)/256;  
   	TL0_H=(65536-500-(100*jd)/9)%256;

	TH0_L=(65536-19500+(100*jd)/9)/256;
	TL0_L=(65536-19500+(100*jd)/9)%256;
}
void main()
{

duoji(90) ;
 }

void T0_timer() interrupt 1
{ 	

   
 switch(flag)
 {
   case 0:TH0=TH0_H;TL0=TL0_H;PWM=1;break;
   default :TH0=TH0_L;TL0=TL0_L;PWM=0;flag=-1; break;
 }
  flag++;
}
