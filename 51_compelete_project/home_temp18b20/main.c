#include "reg51.h"
#include <intrins.h> 
#include "1602.h"  

//#include "DS18B20.h"  
void DS18B20_Delayus(uint us);  
void DS18B20_reset();  
void DS18B20_write(uchar dat);  
uchar DS18B20_data();  
uint read_temperature();  
uint TT;  //1820温度变量  
sbit DQ = P3^7;  
  

/*******************************************************************/  
/*                                                                 */  
/*us级延时函数                                                     */  
/*                                                                 */  
/*******************************************************************/  
void DS18B20_Delayus(uint us)  
{  
    while(--us);  
}  
void DS18B20_reset()  
{  
    uchar x = 0;  
    DQ = 1;  
    DS18B20_Delayus(16);  //稍做延时  
    DQ = 0; //将DQ拉低  
    DS18B20_Delayus(160);//延时400us~960us  
    DQ = 1;    //拉高总线  
    DS18B20_Delayus(28);//延时15us~60us  
    x = DQ; //如果=0则初始化成功 =1则初始化失败  
    DS18B20_Delayus(40);//延时60us~240us  
}  
/*******************************************************************/  
/*                                                                 */  
/* 写一个字节                                                      */  
/*                                                                 */  
/*******************************************************************/  
void DS18B20_write(uchar dat)  
{  
     uchar i;  
     for(i = 8; i > 0; i--)  
     {  
         DQ = 0;  
         DQ = dat & 0x01;  
         DS18B20_Delayus(10);  
         DQ = 1;  
         dat >>= 1;  
     }  
}  
/*******************************************************************/  
/*                                                                 */  
/* 读一个字节                                                      */  
/*                                                                 */  
/*******************************************************************/  
uchar DS18B20_data()  
{  
    uchar i,dat;  
    for (i = 8; i > 0; i--)  
    {  
      DQ = 0; // 给脉冲信号  
      dat >>= 1;  
      DQ = 1; // 给脉冲信号  
      if(DQ)  
        dat |= 0x80;  
      DS18B20_Delayus(8);  
    }  
    return dat;  
}  
/*******************************************************************/  
/*                                                                 */  
/* 读取温度                                                        */  
/*                                                                 */  
/*******************************************************************/  
uint read_temperature()  
{  
    uchar a,b;  
    uint t = 0;  
    float tt = 0;  
  
    DS18B20_reset();//DS18B20复位  
    DS18B20_write(0xcc); //跳过读序号列号的操作  
    DS18B20_write(0x44); //启动温度转换     
  
    DS18B20_reset();//DS18B20复位  
    DS18B20_write(0xcc); //跳过读序号列号的操作  
    DS18B20_write(0xbe); //读取温度寄存器  
    a = DS18B20_data(); //读低8位  
    b = DS18B20_data();  //读高8位  
    t=b;  
    t<<=8;  
    t=t|a;  
    tt=t*0.0625;  
    t= tt*10+0.5; //放大10倍输出并四舍五入  
    return(t);  
} 

void main()  
{  
      uchar tab1,tab2,tab3;       
      LCD_init();  
      DS18B20_reset();   
      while(1)  
      {  
            TT = read_temperature(); //读温度   
            tab1 = TT / 100;              
				    LCD_disp_char(8,1,tab1+48);//十位
            tab2= TT / 10 - tab1*10;             
            LCD_disp_char(9,1,tab2+48);	//个位           
						LCD_disp_char(10,1,'.');//小数点
            tab3 = TT - tab1*100 - tab2*10;             
				    LCD_disp_char(11,1,tab3+48);//小数位            
            LCD_disp_char(12,1,'C');//温度符号              
      }  
} 