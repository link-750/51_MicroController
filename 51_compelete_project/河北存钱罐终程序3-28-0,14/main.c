/******************************************************************************

          ��Ȩ���� (C), 2011-2012, ������ӿƼ�(http://xydz123.taobao.com/)

 ******************************************************************************
  �� �� ��   : main.c
  �� �� ��   : v1.0
  ��    ��   : Guokaiyi
  ��������   : 2017-3-28
  ����޸�   : 
  ��������   : OLED��ʾ����(51ϵ��)
               ˵��: 
               ----------------------------------------------------------------
               G    ��Դ��
               VCC  ��5V��3.3v��Դ
               D0   P1^0��SCLK��
               D1   P1^1��MOSI��
               RST  P1^2
               DC   P1^3
               CS   �Ѿ�Ĭ��ѡ�У����Բ���                   
               ----------------------------------------------------------------
  �޸���ʷ   :
  1.��    ��   : 2017-3-28
    ��    ��   :  ��ΰ����껴�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"
#include "oled.h"
#include "flash.h"

VOID MAIN_Init(VOID); //��ʼ������
VOID MAIN_OLED_Display(VOID); //OLED��ʾ����
VOID MAIN_TIME_Delay(USHORT16 usTime); //��ʱ����
void display_init();
void timer_init();//��ʱ����ʼ��
static long int tt=0,money;
/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
sbit p16=P1^6;//������1������
sbit p15=P1^5;//������5������
sbit p14=P1^4;//������1Ԫ����
sbit p17=P1^7;//�����ⲿ�������
VOID main(void) 
{
    LED_Init();
	  timer_init();//������ʱ����ʱ30s
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
			timer_init();//������ʱ����ʱ30s
      if(p16==0xff|p15==0xff|p14==0xff)	//��Ӳ�ҽ���	 
     {		
			temp1=money;
			EA=1;//������ʱ��0			 
			while(tt<1500)//30s��ʱ
		  {
				if(p16==0xff)//1��
			{
			   money=money+1;	
				 yj=yj+1;
				 i=yj/1000;//ǧλ
				 display_num(96,4,i);
				 j=yj/100-i*10;//��λ
				 display_num(103,4,j);
				 k=yj%100/10;//ʮλ
				 display_num(110,4,k);
				 l=yj%10;//��λ		  
	       display_num(117,4,l);		
         MAIN_TIME_Delay(17);				
			}
			if(p15==0xff)//5��
			{				
			  money=money+5;
				wj=wj+1;
				i=wj/100;//��λ
				display_num(68,4,i);
				j=wj/10-i*10;//ʮλ
				display_num(75,4,j);
				k=wj%10;//��λ  
	      display_num(82,4,k);//5ë��λ��ʼ��				
        MAIN_TIME_Delay(17);					
			}
			if(p14==0xff)//1Ԫ
			{				
			  money=money+10;	
				y=y+1;//Ԫ��ֵ��һ
				i=y/1000;//ǧλ
				display_num(33,4,i);
				j=y/100-i*10;//��λ
				display_num(40,4,j);
				k=y%100/10;//ʮλ
				display_num(47,4,k);
				l=y%10;//��λ		  
	      display_num(54,4,l);				
        MAIN_TIME_Delay(15);					
			}	
        i=money/10000;//ǧλ
        display_num(53,2,i);//ǧλ			
		    j=money/1000-i*10;//��λ
			  display_num(61,2,j);//��λ			
        k=money/100-i*100-j*10;//ʮλ
			  display_num(69,2,k);//ʮλ
			  l=money%100/10;//��λ
			  display_num(77,2,l);//��λ
        m=money%10;//��λ
			  display_num(100,2,m);			
		  }		
      tt=0;//��ʱ����λ			
			EA=0;//�رն�ʱ��0      	
       if(money>=99999)//����������9999Ԫ��ʱ����0
			  {
			     money=0;
			  }    				
		 temp2=money-temp1;//����˴�Ͷ��Ǯ�Ķ���			
		 //i=temp2/1000;//��λ                      //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ    
		 //display_num(61,6,i);//��λ               //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ
		 j=temp2/100-i*10;//ʮλ                  //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ		
		 display_num(69,6,j);//ʮλ               //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ
		 k=temp2%100/10;//��λ                    //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ		 
		 display_num(77,6,k);//��λ               //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ
		 l=temp2%10;//��                          //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ		 
		 display_num(100,6,l);//��λ              //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ 
			
		}
		 
		 if(p17==0x00)//���ⲿ����������������������
			{				
			  money=0;
        temp2=0;	
        y=0;
        wj=0;
        yj=0;				
				i=money/10000;//ǧλ
        display_num(53,2,i);//ǧλ			
		    j=money/1000-i*10;//��λ
			  display_num(61,2,j);//��λ			
        k=money/100-i*100-j*10;//ʮλ
			  display_num(69,2,k);//ʮλ
			  l=money%100/10;//��λ
			  display_num(77,2,l);//��λ
        m=money%10;//��λ
			  display_num(100,2,m);	 
        i=temp2/1000;//��λ                      //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ        
		    display_num(61,6,i);//��λ               //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ
		    j=temp2/100-i*10;//ʮλ                  //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ		    
		    display_num(69,6,j);//ʮλ               //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ
		    k=temp2%100/10;//��λ                    //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ		   
		    display_num(77,6,k);//��λ               //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ
		    l=temp2%10;//��                          //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ		    
		    display_num(100,6,l);//��λ              //�˲���������ʾ������˴�Ͷ��Ǯ����ֵ 				
			  
				i=y/1000;//ǧλ
				display_num(33,4,i);
				j=y/100-i*10;//��λ
				display_num(40,4,j);
				k=y%100/10;//ʮλ
				display_num(47,4,k);
				l=y%10;//��λ		  
	      display_num(54,4,l);					
				i=wj/100;//��λ
				display_num(68,4,i);
				j=wj/10-i*10;//ʮλ
				display_num(75,4,j);
				k=wj%10;//��λ  
	      display_num(82,4,k);//				
				 i=yj/1000;//ǧλ
				 display_num(96,4,i);
				 j=yj/100-i*10;//��λ
				 display_num(103,4,j);
				 k=yj%100/10;//ʮλ
				 display_num(110,4,k);
				 l=yj%10;//��λ		  
	       display_num(117,4,l);	
			}
			else
			{
			  ;
			}
		}   
}
void timer_init()//��ʱ����ʼ��
{
  TL0=0Xff;
	TH0=0X4b;
	ET0=1;//������ʱ��0�ж�
	TR0=1;//������ʱ��0	
	EA=0;
}
void timer_0() interrupt 1
{
	TL0=0Xff;
	TH0=0X4c;//��ʱ0.1ms
	tt++;		
}

void display_init()//��ʾ��ʼ��
{
	  int k,i,j,l,m;
	  money=0;//����
    LED_P14x16Str(0, 0, (UCHAR8*)"�Ѵ����ܽ�"); 
	  LED_P14x16Str(85, 1, (UCHAR8*)"Ԫ");
    LED_P14x16Str(110, 1, (UCHAR8*)"��");	  
    LED_P14x16Str(0, 3, (UCHAR8*)"�ϴν�");
    LED_P14x16Str(85, 3, (UCHAR8*)"Ԫ");
	  LED_P14x16Str(110, 3, (UCHAR8*)"��"); 
 	  LED_P14x16Str(0, 2, (UCHAR8*)"������");
	  LED_P8x16Str(60, 2, (UCHAR8*)"-");
	  LED_P8x16Str(87, 2, (UCHAR8*)"-");
	  display_num(33,4,0);
	  display_num(40,4,0);
	  display_num(47,4,0);
	  display_num(54,4,0);//Ԫ��λ��ʼ��
	
	  display_num(68,4,0);
	  display_num(75,4,0);
	  display_num(82,4,0);//5ë��λ��ʼ��
	  
	
	  display_num(96,4,0);
	  display_num(103,4,0);
	  display_num(110,4,0);
	  display_num(117,4,0);//1ë��λ��ʼ��
	      i=money/10000;//ǧλ
        display_num(53,2,i);//ǧλ			
		    j=money/1000-i*10;//��λ
			  display_num(61,2,j);//��λ			
        k=money/100-i*100-j*10;//ʮλ
			  display_num(69,2,k);//ʮλ
			  l=money%100/10;//��λ
			  display_num(77,2,l);//��λ
        m=money%10;//��λ
			  display_num(100,2,m);		
}
/*****************************************************************************
 �� �� ��  : MAIN_TIME_Delay
 ��������  : ��12MHz���� 1T�� ��ʱʱ��Լ����usTime ms
 �������  : USHORT16 usTime  
 �������  : NONE
 �� �� ֵ  : 
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

