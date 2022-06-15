#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f4xx.h"
/********************************** ͷ�ļ������� **********************************/

#include "esp8266.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "usart.h"
#include "SEEKFREE_18TFT.h"
#include "rtc.h"
#include "key.h"
/************************************* END *****************************************/


/********************************** �û���Ҫ���õĲ���**********************************/
//�ĳ����Լ���
// #define      macUser_ESP8266_ApSsid                      "Redmi K40"        //Ҫ���ӵ��ȵ������
// #define      macUser_ESP8266_ApPwd                       "h123456."         //Ҫ���ӵ��ȵ����Կ

//��֪������ IP ��˿�
#define      macUser_ESP8266_TcpServer_IP                "api.seniverse.com"    //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port              "80"                   //Ҫ���ӵķ������Ķ˿�

//��ȡʱ��ķ�����
#define     macUser_ESP8266_TIME_IP                      "api.k780.com"
#define     macUser_ESP8266_TIME_Port                    "80"
//��ѯʱ��
#define   REQUEST_TIME   "GET http://api.k780.com:88/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json\r\n"

//��ѯ�������
//��˽Կ������ģ�key=SBk0nHXcaAPbDC9L9
//��ѯ�ĳ���Ҳ���������ѯ��: location=zhoukou
#define REQUEST_DATA   "GET https://api.seniverse.com/v3/weather/now.json?key=SBk0nHXcaAPbDC9L9&location=zhoukou&language=en&unit=c\r\n"


/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;

extern RTC_TimeTypeDef getTime;
extern RTC_DateTypeDef getDate;

/********************************** ���Ժ������� ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
//�˺����ŵ���ѭ����
void ESP8266_CheckRecvDataTest(void);

//��LCD��Ļ����ʾ����
void LCD_display_weather(void);

//��ʾʱ��
void lcd_dispaly_rtc(void);


//ѡ�����ӵ�Wifi
uint8_t select_wifi(void);

void analytical_data(void);

void analytical_time(void);

//��������
void updata_time(void);

void updata_weather(void);

#endif

