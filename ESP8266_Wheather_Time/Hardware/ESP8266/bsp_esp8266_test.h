#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f4xx.h"
/********************************** 头文件包含区 **********************************/

#include "esp8266.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "usart.h"
#include "SEEKFREE_18TFT.h"
#include "rtc.h"
#include "key.h"
/************************************* END *****************************************/


/********************************** 用户需要设置的参数**********************************/
//改成你自己的
// #define      macUser_ESP8266_ApSsid                      "Redmi K40"        //要连接的热点的名称
// #define      macUser_ESP8266_ApPwd                       "h123456."         //要连接的热点的密钥

//心知天气的 IP 与端口
#define      macUser_ESP8266_TcpServer_IP                "api.seniverse.com"    //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port              "80"                   //要连接的服务器的端口

//获取时间的服务器
#define     macUser_ESP8266_TIME_IP                      "api.k780.com"
#define     macUser_ESP8266_TIME_Port                    "80"
//查询时间
#define   REQUEST_TIME   "GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json\r\n"

//查询天气情况
//将私钥换成你的：key=SBk0nHXcaAPbDC9L9
//查询的城市也换成你想查询的: location=zhoukou
#define REQUEST_DATA   "GET https://api.seniverse.com/v3/weather/now.json?key=SBk0nHXcaAPbDC9L9&location=zhoukou&language=en&unit=c\r\n"


/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;

extern RTC_TimeTypeDef getTime;
extern RTC_DateTypeDef getDate;

/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
//此函数放到主循环中
void ESP8266_CheckRecvDataTest(void);

//在LCD屏幕上显示出来
void LCD_display_weather(void);

//显示时钟
void lcd_dispaly_rtc(void);


//选择连接的Wifi
uint8_t select_wifi(void);

void analytical_data(void);

void analytical_time(void);

//更新数据
void updata_time(void);

void updata_weather(void);

#endif

