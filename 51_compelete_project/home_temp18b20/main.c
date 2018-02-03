#include "reg51.h"
#include <intrins.h> 
#include "1602.h"  

//#include "DS18B20.h"  
void DS18B20_Delayus(uint us);  
void DS18B20_reset();  
void DS18B20_write(uchar dat);  
uchar DS18B20_data();  
uint read_temperature();  
uint TT;  //1820�¶ȱ���  
sbit DQ = P3^7;  
  

/*******************************************************************/  
/*                                                                 */  
/*us����ʱ����                                                     */  
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
    DS18B20_Delayus(16);  //������ʱ  
    DQ = 0; //��DQ����  
    DS18B20_Delayus(160);//��ʱ400us~960us  
    DQ = 1;    //��������  
    DS18B20_Delayus(28);//��ʱ15us~60us  
    x = DQ; //���=0���ʼ���ɹ� =1���ʼ��ʧ��  
    DS18B20_Delayus(40);//��ʱ60us~240us  
}  
/*******************************************************************/  
/*                                                                 */  
/* дһ���ֽ�                                                      */  
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
/* ��һ���ֽ�                                                      */  
/*                                                                 */  
/*******************************************************************/  
uchar DS18B20_data()  
{  
    uchar i,dat;  
    for (i = 8; i > 0; i--)  
    {  
      DQ = 0; // �������ź�  
      dat >>= 1;  
      DQ = 1; // �������ź�  
      if(DQ)  
        dat |= 0x80;  
      DS18B20_Delayus(8);  
    }  
    return dat;  
}  
/*******************************************************************/  
/*                                                                 */  
/* ��ȡ�¶�                                                        */  
/*                                                                 */  
/*******************************************************************/  
uint read_temperature()  
{  
    uchar a,b;  
    uint t = 0;  
    float tt = 0;  
  
    DS18B20_reset();//DS18B20��λ  
    DS18B20_write(0xcc); //����������кŵĲ���  
    DS18B20_write(0x44); //�����¶�ת��     
  
    DS18B20_reset();//DS18B20��λ  
    DS18B20_write(0xcc); //����������кŵĲ���  
    DS18B20_write(0xbe); //��ȡ�¶ȼĴ���  
    a = DS18B20_data(); //����8λ  
    b = DS18B20_data();  //����8λ  
    t=b;  
    t<<=8;  
    t=t|a;  
    tt=t*0.0625;  
    t= tt*10+0.5; //�Ŵ�10���������������  
    return(t);  
} 

void main()  
{  
      uchar tab1,tab2,tab3;       
      LCD_init();  
      DS18B20_reset();   
      while(1)  
      {  
            TT = read_temperature(); //���¶�   
            tab1 = TT / 100;              
				    LCD_disp_char(8,1,tab1+48);//ʮλ
            tab2= TT / 10 - tab1*10;             
            LCD_disp_char(9,1,tab2+48);	//��λ           
						LCD_disp_char(10,1,'.');//С����
            tab3 = TT - tab1*100 - tab2*10;             
				    LCD_disp_char(11,1,tab3+48);//С��λ            
            LCD_disp_char(12,1,'C');//�¶ȷ���              
      }  
} 