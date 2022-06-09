#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f4xx.h"
/********************************** ͷ�ļ������� **********************************/

#include "esp8266.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "usart.h"
/************************************* END *****************************************/


/********************************** �û���Ҫ���õĲ���**********************************/
//�ĳ����Լ���
#define      macUser_ESP8266_ApSsid                      "Redmi K40"        //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                       "h123456."         //Ҫ���ӵ��ȵ����Կ

//��֪������ IP ��˿�
#define      macUser_ESP8266_TcpServer_IP                "api.seniverse.com"    //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port              "80"              //Ҫ���ӵķ������Ķ˿�

//��ѯ�������
//��˽Կ������ģ�key=SBk0nHXcaAPbDC9L9
//��ѯ�ĳ���Ҳ���������ѯ��: location=zhengzhou
#define REQUEST_DATA   "GET https://api.seniverse.com/v3/weather/now.json?key=SBk0nHXcaAPbDC9L9&location=zhengzhou&language=zh-Hans&unit=c\r\n"


/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** ���Ժ������� ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
//�˺����ŵ���ѭ����
void ESP8266_CheckRecvDataTest(void);

#endif

