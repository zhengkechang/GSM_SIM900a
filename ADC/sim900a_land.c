#include "sim900a_land.h"
#include "sys.h"
#include "sim900a.h"
#include "usart2.h"
void Landing_Init(int id,int num,char *jiaoben )
{
	
//	char LANDING_Buf[200];
	u8 ch = 0x1A;
	
	sim900a_send_cmd("AT", "OK", 1000);		//模块有效性检查
	USART2_RX_STA = 0;
	
	

//    SendCmd(CWMODE, "OK", 1000);	//模块工作模式
//    SendCmd(RST, "OK", 2000);		//模块重置
//    SendCmd(CIFSR, "OK", 1000);		//查询网络信息
//    SendCmd(CWJAP, "OK", 2000);		//配置需要连接的WIFI热点SSID和密码
//    SendCmd(CIPSTART, "OK", 2000);	//TCP连接
	sim900a_send_cmd("AT+CGCLASS=\"B\"", "OK", 1000);
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CGDCONT=1,\"IP\",\"CMNET\"", "OK", 1000);
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CGATT=1", "OK", 1000);
	USART2_RX_STA = 0;		
	sim900a_send_cmd("AT+CIPCSGP=1,\"CMNET\"", "OK", 1000);
	USART2_RX_STA = 0;
	
/////////多路连接////////////////////////////////////////////////////////////
	sim900a_send_cmd("AT+CIPMUX=1", "OK", 1000);						/////
	sim900a_send_cmd("AT+CSTT=\"CNMET\",\"KC\",\"123\"","OK", 1000);	/////
	sim900a_send_cmd("AT+CIICR","OK", 1000);							/////
	sim900a_send_cmd("AT+CIFSR", "", 1000);								/////
/////////////////////////////////////////////////////////////////////////////
	
	
//	sim900a_send_cmd("AT+CLPORT=\"TCP\",2002", "OK",1000);
	
	sim900a_send_cmd("AT+CIPSTART=2,\"TCP\",\"183.230.40.40\",1811", "OK", 1000);
	
//	if(sim900a_send_cmd("AT+CGCLASS=\"B\"","OK",100))return 1;				//设置GPRS移动台类别为B,支持包交换和数据交换 
//	if(sim900a_send_cmd("AT+CGDCONT=1,\"IP\",\"CMNET\"","OK",500))return 2;//设置PDP上下文,互联网接协议,接入点等信息
//	if(sim900a_send_cmd("AT+CGATT=1","OK",500))return 3;					//附着GPRS业务
//	//if(sim900a_send_cmd("AT+CIPCSGP=1,\"CMNET\"","OK",500))return 4;	 	//设置为GPRS连接模式
//	if(sim900a_send_cmd("AT+CLPORT=\"TCP\",\"2000\"", "OK",1000))return 4;
//	if(sim900a_send_cmd("AT+CIPSTART=\"TCP\",\"183.230.40.33\",\"80\"", "OK", 3000))return 5;
	USART2_RX_STA = 0;
	
	while(1)
	{
		if(USART2_RX_STA & (0x8000))
		{
			printf("%s\r\n",USART2_RX_BUF);
			break;
		}
	}
	USART2_RX_STA = 0;
	delay_ms(1000);
	delay_ms(1000);
	sim900a_send_cmd("AT+CIPSEND=2", ">", 1000);	//进入透传模式
	
	//sprintf(LANDING_Buf,"*%d#%d#%s*",ID,NUM,JIAOBEN);
	
	u2_printf("*127734#0002#sample1*");
	//uart2_send((u8*)LANDING_Buf,strlen(LANDING_Buf));
	
	uart2_send(&ch,1);

}
