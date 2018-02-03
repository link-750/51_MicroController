#ifndef __1602_H__
#define __1602_H__
# define uchar unsigned char
# define uint unsigned int
void LCD_init(void); // - - 初始化LCD1602函数
void LCD_write_command(uchar command); // - - 向LCD1602写指令函数
void LCD_write_data(uchar dat); // - - 向LCD1602写数据函数
void LCD_set_xy(uchar x,uchar y); // - - 设置LCD1602显示位置 X（0-16),y(1-2)
void LCD_disp_char(uchar x,uchar y,uchar dat); // - - 在LCD1602上显示一个字符
void LCD_disp_string(uchar X,uchar Y,uchar *s); // - - 在LCD1602上显示一个字符串
//void LCD_check_busy(void);//检查忙函数。我没用到此函数，因为通过率极低。
void LCD_delay_10us(uint n); // - - 10微秒的延时子程序
void LCD_delay_50us(uint n); // - - 50微秒的延时子程序
#endif