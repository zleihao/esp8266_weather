/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�����ļ�
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.26
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 ********************************************************************************************************************/


#ifndef _SEEKFREE_FONT_h
#define _SEEKFREE_FONT_h
#include "stm32f4xx_hal.h"

typedef unsigned char      uint8;   //  8 bits 
typedef unsigned short int uint16;  // 16 bits 
typedef unsigned long int  uint32;  // 32 bits 
typedef unsigned long long uint64;  // 64 bits 

typedef signed char        int8;    //  8 bits 
typedef signed short int   int16;   // 16 bits 
typedef long  int          int32;   // 32 bits 
typedef long  long         int64;   // 64 bits 

typedef volatile int8       vint8;   //  8 bits 
typedef volatile int16      vint16;  // 16 bits 
typedef volatile int32      vint32;  // 32 bits 
typedef volatile int64      vint64;  // 64 bits 

typedef volatile uint8      vuint8;  //  8 bits 
typedef volatile uint16     vuint16; // 16 bits 
typedef volatile uint32     vuint32; // 32 bits 
typedef volatile uint64     vuint64; // 64 bits 


extern const uint8 tft_ascii[95][16];

extern const uint8 gImage_qq[3200];

extern const uint8 chinese_test[40][16];

extern const uint8 oled_6x8[][6];

extern const uint8 oled_8x16[];

extern const uint8 oled_16x16_chinese[][16];

extern const unsigned char ascii_1206[][12];
extern const unsigned char ascii_1608[][16];
extern const unsigned char ascii_2412[][48];
extern const unsigned char ascii_3216[][64];

#endif
