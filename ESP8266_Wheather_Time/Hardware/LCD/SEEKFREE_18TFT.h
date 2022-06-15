/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		TFT
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.26
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					���߶��壺
					------------------------------------ 
					ģ��ܽ�            ��Ƭ���ܽ�
					SCL                 �鿴TFT_SCL�궨�������     Ӳ��SPI���Ų��������л�
					SDA                 �鿴TFT_SDA�궨�������     Ӳ��SPI���Ų��������л�
					RES                 �鿴REST_PIN�궨�������    
					DC                  �鿴DC_PIN�궨�������  
					CS                  �鿴TFT_CS�궨�������      Ӳ��SPI���Ų��������л�
					
					��Դ����
					BL  3.3V��Դ������������ţ�Ҳ���Խ�PWM���������ȣ�
					VCC 3.3V��Դ
					GND ��Դ��
					���ֱ���128*160
					------------------------------------ 

 ********************************************************************************************************************/



#ifndef _SEEKFREE_18TFT_h
#define _SEEKFREE_18TFT_h
#include "SEEKFREE_FONT.h"
#include "main.h"
     

     
#define BL_PIN		B13	            //Һ���������Ŷ���  ����ʵ��ͨѶδʹ��B13��� ���︴��ΪGPIO����BL����
#define REST_PIN	B8              //Һ����λ���Ŷ���
#define DC_PIN		B9	            //Һ������λ���Ŷ���

     
#define TFT_DC(x)    	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,(GPIO_PinState)x)
#define REST(x) 	 	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin,(GPIO_PinState)x)
#define TFT_SCL(x) 		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin,(GPIO_PinState)x)
#define TFT_SDA(x) 		HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin,(GPIO_PinState)x)
#define TFT_CS(x) 		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin,(GPIO_PinState)x)



//-------������ɫ----------
#define RED     	0XF800    //��ɫ
#define GREEN   	0X07E0    //��ɫ
#define BLUE    	0X001F    //��ɫ
#define BRED    	0XF81F
#define GRED    	0XFFE0    //��ɫ
#define GBLUE   	0X07FF    //
#define BLACK   	0X0000    //��ɫ
#define WHITE   	0XFFFF    //��ɫ
#define YELLOW  	0xFFE0    //��ɫ



//����д�ֱʵ���ɫ
#define PENCOLOR    RED

//���屳����ɫ
#define BGCOLOR	    WHITE

     
     
//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
#define TFT_DISPLAY_DIR 0

#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
#define	TFT_X_MAX	128	//Һ��X�����
#define TFT_Y_MAX	160 //Һ��Y�����
     
#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
#define	TFT_X_MAX	160	//Һ��X�����
#define TFT_Y_MAX	128 //Һ��Y�����
     
#else
#error "TFT_DISPLAY_DIR �������"
     
#endif


void lcd_init(void);
void lcd_clear(int color);
void lcd_drawpoint(uint16 x,uint16 y,uint16 color);
void lcd_showchar(uint16 x,uint16 y,uint8 dat);
void lcd_showstr(uint16 x,uint16 y,uint8 dat[],uint8_t len);
void lcd_showint8(uint16 x,uint16 y,int8 dat);
void lcd_showuint8(uint16 x,uint16 y,uint8 dat);
void lcd_showint16(uint16 x,uint16 y,int16 dat);
void lcd_showuint16(uint16 x,uint16 y,uint16 dat);
void lcd_showint32(uint16 x,uint16 y,int32 dat,uint8 num);
void lcd_showfloat(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);
void showimage(const unsigned char *p);
void lcd_displayimage032(uint8 *p, uint16 width, uint16 height);
void lcd_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void lcd_displayimage7725(uint8 *p, uint16 width, uint16 height);
void lcd_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);

#endif
