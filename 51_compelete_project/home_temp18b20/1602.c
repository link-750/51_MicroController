#include "reg52.h"
#include "1602.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - 初始化接口
# define LCD_DB   P0  // - - P0   = DB0～DB7
sbit     LCD_RS=P2^6; // - - p2.0 = RS
sbit     LCD_RW=P2^5; // - - p2.1 = RW
sbit     LCD_E=P2^7;  // - - p2.2 = E
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - 定义函数

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - 定义子程序函数

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//void main()
//{
//  LCD_init();
//	LCD_disp_char(8,3,'9');
//	while(1);
//}
// - - 初始化LCD1602
void LCD_init(void)
{
LCD_delay_10us(20);
LCD_write_command(0x38); // - - 设置8位格式，2行，5x7
LCD_delay_10us(5);
LCD_write_command(0x0c); // - - 整体显示，关光标，不闪烁
LCD_delay_10us(5);
LCD_write_command(0x06); // - - 设定输入方式，增量不移位
LCD_delay_10us(5);
LCD_write_command(0x01); // - - 清除屏幕显示
LCD_delay_50us(40);
}
//********************************

// - - 向LCD1602写指令
void LCD_write_command(uchar dat)
{
LCD_delay_10us(5);
LCD_RS=0; // - - 指令
LCD_RW=0; // - - 写入
LCD_DB=dat;
LCD_delay_10us(5);
LCD_E=1; // - - 允许
LCD_delay_10us(5);
LCD_E=0;
}

// - - 向LCD1602写数据
void LCD_write_data(uchar dat) 
{
LCD_delay_10us(5);
LCD_RS=1;// - - 数据
LCD_RW=0;// - - 写入
LCD_DB=dat;
LCD_delay_10us(5);
LCD_E=1;// - - 允许
LCD_delay_10us(5);
LCD_E=0;
}

// - - 设置显示位置
void LCD_set_xy(uchar x,uchar y)
{
  uchar address;
  if(y==1)
  {
    address=0x80+x-1; // - - 第一行位置
  } else {
    address=0xc0+x-1; // - - 第二行位置
  }
    LCD_delay_10us(5);
    LCD_write_command(address);
}

// - - 显示一个字符函数
void LCD_disp_char(uchar x,uchar y,uchar dat) // - - LCD_disp_char(0,1,0x38); // - - 显示8
{
    LCD_set_xy(x,y);
    LCD_delay_10us(5);
    LCD_write_data(dat);
}

// - - 显示一个字符串函数
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
/*******检查忙函数*************
void LCD_check_busy() //实践证明，在我的LCD1602上，检查忙指令通过率极低，以
{  //至于不能正常使用LCD。因此我没有再用检查忙函数。而使
  do   //用了延时的方法，延时还是非常好用的。我试了一下，用
  { LCD_E=0;   //for循环作延时，普通指令只要1次循就可完成。清屏指令
    LCD_RS=0;                 //要用200次循环便能完成。   
    LCD_RW=1;
    LCD_DB=0xff;
    LCD_E=1;
  }while(LCD_DB^7==1);
｝
******************************/

void LCD_delay_10us(uint n) // - - 10微秒的延时子程序
{ 
  uint i,j;
  for(i=n;i>0;i--)
    for(j=2;j>0;j--);  
} 

void LCD_delay_50us(uint n) // - - 50微秒的延时子程序
{ 
  uint i,j;
  for(i=n;i>0;i--)
    for(j=22;j>0;j--);  
} 
