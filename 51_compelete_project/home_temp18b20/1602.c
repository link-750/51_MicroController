#include "reg52.h"
#include "1602.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - ��ʼ���ӿ�
# define LCD_DB   P0  // - - P0   = DB0��DB7
sbit     LCD_RS=P2^6; // - - p2.0 = RS
sbit     LCD_RW=P2^5; // - - p2.1 = RW
sbit     LCD_E=P2^7;  // - - p2.2 = E
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - ���庯��

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - �����ӳ�����

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//void main()
//{
//  LCD_init();
//	LCD_disp_char(8,3,'9');
//	while(1);
//}
// - - ��ʼ��LCD1602
void LCD_init(void)
{
LCD_delay_10us(20);
LCD_write_command(0x38); // - - ����8λ��ʽ��2�У�5x7
LCD_delay_10us(5);
LCD_write_command(0x0c); // - - ������ʾ���ع�꣬����˸
LCD_delay_10us(5);
LCD_write_command(0x06); // - - �趨���뷽ʽ����������λ
LCD_delay_10us(5);
LCD_write_command(0x01); // - - �����Ļ��ʾ
LCD_delay_50us(40);
}
//********************************

// - - ��LCD1602дָ��
void LCD_write_command(uchar dat)
{
LCD_delay_10us(5);
LCD_RS=0; // - - ָ��
LCD_RW=0; // - - д��
LCD_DB=dat;
LCD_delay_10us(5);
LCD_E=1; // - - ����
LCD_delay_10us(5);
LCD_E=0;
}

// - - ��LCD1602д����
void LCD_write_data(uchar dat) 
{
LCD_delay_10us(5);
LCD_RS=1;// - - ����
LCD_RW=0;// - - д��
LCD_DB=dat;
LCD_delay_10us(5);
LCD_E=1;// - - ����
LCD_delay_10us(5);
LCD_E=0;
}

// - - ������ʾλ��
void LCD_set_xy(uchar x,uchar y)
{
  uchar address;
  if(y==1)
  {
    address=0x80+x-1; // - - ��һ��λ��
  } else {
    address=0xc0+x-1; // - - �ڶ���λ��
  }
    LCD_delay_10us(5);
    LCD_write_command(address);
}

// - - ��ʾһ���ַ�����
void LCD_disp_char(uchar x,uchar y,uchar dat) // - - LCD_disp_char(0,1,0x38); // - - ��ʾ8
{
    LCD_set_xy(x,y);
    LCD_delay_10us(5);
    LCD_write_data(dat);
}

// - - ��ʾһ���ַ�������
void LCD_disp_string(uchar x,uchar y,uchar *s)
{
  LCD_set_xy(x,y);
  LCD_delay_10us(5);
  while(*s!='\0')
  {
    LCD_write_data(*s);
    s++;
  }
}

//********************************
/*******���æ����*************
void LCD_check_busy() //ʵ��֤�������ҵ�LCD1602�ϣ����æָ��ͨ���ʼ��ͣ���
{  //���ڲ�������ʹ��LCD�������û�����ü��æ��������ʹ
  do   //������ʱ�ķ�������ʱ���Ƿǳ����õġ�������һ�£���
  { LCD_E=0;   //forѭ������ʱ����ָͨ��ֻҪ1��ѭ�Ϳ���ɡ�����ָ��
    LCD_RS=0;                 //Ҫ��200��ѭ��������ɡ�   
    LCD_RW=1;
    LCD_DB=0xff;
    LCD_E=1;
  }while(LCD_DB^7==1);
��
******************************/

void LCD_delay_10us(uint n) // - - 10΢�����ʱ�ӳ���
{ 
  uint i,j;
  for(i=n;i>0;i--)
    for(j=2;j>0;j--);  
} 

void LCD_delay_50us(uint n) // - - 50΢�����ʱ�ӳ���
{ 
  uint i,j;
  for(i=n;i>0;i--)
    for(j=22;j>0;j--);  
} 
