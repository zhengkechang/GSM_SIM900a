#include "sim900a_init.h"

void SIM900A_Init(void)
{
#if 1
	sim900a_send_cmd("AT", "OK", 1000);		//模块有效性检查
	USART2_RX_STA = 0;
//	sim900a_send_cmd("AT+CIPSHUT", "OK", 1000);	
//    SendCmd(CWMODE, "OK", 1000);	//模块工作模式
//    SendCmd(RST, "OK", 2000);		//模块重置
//    SendCmd(CIFSR, "OK", 1000);		//查询网络信息
//    SendCmd(CWJAP, "OK", 2000);		//配置需要连接的WIFI热点SSID和密码
//    SendCmd(CIPSTART, "OK", 2000);	//TCP连接
	
	
//	sim900a_send_cmd("AT+CGCLASS=\"B\"", "OK", 1000);
//	USART2_RX_STA = 0;
//	sim900a_send_cmd("AT+CGDCONT=1,\"IP\",\"CMNET\"", "OK", 1000);
//	USART2_RX_STA = 0;
//	sim900a_send_cmd("AT+CGATT=1", "OK", 1000);
//	USART2_RX_STA = 0;		
//	sim900a_send_cmd("AT+CIPCSGP=1,\"CMNET\"", "OK", 1000);
//	USART2_RX_STA = 0;
	
	
//	sim900a_send_cmd("AT+CLPORT=\"TCP\",2000", "OK",1000);
	
	sim900a_send_cmd("AT+CIPSTART=1,\"TCP\",\"183.230.40.33\",80", "OK", 1000);

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
	
//	sim900a_send_cmd("AT+CIPSEND", ">", 1000);	
	
//	sim900a_send_cmd("AT+CIPMODE?", "OK", 1000);

//	sim900a_send_cmd("AT+CIPMODE=1", "OK", 1000);	//进入透传模式

#endif
}