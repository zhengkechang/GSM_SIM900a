#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"		
#include "touch.h"	
#include "usart2.h"	
#include "sim900a.h"
#include "string.h"
#include "stdio.h"
#include "time.h"
#include <stdlib.h>//������ͷ�ļ�
#include "stm32f10x_adc.h"
#include "http.h"
#include "sim900a_init.h"
#include "adc_rand.h"
#include "sim900a_land.h"

extern void uart2_send(u8* buf,u32 num);

 int main(void)
 { 

	u8 ch = 0x1A; 
	double air_temp, fun_temp,room_temp;
	uint16_t room_humi,smoke_detector,room_door_isClose,cabinet_door_isClose,water_leakage;
	 
    char HTTP_Buf[1024];     //HTTP���ĳ���

    char air_tempStr[10];       //��������
	char fun_tempStr[10];
	char room_tempStr[10];
	char room_humiStr[5];
	char water_leakageStr[2];
	char smoke_detectorStr[2];
	char room_door_isCloseStr[2];
	char cabinet_door_isCloseStr[2];

	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600			 
	LCD_Init();				//��ʼ��Һ�� 
	LED_Init();         	//LED��ʼ��	 
	KEY_Init();				//������ʼ��	  													    
 	USART2_Init(115200);	//��ʼ������2 
	
	sim900a_send_cmd("AT+CIPSHUT", "OK", 1000);		//�ر���������
	
	Landing_Init(ID,NUM,JIAOBEN);					//��¼�豸
	printf("Landing_Init over\r\n");
	
	while(1)
	{
		
		
		air_temp=temp_random()/10;
		delay_ms(1000);
		fun_temp=temp_random();
		delay_ms(1000);
		room_temp=temp_random();

		room_humi=humi_random();
		
		water_leakage=Close_random();
		delay_ms(1000);
		smoke_detector=Close_random();
		room_door_isClose=Close_random();
		delay_ms(1000);
		cabinet_door_isClose=Close_random();
		
////////���÷���/////////////////////////////////////////////////////////////////////////////
		sim900a_send_cmd("AT+CIPSTART=1,\"TCP\",\"183.230.40.33\",\"80\"", "OK", 1000);
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
		sim900a_send_cmd("AT+CIPSEND=1", ">", 1000);	//����͸��ģʽ
		
        /* ת��Ϊ�ַ�����ʽ */
        sprintf(air_tempStr, ".%.1f", (float)air_temp);								
		sprintf(fun_tempStr,"%lf",fun_temp);
		sprintf(room_tempStr,"%lf",room_temp);
		sprintf(room_humiStr,"%d",room_humi);
		sprintf(water_leakageStr,"%d",water_leakage);
		sprintf(smoke_detectorStr,"%d",smoke_detector);
		sprintf(room_door_isCloseStr,"%d",room_door_isClose);
		sprintf(cabinet_door_isCloseStr,"%d",cabinet_door_isClose);
		
		HTTP_PostPkt
			(HTTP_Buf, API_KEY, DEV_ID,  
			"air_temp", "fun_temp","room_temp","room_humi",
			"water_leakage","smoke_detector",
			"room_door_isClose","cabinet_door_isClose",
			air_tempStr , fun_tempStr,room_tempStr , room_humiStr , 
			water_leakageStr , smoke_detectorStr , 
			room_door_isCloseStr , cabinet_door_isCloseStr ); //HTTP���
			
		uart2_send((u8*)HTTP_Buf,strlen(HTTP_Buf));

		uart2_send(&ch,1);

        printf("\r\n%s\r\n", HTTP_Buf);
		printf("%x",0x1A);

        delay_ms(1000);
		
        printf("rcv response:\r\n%s\r\n", USART2_RX_BUF);
		
		sim900a_send_cmd("AT+CIPCLOSE=1", "OK", 1000);
	
//////////////////������ϣ��رշ���//////////////////////////////////////////////////////		

/////////////////��¼����////////////////////////////////////////////////////////////////
	sim900a_send_cmd("AT+CIPSTART=2,\"TCP\",\"183.230.40.40\",1811", "ERROR", 1000);
	
	delay_ms(1000);
	delay_ms(1000);
	sim900a_send_cmd("AT+CIPSEND=2", ">", 1000);	//����͸��ģʽ
	
	//sprintf(LANDING_Buf,"*%d#%d#%s*",ID,NUM,JIAOBEN);
	
	u2_printf("*127734#0002#sample1*");
	
	uart2_send(&ch,1);
////////////////��¼���/////////////////////////////////////////////////////////////////

	}
	 
}





