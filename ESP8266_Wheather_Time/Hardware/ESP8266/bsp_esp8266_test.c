/**
 * @Revision:               V1.0
 * @author:                 点灯大师
 * @Affiliated unit：       黄河科技学院
 * @Email:                  im_leihao@163.com
 * @github:                 https://github.com/zleihao
 * @note                    bilibili视频:https://www.bilibili.com/video/BV1mA4y1R7bC
 */

#include "bsp_esp8266_test.h"
#include "math.h"

volatile uint8_t ucTcpClosedFlag = 0;
bool IP_Status = true;  			//true: 连接到服务器 api.k780.com  false: 连接到心知天气
bool updata_time_status = false;   //是否按下按键更新时间
bool updata_weather_status = false;   //是否按下按键更新时间

RTC_TimeTypeDef getTime;
RTC_DateTypeDef getDate;
//用来校准时间
RTC_TimeTypeDef caliTime;

//解析后的数据，后续开发时可以直接用这些值
typedef struct Date
{
	char text_city[10];   //城市
	char text_weather[10];    //天气
	char text_temp[10];    //温度
	char text_date[30];   //日期
	char text_time[10];   //时间
}WEATHER_InitTypeDef;

WEATHER_InitTypeDef WEATHER_InitStruct;

/******************************************************************
*    !!!!! 注意：ESP8266 接收到的数据存储在数组 strEsp8266_Fram_Record .Data_RX_BUF 中，
*               需要解析数据，并做出对应的操作
******************************************************************/


/****************************************************************************/
/**
 * @brief  连接到心知天气服务器
 * @param  null
 * @return null
 */
void esp8266_link_seniverse() {
	printf( "\r\n正在连接服务器 ......\r\n" );
	while( !ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );

  	printf( "\r\n进入透传发送模式 ....\r\n" );
	while( ! ESP8266_UnvarnishSend () );	
	IP_Status = false;    //更新一个连接状态
}

/**
 * @brief  连接到时间获取服务器
 * @param  null
 * @return null
 */
void esp8266_link_time(void) {
/********************连接服务器**********************************************************/
  	printf( "\r\n正在连接服务器 ......\r\n" );
	while( !ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TIME_IP, macUser_ESP8266_TIME_Port, Single_ID_0 ) );

  	printf( "\r\n进入透传发送模式 ....\r\n" );
	while( ! ESP8266_UnvarnishSend () );	
	IP_Status = true;         //更新一个连接状态
}

/**
 * @brief  更新时间
 * @param  null
 * @return null
 * @note   先判断一下此时连接的服务器是否为api.k780.com
 * 		   如果是则不需要重新连接服务器
 */
void updata_time(void) {
	if (IP_Status == false) 
	{
		ESP8266_ExitUnvarnishSend ();    						//退出透传模式，进入AT指令
		while (! ESP8266_Cmd("AT+CIPCLOSE","OK",NULL,500) );    //关闭当前所连接的服务器
		while( ! ESP8266_Enable_MultipleId ( DISABLE ) );       //禁止多连接
		esp8266_link_time();
	}
}

/**
 * @brief  更新天气
 * @param  null
 * @return null
 * @note   先判断一下此时连接的服务器是否为心知天气
 * 		   如果是则不需要重新连接服务器
 */
void updata_weather(void) {
	if (IP_Status == true) {
		ESP8266_ExitUnvarnishSend ();    						//退出透传模式，进入AT指令
		while (! ESP8266_Cmd("AT+CIPCLOSE","OK",NULL,500) );    //关闭当前所连接的服务器
		while( ! ESP8266_Enable_MultipleId ( DISABLE ) );       //禁止多连接
		esp8266_link_seniverse();
	}
}

/**
 * @brief  在LCD屏幕上显示天气信息
 * @param  无
 * @return 无 
 * @note   函数实现也就是按照像素点显示字符、汉字等等，这个过程很难受，快整吐了
 */
void LCD_display_weather(void) {
	uint8_t str[20];

	//显示城市信息
	lcd_display_chinese(0,96,16,chinese_test[0],2,RED);
	lcd_showchar(32,96,':');
	if (strcmp(WEATHER_InitStruct.text_city,"Zhengzhou") == 0) {
		lcd_display_chinese(48,96,16,chinese_test[32],2,RED);
	}
	else if (strcmp(WEATHER_InitStruct.text_city,"Zhoukou") == 0) {
		lcd_display_chinese(48,96,16,chinese_test[36],2,RED);
	}
	//显示天气信息
	lcd_display_chinese(0,112,16,chinese_test[8],2,RED);
	lcd_showchar(32,112,':');
	if (strcmp(WEATHER_InitStruct.text_weather,"Haze") == 0)
	{
		lcd_display_chinese(48,112,16,chinese_test[16],1,RED);
	}
	else if(strcmp(WEATHER_InitStruct.text_weather,"Overcast") == 0)
	{
		lcd_display_chinese(48,112,16,chinese_test[18],2,RED);
	}
	else if(strcmp(WEATHER_InitStruct.text_weather,"Light rain") == 0)
	{
		lcd_display_chinese(48,112,16,chinese_test[22],2,RED);
	}
	else if(strcmp(WEATHER_InitStruct.text_weather,"Cloudy") == 0)
	{
		lcd_display_chinese(48,112,16,chinese_test[26],2,RED);
	}
	else if(strcmp(WEATHER_InitStruct.text_weather,"Sunny") == 0)
	{
		lcd_display_chinese(48,112,16,chinese_test[30],1,RED);
	}
	else {
		lcd_display_chinese(48,112,16,chinese_test[30],1,RED);
	}
	//显示温度信息
	sprintf(str,"%sC",WEATHER_InitStruct.text_temp);
	lcd_display_chinese(0,128,16,chinese_test[4],2,RED);
	lcd_showchar(32,128,':');
	lcd_showstr(48,128,str,strlen(str));
	//显示日期
	lcd_display_chinese(0,144,16,chinese_test[12],2,RED);
	lcd_showchar(32,144,':');
	lcd_showstr(48,144,WEATHER_InitStruct.text_date,strlen(WEATHER_InitStruct.text_date));
}

/**
 * @brief  解析心知天气发送的信息
 * @param  null
 * @return null
 * @note   这是接收到的消息：{"results":[{"location":{"id":"WW0V9QP93VS8","name":"郑州","country":"CN","path":"郑州,郑州,河南,中国","timezone":"Asia/Shanghai","timezone_offset":"+08:00"},"now":{"text":"阴","code":"9","temperature":"29"},"last_update":"2022-05-21T11:20:10+08:00"}]}
 *         解析数据可以查看这篇文章: https://blog.csdn.net/m0_47329175/article/details/124896706
 */
void analytical_data(void) {
	char *str;
	//得到城市
	str = strstr(strEsp8266_Fram_Record.Data_RX_BUF,"name");
	str += 7;
	sscanf(str,"%[^\"]",WEATHER_InitStruct.text_city);
	printf("city: %s\n",WEATHER_InitStruct.text_city);
	//得到天气
	str = strstr(strEsp8266_Fram_Record.Data_RX_BUF,"text");
	str += 7;
	sscanf(str,"%[^\"]",WEATHER_InitStruct.text_weather);
	printf("temp: %s\n",WEATHER_InitStruct.text_weather);
	//得到温度 
	str = strstr(strEsp8266_Fram_Record.Data_RX_BUF,"temperature");
	str += 14;
	sscanf(str,"%[^\"]",WEATHER_InitStruct.text_temp);
	printf("temp: %s\n",WEATHER_InitStruct.text_temp);
	//得到日期 
	str = strstr(strEsp8266_Fram_Record.Data_RX_BUF,"last_update");
	str += 14;
	sscanf(str,"%[^T]",WEATHER_InitStruct.text_date);
	printf("temp: %s\n\n\n",WEATHER_InitStruct.text_date);

	LCD_display_weather();  //在LCD上显示出来
}

/**
 * @brief  解析api.k780.com发送的信息
 * @param  null
 * @return null
 * @note   这是接收到的消息：{"success":"1","result":{"timestamp":"1655027739","datetime_1":"2022-06-12 17:55:39","datetime_2":"2022年06月12日 17时55分39秒","week_1":"0","week_2":"星期日","week_3":"周日","week_4":"Sunday"}}
 *         解析数据可以查看这篇文章: https://blog.csdn.net/m0_47329175/article/details/124896706
 */
void analytical_time(void) {
	uint8_t *str_p;
	uint8_t str[20];
	str_p = strstr(strEsp8266_Fram_Record.Data_RX_BUF,"datetime_1");
	str_p += 13;
	sscanf(str_p, "%[^\"]",str);
	sscanf(str, "%*s %s",WEATHER_InitStruct.text_time);
	//校准时间
	sscanf(WEATHER_InitStruct.text_time,"%d:%d:%d",&caliTime.Hours,&caliTime.Minutes,&caliTime.Seconds);

	caliTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	caliTime.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&hrtc,&caliTime,RTC_FORMAT_BIN);
	
	//更新时间后，重新获取一下
	HAL_RTC_GetTime(&hrtc,&getTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&getDate,RTC_FORMAT_BIN);
	printf("%s\n",WEATHER_InitStruct.text_time);

}

/**
 * @brief  在LCD屏幕上显示时钟
 * @param  无
 * @return 无 
 * @note   与显示天气信息一样
 */
void lcd_dispaly_rtc(void) {
	uint8_t time_str[20];
	float x,y;

	//使用 CubeMx 生成的 RTC 代码需要时间、日期一同获取，要不时间会卡死
	HAL_RTC_GetTime(&hrtc,&getTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&getDate,RTC_FORMAT_BIN);

	sprintf(time_str,"%2d:%2d:%2d",getTime.Hours,getTime.Minutes,getTime.Seconds);
	//画个表盘，圆心(64,48)、半径40
	Draw_Circle(64,48,40,RED);
	lcd_drawpoint(64,48,BLACK);
	//12点、6点两条线
	LCD_DrawLine(64,8,64,18,BLACK);
	LCD_DrawLine(64,88,64,78,BLACK);
	//9点、3点两条线
	LCD_DrawLine(24,48,34,48,BLACK);
	LCD_DrawLine(104,48,94,48,BLACK);

	//在表盘中显示出时间
	lcd_showstr(32,40,time_str,strlen(time_str));
}

/**
 * @brief  连接wifi  
 * @param  i 连接哪一个
 * @return true 连接成功 
 * 		   false 连接失败，有可能密码不正确
 * @note   数组aps_list中存储的是查询到附近的wifi
 */
bool connect_to_wifi(uint8_t i) {
	uint8_t ApPwd[10];
	uint8_t connet_out_time = 0;  //连接超时计数

	//由于本人不会编写上位机，所以wifi密码是事先给出的
	if ( !strcmp(aps_list[i],"Redmi K40")) {
		sprintf(ApPwd,"%s","h123456.");
	}
	else if ( !strcmp(aps_list[i],"CMCC-HQaF")) {
		sprintf(ApPwd,"%s","pysup5qb");
	}
	else if ( !strcmp(aps_list[i],"pink_hyacinth")) {
		sprintf(ApPwd,"%s","15836285781");
	}

	do {
		connet_out_time++;
		HAL_Delay(1000);
		//5s 内没有连接成功，代表密码错误
		if (connet_out_time > 5) {
			return false;
		}
	}while( ! ESP8266_JoinAP ( aps_list[i], ApPwd ) );

	return true;
}

//选择连接的Wifi
uint8_t select_wifi(void) {
	static uint8_t index = 1;

	LCD_ShowString(20,0,"Select wifi",BLACK,WHITE,16,1);
	//画边框
	LCD_DrawLine(10,15,10,150,BLACK); //x 轴
	LCD_DrawLine(12,15,118,15,BLACK); //y 轴
	Draw_Circle(5,16*index+8,3,BLACK);
	LCD_Fill(0,0,10,15,YELLOW);
	//显示wifi
	lcd_showstr(12,16,aps_list[0],14);
	lcd_showstr(12,32,aps_list[1],14);
	lcd_showstr(12,48,aps_list[2],14);
	lcd_showstr(12,64,aps_list[3],14);
	lcd_showstr(12,80,aps_list[4],14);
	lcd_showstr(12,96,aps_list[5],14);
	lcd_showstr(12,112,aps_list[6],14);
	lcd_showstr(12,128,aps_list[7],14);

	if (KEY_Scan(1) == KEY1_PRES) {  //向下选择
		if (index < current_wifi_nums) {
			Draw_Circle(5,16*index+8,3,WHITE);   //清除上次的位置
			index++;
			Draw_Circle(5,16*index+8,3,BLACK);  //画出本次所在的位置
			return false;
		}
		else {
			return false;
		}
	}
	else if (KEY_Scan(1) == WKUP_PRES) { //向上选择
		if (index > 1) {
			Draw_Circle(5,16*index+8,3,WHITE);    //清除上次的位置
			index--;
			Draw_Circle(5,16*index+8,3,BLACK);    //画出本次所在的位置
			return false;
		}
		else {
			return false;
		}
	}
	else if (KEY_Scan(1) == KEY2_PRES) { //刷新wifi列表
		LCD_Fill(11,16,128,150,WHITE);
		while ( !ESP8266_ListAPs() );
		return false;
	}
	if (KEY_Scan(1) == KEY0_PRES) {  //连接wifi
		
		LCD_Fill(0,150,75,160,RED);
		LCD_Fill(0,0,128,150,WHITE);
		LCD_ShowString(5,60,"Link wifi ...",BLACK,WHITE,16,1);
		
		//连接失败
		if (!connect_to_wifi(index-1)) {
			LCD_Fill(0,0,128,160,RED);
			LCD_ShowString(0,40,"connet error",BLACK,WHITE,16,1);
			HAL_Delay(1000);
			LCD_Fill(0,0,128,160,WHITE);
			//连接失败，重新选择wifi
			select_wifi();
			return false;
		}
		else 
			return true; 
	}
}

/********************************************连接服务器*************************************************************************/

/**
  * @brief  ESP8266 StaTcpClient Unvarnish 配置测试函数
  * @param  无
  * @retval 无
  * @note   此函数首先测试AT指令、配置成STA模式(作客户端)、连接WIFI、
  *         禁止多连接、连接服务器、进入透传模式、开始透传(可以通过ESP8266向服务器发送请求)
  */
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
	bool res;
	printf( "\r\n正在配置 ESP8266 ......\r\n" );
	printf( "\r\n使能ESP8266 ......\r\n" );
	
	//测试esp8266
	LCD_Fill(0,150,25,160,RED);
	LCD_ShowString(5,60,"starting ...",BLACK,WHITE,16,1);
	macESP8266_CH_ENABLE();
	while( ! ESP8266_AT_Test() );
	
	//设置工作模式esp8266
	printf( "\r\n正在配置工作模式: STA ......\r\n" );
	LCD_Fill(0,150,50,160,RED);
	LCD_ShowString(5,60,"starting ...",BLACK,WHITE,16,1);
	while( ! ESP8266_Net_Mode_Choose ( STA ) );

	LCD_Fill(0,150,75,160,RED);
  	while ( !ESP8266_ListAPs() );
	LCD_Fill(0,0,128,150,WHITE);
	do {
		res = select_wifi();
	}while (res == false);

	//连接成功
	LCD_Fill(0,150,100,160,RED);
	printf("连接wifi成功\n");
	
  	printf( "\r\n禁止多连接 ......\r\n" );
	
	LCD_Fill(0,150,125,160,RED);
	LCD_Fill(0,0,128,150,WHITE);
	LCD_ShowString(5,60,"Load data ...",BLACK,WHITE,16,1);
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );

/********************连接服务器**********************************************************/
  	printf( "\r\n正在连接服务器 ......\r\n" );
	while( !ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TIME_IP, macUser_ESP8266_TIME_Port, Single_ID_0 ) );

  	printf( "\r\n进入透传发送模式 ....\r\n" );
	while( ! ESP8266_UnvarnishSend () );	
	printf( "\r\n配置 ESP8266 完毕\r\n" );
}

/*************************************************************************************************************************/

/**
  * @brief  ESP8266 检查是否接收到了数据，检查连接和掉线重连
  * @param  无
  * @retval 无
  */
void ESP8266_CheckRecvDataTest(void)
{
  uint8_t ucStatus;

	if( strEsp8266_Fram_Record .InfBit .FramFinishFlag )   //接收到数据
	{
		LL_USART_DisableIT_RXNE(macESP8266_USARTx);
		strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';

		//使用USART1将esp8266接收到的数据通过串口调试助手打印出来
		printf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);
		if (updata_time_status) {
			analytical_time();
			updata_time_status = false;
		}
		if (updata_weather_status) {
			analytical_data();
			updata_weather_status = false;
		}
		strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
		strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
		LL_USART_EnableIT_RXNE(macESP8266_USARTx);         //使能串口接收中断
	}

//   if ( ucTcpClosedFlag )                                             //检测是否失去连接
//   {
//     ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
//     do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
//     while ( ! ucStatus );
    
//     if ( ucStatus == 4 )                                             //确认失去连接后重连
//     {
//       //正在重连热点和服务器
//       printf ( "\r\nReconnecting to hotspot and server ......\r\n" );
      
//       while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
//       while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
//       //重连热点和服务器成功
//       printf ( "\r\nReconnect to hotspot and server successfully\r\n" );

//     }
    
//     while ( ! ESP8266_UnvarnishSend () );		
    
//   }
}

