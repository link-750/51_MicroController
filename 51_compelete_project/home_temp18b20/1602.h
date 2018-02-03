#ifndef __1602_H__
#define __1602_H__
# define uchar unsigned char
# define uint unsigned int
void LCD_init(void); // - - ��ʼ��LCD1602����
void LCD_write_command(uchar command); // - - ��LCD1602дָ���
void LCD_write_data(uchar dat); // - - ��LCD1602д���ݺ���
void LCD_set_xy(uchar x,uchar y); // - - ����LCD1602��ʾλ�� X��0-16),y(1-2)
void LCD_disp_char(uchar x,uchar y,uchar dat); // - - ��LCD1602����ʾһ���ַ�
void LCD_disp_string(uchar X,uchar Y,uchar *s); // - - ��LCD1602����ʾһ���ַ���
//void LCD_check_busy(void);//���æ��������û�õ��˺�������Ϊͨ���ʼ��͡�
void LCD_delay_10us(uint n); // - - 10΢�����ʱ�ӳ���
void LCD_delay_50us(uint n); // - - 50΢�����ʱ�ӳ���
#endif