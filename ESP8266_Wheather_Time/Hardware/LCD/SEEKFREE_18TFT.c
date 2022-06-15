/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		TFT
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.26
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					接线定义：
					------------------------------------ 
					模块管脚            单片机管脚
					SCL                 查看TFT_SCL宏定义的引脚     硬件SPI引脚不可随意切换
					SDA                 查看TFT_SDA宏定义的引脚     硬件SPI引脚不可随意切换
					RES                 查看REST_PIN宏定义的引脚    
					DC                  查看DC_PIN宏定义的引脚  
					CS                  查看TFT_CS宏定义的引脚      硬件SPI引脚不可随意切换
					
					电源引脚
					BL  3.3V电源（背光控制引脚，也可以接PWM来控制亮度）
					VCC 3.3V电源
					GND 电源地
					最大分辨率128*160
					------------------------------------ 

 ********************************************************************************************************************/




#include "SEEKFREE_FONT.h"

#include "SEEKFREE_18TFT.h"
#include "stm32f4xx_hal.h"





void  lcd_writeIndex(uint8 dat)			//写命令
{	

	uint8 i=8;
	
    TFT_CS(0);
	TFT_DC(0);
	TFT_SCL(0);
	
	while(i--)
	{
		if(dat&0x80){TFT_SDA(1);}
		else{TFT_SDA(0);}
		TFT_SCL(1);
		
		TFT_SCL(0);
		dat<<=1;
	}	
    TFT_CS(1);
}

void lcd_writeData(uint8 dat)			//写数据
{
	uint8 i=8;
	
    TFT_CS(0);
	TFT_DC(1);
	TFT_SCL(0);
	while(i--)
	{
	  	if(dat&0x80){TFT_SDA(1);}
	  	else{TFT_SDA(0);}
	  	TFT_SCL(1);
		
	  	TFT_SCL(0);
	  	dat<<=1;
	}
    TFT_CS(1);

}

void lcd_writedata_16bit(uint16 dat)	//向液晶屏写一个16位数据
{

	uint8 i=16;
    TFT_CS(0);
    TFT_DC(1);
    TFT_SCL(0);
	while(i--)
	{
	  	if(dat&0x8000){TFT_SDA(1);}
	  	else{TFT_SDA(0);}
	  	TFT_SCL(1);
		
	  	TFT_SCL(0);
	  	dat<<=1;
	}
    TFT_CS(1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶坐标设置
//  @param      x_start     	坐标x方向的起点
//  @param      y_start     	坐标y方向的起点
//  @param      x_end       	坐标x方向的终点
//  @param      y_end       	坐标y方向的终点
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_set_region(0,0,10,10);// x、y的起点都是0，终点都是10
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_region(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	

    
#if (0 == TFT_DISPLAY_DIR || 1 == TFT_DISPLAY_DIR)
    lcd_writeIndex(0x2a);
	lcd_writeData(0x00);
	lcd_writeData(x_start+2);
	lcd_writeData(0x00);
	lcd_writeData(x_end+2);

	lcd_writeIndex(0x2b);
	lcd_writeData(0x00);
	lcd_writeData(y_start+1);
	lcd_writeData(0x00);
	lcd_writeData(y_end+1);	

#elif(2 == TFT_DISPLAY_DIR || 3 == TFT_DISPLAY_DIR)
    lcd_writeIndex(0x2a);
	lcd_writeData(0x00);
	lcd_writeData(x_start+1);
	lcd_writeData(0x0);
	lcd_writeData(x_end+1);

	lcd_writeIndex(0x2b);
	lcd_writeData(0x00);
	lcd_writeData(y_start+2);
	lcd_writeData(0x00);
	lcd_writeData(y_end+2);	

#endif
    
    lcd_writeIndex(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_clear(YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void lcd_clear(int color)
{
 	uint8 i,j;
	lcd_set_region(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
 	for (i=0;i<TFT_Y_MAX;i++)
    	for (j=0;j<TFT_X_MAX;j++)
        	lcd_writedata_16bit(color);
}

/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	lcd_set_region(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			lcd_writedata_16bit(color);
		}
	} 					  	    
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶初始化
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_init(void)
{	


    
    REST(0);
    HAL_Delay(10);
    REST(1);
    HAL_Delay(120);
    lcd_writeIndex(0x11);
    HAL_Delay(120);

    lcd_writeIndex(0xB1); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    
    lcd_writeIndex(0xB2); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    
    lcd_writeIndex(0xB3); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    
    lcd_writeIndex(0xB4);
    lcd_writeData(0x07); 

    lcd_writeIndex(0xC0); 
    lcd_writeData(0xA2); 
    lcd_writeData(0x02); 
    lcd_writeData(0x84); 
    lcd_writeIndex(0xC1); 
    lcd_writeData(0xC5); 
    
    lcd_writeIndex(0xC2); 
    lcd_writeData(0x0A); 
    lcd_writeData(0x00); 
    
    lcd_writeIndex(0xC3); 
    lcd_writeData(0x8A); 
    lcd_writeData(0x2A); 
    lcd_writeIndex(0xC4); 
    lcd_writeData(0x8A); 
    lcd_writeData(0xEE); 
    
    lcd_writeIndex(0xC5);
    lcd_writeData(0x0E); 
    
    lcd_writeIndex(0x36);
    switch(TFT_DISPLAY_DIR)//y x v
    {
        case 0: lcd_writeData(1<<7 | 1<<6 | 0<<5);  break;  //竖屏模式
        case 1: lcd_writeData(0<<7 | 0<<6 | 0<<5);  break;  //竖屏模式  旋转180
        case 2: lcd_writeData(1<<7 | 0<<6 | 1<<5);  break;  //横屏模式
        case 3: lcd_writeData(0<<7 | 1<<6 | 1<<5);  break;  //横屏模式  旋转180
    }

    lcd_writeIndex(0xe0); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x1a); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x18); 
    lcd_writeData(0x2f); 
    lcd_writeData(0x28); 
    lcd_writeData(0x20); 
    lcd_writeData(0x22); 
    lcd_writeData(0x1f); 
    lcd_writeData(0x1b); 
    lcd_writeData(0x23); 
    lcd_writeData(0x37); 
    lcd_writeData(0x00); 	
    lcd_writeData(0x07); 
    lcd_writeData(0x02); 
    lcd_writeData(0x10); 
    
    lcd_writeIndex(0xe1); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x1b); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x17); 
    lcd_writeData(0x33); 
    lcd_writeData(0x2c); 
    lcd_writeData(0x29); 
    lcd_writeData(0x2e); 
    lcd_writeData(0x30); 
    lcd_writeData(0x30); 
    lcd_writeData(0x39); 
    lcd_writeData(0x3f); 
    lcd_writeData(0x00); 
    lcd_writeData(0x07); 
    lcd_writeData(0x03); 
    lcd_writeData(0x10);  
    
    lcd_writeIndex(0x2a);
    lcd_writeData(0x00);
    lcd_writeData(0x00+2);
    lcd_writeData(0x00);
    lcd_writeData(0x80+2);
    
    lcd_writeIndex(0x2b);
    lcd_writeData(0x00);
    lcd_writeData(0x00+3);
    lcd_writeData(0x00);
    lcd_writeData(0x80+3);
    
    lcd_writeIndex(0xF0); 
    lcd_writeData(0x01); 
    lcd_writeIndex(0xF6);
    lcd_writeData(0x00); 
    
    lcd_writeIndex(0x3A);
    lcd_writeData(0x05); 
    lcd_writeIndex(0x29);

    lcd_clear(WHITE);//全白
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶画点
//  @param      x     	        坐标x方向的起点
//  @param      y     	        坐标y方向的起点
//  @param      dat       	    需要显示的颜色
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_drawpoint(0,0,RED);  //坐标0,0画一个红色的点
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawpoint(uint16 x,uint16 y,uint16 color)
{
    lcd_set_region(x,y,x,y);
    lcd_writedata_16bit(color);
}

/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		lcd_drawpoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		lcd_drawpoint(x0-b,y0-a,color);             //3           
		lcd_drawpoint(x0+b,y0-a,color);             //0           
		lcd_drawpoint(x0-a,y0+b,color);             //1                
		lcd_drawpoint(x0-a,y0-b,color);             //2             
		lcd_drawpoint(x0+b,y0+a,color);             //4               
		lcd_drawpoint(x0+a,y0-b,color);             //5
		lcd_drawpoint(x0+a,y0+b,color);             //6 
		lcd_drawpoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//一个字符所占字节大小
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	lcd_set_region(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
		else if(sizey==24)temp=ascii_2412[num][i];		 //调用12x24字体
		else if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))lcd_writedata_16bit(fc);
				else lcd_writedata_16bit(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))lcd_drawpoint(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX-1）
//  @param      dat       	    需要显示的字符
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showchar(0,0,'x');//坐标0,0写一个字符x
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar(uint16 x,uint16 y,uint8 dat)
{
	uint8 i,j;
	uint8 temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region(x,y+i,x+7,y+i);
		temp = tft_ascii[dat-32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writedata_16bit(PENCOLOR);
			else			lcd_writedata_16bit(BGCOLOR);
			temp>>=1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符串
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符串
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void lcd_showstr(uint16 x,uint16 y,uint8 dat[],uint8_t len)
{
	uint16 j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		lcd_showchar(x+8*j,y,dat[j]);
		j++;
		if (j > len) 
			break;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位有符号
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint8(0,0,x);//x为int8类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint8(uint16 x,uint16 y,int8 dat)
{
	uint8 a[3];
	uint8 i;
	if(dat >= 0)
	{
		lcd_showchar(x,y*16,' ');
	}
	else	
	{
		lcd_showchar(x,y*16,'-');
		dat = -dat;
	}
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar(x+(8*(i+1)),y*16,'0' + a[i]);
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint8(0,0,x);//x为uint8类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint8(uint16 x,uint16 y,uint8 dat)
{
	uint8 a[3];
	uint8 i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar(x+(8*i),y,'0' + a[i]);
		i++;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位有符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint16(0,0,x);//x为int16类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint16(uint16 x,uint16 y,int16 dat)
{
	uint8 a[5];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar(x,y*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar(x+(8*(i+1)),y*16,'0' + a[i]);
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint16(0,0,x);//x为uint16类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint16(uint16 x,uint16 y,uint16 dat)
{
	uint8 a[5];
	uint8 i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar(x+(8*i),y*16,'0' + a[i]);
		i++;
	}
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      显示40*40 QQ图片
//  @param      *p     			图像数组地址
//  @return     void
//  @since      v1.0
//  Sample usage:          
//-------------------------------------------------------------------------------------------------------------------
void showimage(const unsigned char *p) 
{
  	int i,j,k; 
	unsigned char picH,picL;
	lcd_clear(WHITE); //清屏  
	
	for(k=0;k<4;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			lcd_set_region(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				lcd_writedata_16bit(picH<<8|picL);  						
			 }	
		 }
	}		
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风(灰度摄像头)液晶显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @return     void
//  @since      v1.0
//  Sample usage:              
//  @note       图像的宽度如果超过液晶的宽度，则自动进行缩放显示。这样可以显示全视野
//-------------------------------------------------------------------------------------------------------------------
void lcd_displayimage032(uint8 *p, uint16 width, uint16 height) 
{
    uint32 i,j;
                
    uint16 color = 0;
	uint16 temp = 0;
	
    uint16 coord_x = 0;
    uint16 coord_y = 0;

    
    if(0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)//竖屏
    {
        coord_x = height>TFT_X_MAX?TFT_X_MAX:height;
        coord_y = width>TFT_Y_MAX?TFT_Y_MAX:width;

        for(j=0;j<coord_y;j++)
        {
            lcd_set_region(0,j,coord_x-1,j);
            for(i=0;i<coord_x;i++)
            {
                temp = *(p+i*width+j*width/coord_y);//读取像素点
                color=(0x001f&((temp)>>3))<<11;
                color=color|(((0x003f)&((temp)>>2))<<5);
                color=color|(0x001f&((temp)>>3));
                lcd_writedata_16bit(color); 
            }
        }
        
    }
    else//横屏
    {
        coord_x = width>TFT_X_MAX?TFT_X_MAX:width;
        coord_y = height>TFT_Y_MAX?TFT_Y_MAX:height;
        lcd_set_region(0,0,coord_x-1,coord_y-1);

        for(j=0;j<coord_y;j++)
        {
            for(i=0;i<coord_x;i++)
            {
                temp = *(p+j*width+i*width/coord_x);//读取像素点
                color=(0x001f&((temp)>>3))<<11;
                color=color|(((0x003f)&((temp)>>2))<<5);
                color=color|(0x001f&((temp)>>3));
                lcd_writedata_16bit(color); 
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风(灰度摄像头)液晶缩放显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @param      dis_width       图像显示宽度  0 -（TFT_X_MAX-1）
//  @param      dis_height      图像显示高度  0 -（TFT_Y_MAX-1）
//  @return     void
//  @since      v1.0
//  Sample usage:              
//  @note       图像的宽度如果超过液晶的宽度，则自动进行缩放显示。这样可以显示全视野
//-------------------------------------------------------------------------------------------------------------------
void lcd_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    uint32 i,j;
                
    uint16 color = 0;
	uint16 temp = 0;

    lcd_set_region(0,0,dis_width-1,dis_height-1);//设置显示区域 
    
    for(j=0;j<dis_height;j++)
    {
        for(i=0;i<dis_width;i++)
        {
            temp = *(p+(j*height/dis_height)*width+i*width/dis_width);//读取像素点
            color=(0x001f&((temp)>>3))<<11;
            color=color|(((0x003f)&((temp)>>2))<<5);
            color=color|(0x001f&((temp)>>3));
            lcd_writedata_16bit(color); 
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风(二值化摄像头)液晶显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @return     void
//  @since      v1.0
//  @note      	图像分辨率需要设置在120(高)*160(宽)以下       
//-------------------------------------------------------------------------------------------------------------------
void lcd_displayimage7725(uint8 *p, uint16 width, uint16 height) 
{
    int i,j; 
	
    uint16 temp = 0;
    lcd_set_region(0,0,width-1,height-1);
	for(i=0;i<height * (width/8);i++)
    {
        temp = *p;
        p++;
        for(j=0; j<8; j++)
        {
            if( (temp<<j)&0x80 )	lcd_writedata_16bit(WHITE);
            else					lcd_writedata_16bit(BLACK);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      汉字显示
//  @param      x       横坐标 0-（TFT_X_MAX-1）
//  @param      y       纵坐标 0-（TFT_Y_MAX-1）
//  @param      size    取模的时候设置的汉字字体大小，也就是一个汉字占用的点阵长宽为多少个点，取模的时候需要长宽是一样的。
//  @param      *p      需要显示的汉字数组
//  @param      number  需要显示多少位
//  @param      color   显示颜色
//  @return     void
//  @since      v1.0
//  Sample usage:		lcd_display_chinese(0,0,16,chinese_test[0],4,RED);//显示font文件里面的 示例
//  @Note       使用PCtoLCD2002软件取模		    阴码、逐行式、顺向   16*16
//-------------------------------------------------------------------------------------------------------------------
void lcd_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color)
{
    int i, j, k; 
    uint8 temp, temp1, temp2;
    const uint8 *p_data;
    
    temp2 = size/8;
    
    lcd_set_region(x,y,number*size-1+x,y+size-1);
    
    for(i=0;i<size;i++)
    {
        temp1 = number;
        p_data = p+i*temp2;
        while(temp1--)
        {
            for(k=0;k<temp2;k++)
            {
                for(j=8;j>0;j--)
                {
                    temp = (*p_data>>(j-1)) & 0x01;
                    if(temp)    lcd_writedata_16bit(color);
                    else        lcd_writedata_16bit(BGCOLOR);
                }
                p_data++;
            }
            p_data = p_data - temp2 + temp2*size;
        }   
    }
}



