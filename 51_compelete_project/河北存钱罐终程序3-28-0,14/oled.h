/******************************************************************************

          ��Ȩ���� (C), 2011-2012, ������ӿƼ�(http://xydz123.taobao.com/)

 ******************************************************************************
  �� �� ��   : oled.h
  �� �� ��   : v1.0
  ��    ��   : Guokaiyi
  ��������   : 2012-11-12
  ����޸�   : 
  ��������   : oled.c ��ͷ�ļ�
  �޸���ʷ   :
  1.��    ��   : 2012-11-12
    ��    ��   : Guokaiyi
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __OLED_H__
#define __OLED_H__

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
#define LED_IMAGE_WHITE       1
#define LED_IMAGE_BLACK       0

#define LED_MAX_ROW_NUM      64
#define LED_MAX_COLUMN_NUM  128

/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
extern VOID LED_Init(VOID);
extern VOID LED_SetPos(UCHAR8 ucIdxX, UCHAR8 ucIdxY); 
extern VOID LED_P6x8Char(UCHAR8 ucIdxX,UCHAR8 ucIdxY,UCHAR8 ucData);
extern VOID LED_P6x8Str(UCHAR8 ucIdxX,UCHAR8 ucIdxY,UCHAR8 ucDataStr[]);
extern VOID LED_P8x16Str(UCHAR8 ucIdxX,UCHAR8 ucIdxY,UCHAR8 ucDataStr[]);
extern VOID LED_P14x16Str(UCHAR8 ucIdxX,UCHAR8 ucIdxY,UCHAR8 ucDataStr[]);
extern VOID LED_PXx16MixStr(UCHAR8 ucIdxX, UCHAR8 ucIdxY, UCHAR8 ucDataStr[]);
extern VOID LED_Fill(UCHAR8 ucData);
extern VOID LED_PrintChar(UCHAR8 ucIdxX, UCHAR8 ucIdxY, CHAR8 cData);
extern VOID LED_PrintShort(UCHAR8 ucIdxX, UCHAR8 ucIdxY, SHORT16 sData);
extern VOID LED_PrintImage(UCHAR8 *pucTable, USHORT16 usRowNum, USHORT16 usColumnNum);
extern void display_num(unsigned char x,unsigned char y,int num);
#endif

