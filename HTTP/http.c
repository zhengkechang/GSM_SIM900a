#include "http.h"
#include "string.h"
#include "stdio.h"

uint32_t HTTP_PostPkt
(char *pkt, char *key, char *devid, 
	char *air_temp, char *fun_temp,char *room_temp,
		char *room_humi,char *water_leakage,
			char *smoke_detector,char *room_door_isClose,char *cabinet_door_isClose,
	char *air_tempStr,char *fun_tempStr,char *room_tempStr,
		char *room_humiStr,char *water_leakageStr,
			char *smoke_detectorStr,char *room_door_isCloseStr,char *cabinet_door_isCloseStr)
{
    char dataBuf[1024] = {0};
    char lenBuf[10] = {0};
    *pkt = 0;

    sprintf(dataBuf, "{\"datastreams\":\
	[{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
		{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
			{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
				{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
					{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
						{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
							{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},\
								{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]}]}",
		air_temp, air_tempStr,//浮点数
			fun_temp,fun_tempStr, //浮点数
				room_temp,room_tempStr, //浮点数
					room_humi,room_humiStr, 
						smoke_detector,smoke_detectorStr, 
							room_door_isClose,room_door_isCloseStr, 
								cabinet_door_isClose,cabinet_door_isCloseStr ,
									water_leakage,water_leakageStr); 

    //采用分割字符串格式:type = 5
    sprintf(lenBuf, "%d", strlen(dataBuf));

    strcat(pkt, "POST /devices/");
    strcat(pkt, devid);
    strcat(pkt, "/datapoints HTTP/1.1\r\n");

    strcat(pkt, "api-key:");
    strcat(pkt, key);
    strcat(pkt, "\r\n");

    strcat(pkt, "Host:api.heclouds.com\r\n");

    strcat(pkt, "Content-Length:");
    strcat(pkt, lenBuf);
    strcat(pkt, "\r\n\r\n");

    strcat(pkt, dataBuf);
	strcat(pkt, "\r\n");

    return strlen(pkt);
}
