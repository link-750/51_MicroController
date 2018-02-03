/******************************************************************************

          版权所有 (C), 2011-2012, 信意电子科技(http://xydz123.taobao.com/)

 ******************************************************************************
  文 件 名   : main.c
  版 本 号   : v1.0
  作    者   : Guokaiyi
  生成日期   : 2017-3-28
  最近修改   : 
  功能描述   : OLED演示例程(51系列)
               说明: 
               ----------------------------------------------------------------
               G    电源地
               VCC  接5V或3.3v电源
               D0   P1^0（SCLK）
               D1   P1^1（MOSI）
               RST  P1^2
               DC   P1^3
               CS   已经默认选中，可以不接                   
               ----------------------------------------------------------------
  修改历史   :
  1.日    期   : 2017-3-28
    作    者   :  刘伟，余昊川
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"
#include "oled.h"
#include "flash.h"

VOID MAIN_Init(VOID); //初始化函数
VOID MAIN_OLED_Display(VOID); //OLED显示函数
VOID MAIN_TIME_Delay(USHORT16 usTime); //延时函数
void display_init();
void timer_init();//定时器初始化
static long int tt=0,money;
/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/
sbit p16=P1^6;//传感器1角引脚
sbit p15=P1^5;//传感器5角引脚
sbit p14=P1^4;//传感器1元引脚
sbit p17=P1^7;//定义外部清除引脚
VOID main(void) 
{
    LED_Init();
	  timer_init();//开启定时器计时30s
    MAIN_OLED_Display();      
}  

VOID MAIN_OLED_Display(VOID)
{
    int i=0,j=0,k=0,l,m;
	  long int temp1,temp2,y=0,wj=0,yj=0;
	  p16=0xff;
	  p14=0xff;
	  p15=0xff;
	  p17=0xff;   	
    display_init();	 
	  while(1)
		{			
			timer_init();//开启定时器计时30s
      if(p16==0xff|p15==0xff|p14==0xff)	//有硬币进入	 
     {		
			temp1=money;
			EA=1;//开启定时器0			 
			while(tt<1500)//30s延时
		  {
				if(p16==0xff)//1角
			{
			   money=money+1;	
				 yj=yj+1;
				 i=yj/1000;//千位
				 display_num(96,4,i);
				 j=yj/100-i*10;//百位
				 display_num(103,4,j);
				 k=yj%100/10;//十位
				 display_num(110,4,k);
				 l=yj%10;//个位		  
	       display_num(117,4,l);		
         MAIN_TIME_Delay(17);				
			}
			if(p15==0xff)//5角
			{				
			  money=money+5;
				wj=wj+1;
				i=wj/100;//百位
				display_num(68,4,i);
				j=wj/10-i*10;//十位
				display_num(75,4,j);
				k=wj%10;//个位  
	      display_num(82,4,k);//5毛定位初始化				
        MAIN_TIME_Delay(17);					
			}
			if(p14==0xff)//1元
			{				
			  money=money+10;	
				y=y+1;//元数值加一
				i=y/1000;//千位
				display_num(33,4,i);
				j=y/100-i*10;//百位
				display_num(40,4,j);
				k=y%100/10;//十位
				display_num(47,4,k);
				l=y%10;//个位		  
	      display_num(54,4,l);				
        MAIN_TIME_Delay(15);					
			}	
        i=money/10000;//千位
        display_num(53,2,i);//千位			
		    j=money/1000-i*10;//百位
			  display_num(61,2,j);//百位			
        k=money/100-i*100-j*10;//十位
			  display_num(69,2,k);//十位
			  l=money%100/10;//个位
			  display_num(77,2,l);//个位
        m=money%10;//角位
			  display_num(100,2,m);			
		  }		
      tt=0;//定时器归位			
			EA=0;//关闭定时器0      	
       if(money>=99999)//当计数大于9999元的时候置0
			  {
			     money=0;
			  }    				
		 temp2=money-temp1;//求出此次投入钱的多少			
		 //i=temp2/1000;//百位                      //此部分用于显示并储存此次投入钱的数值    
		 //display_num(61,6,i);//百位               //此部分用于显示并储存此次投入钱的数值
		 j=temp2/100-i*10;//十位                  //此部分用于显示并储存此次投入钱的数值		
		 display_num(69,6,j);//十位               //此部分用于显示并储存此次投入钱的数值
		 k=temp2%100/10;//个位                    //此部分用于显示并储存此次投入钱的数值		 
		 display_num(77,6,k);//个位               //此部分用于显示并储存此次投入钱的数值
		 l=temp2%10;//角                          //此部分用于显示并储存此次投入钱的数值		 
		 display_num(100,6,l);//个位              //此部分用于显示并储存此次投入钱的数值 
			
		}
		 
		 if(p17==0x00)//当外部清除按键被按下则清除数据
			{				
			  money=0;
        temp2=0;	
        y=0;
        wj=0;
        yj=0;				
				i=money/10000;//千位
        display_num(53,2,i);//千位			
		    j=money/1000-i*10;//百位
			  display_num(61,2,j);//百位			
        k=money/100-i*100-j*10;//十位
			  display_num(69,2,k);//十位
			  l=money%100/10;//个位
			  display_num(77,2,l);//个位
        m=money%10;//角位
			  display_num(100,2,m);	 
        i=temp2/1000;//百位                      //此部分用于显示并储存此次投入钱的数值        
		    display_num(61,6,i);//百位               //此部分用于显示并储存此次投入钱的数值
		    j=temp2/100-i*10;//十位                  //此部分用于显示并储存此次投入钱的数值		    
		    display_num(69,6,j);//十位               //此部分用于显示并储存此次投入钱的数值
		    k=temp2%100/10;//个位                    //此部分用于显示并储存此次投入钱的数值		   
		    display_num(77,6,k);//个位               //此部分用于显示并储存此次投入钱的数值
		    l=temp2%10;//角                          //此部分用于显示并储存此次投入钱的数值		    
		    display_num(100,6,l);//个位              //此部分用于显示并储存此次投入钱的数值 				
			  
				i=y/1000;//千位
				display_num(33,4,i);
				j=y/100-i*10;//百位
				display_num(40,4,j);
				k=y%100/10;//十位
				display_num(47,4,k);
				l=y%10;//个位		  
	      display_num(54,4,l);					
				i=wj/100;//百位
				display_num(68,4,i);
				j=wj/10-i*10;//十位
				display_num(75,4,j);
				k=wj%10;//个位  
	      display_num(82,4,k);//				
				 i=yj/1000;//千位
				 display_num(96,4,i);
				 j=yj/100-i*10;//百位
				 display_num(103,4,j);
				 k=yj%100/10;//十位
				 display_num(110,4,k);
				 l=yj%10;//个位		  
	       display_num(117,4,l);	
			}
			else
			{
			  ;
			}
		}   
}
void timer_init()//定时器初始化
{
  TL0=0Xff;
	TH0=0X4b;
	ET0=1;//启动定时器0中断
	TR0=1;//启动定时器0	
	EA=0;
}
void timer_0() interrupt 1
{
	TL0=0Xff;
	TH0=0X4c;//定时0.1ms
	tt++;		
}

void display_init()//显示初始化
{
	  int k,i,j,l,m;
	  money=0;//清零
    LED_P14x16Str(0, 0, (UCHAR8*)"已存入总金额："); 
	  LED_P14x16Str(85, 1, (UCHAR8*)"元");
    LED_P14x16Str(110, 1, (UCHAR8*)"角");	  
    LED_P14x16Str(0, 3, (UCHAR8*)"上次金额：");
    LED_P14x16Str(85, 3, (UCHAR8*)"元");
	  LED_P14x16Str(110, 3, (UCHAR8*)"角"); 
 	  LED_P14x16Str(0, 2, (UCHAR8*)"数量：");
	  LED_P8x16Str(60, 2, (UCHAR8*)"-");
	  LED_P8x16Str(87, 2, (UCHAR8*)"-");
	  display_num(33,4,0);
	  display_num(40,4,0);
	  display_num(47,4,0);
	  display_num(54,4,0);//元定位初始化
	
	  display_num(68,4,0);
	  display_num(75,4,0);
	  display_num(82,4,0);//5毛定位初始化
	  
	
	  display_num(96,4,0);
	  display_num(103,4,0);
	  display_num(110,4,0);
	  display_num(117,4,0);//1毛定位初始化
	      i=money/10000;//千位
        display_num(53,2,i);//千位			
		    j=money/1000-i*10;//百位
			  display_num(61,2,j);//百位			
        k=money/100-i*100-j*10;//十位
			  display_num(69,2,k);//十位
			  l=money%100/10;//个位
			  display_num(77,2,l);//个位
        m=money%10;//角位
			  display_num(100,2,m);		
}
/*****************************************************************************
 函 数 名  : MAIN_TIME_Delay
 功能描述  : 在12MHz晶振 1T下 延时时间约等于usTime ms
 输入参数  : USHORT16 usTime  
 输出参数  : NONE
 返 回 值  : 
*****************************************************************************/
VOID MAIN_TIME_Delay(USHORT16 usTime)
{
    UCHAR8 j;
    LONG32 i;
    
    for (i = (LONG32)10 * usTime; i > 0; i--)
    {
        for(j = 110; j > 0; j--)
        {
        }
    }

    return;
}

