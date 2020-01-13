#ifndef __HTTP_H
#define __HTTP_H
#include "sys.h"

#define API_KEY     "tpbCanP4sZQ7t=rPkw7q=RodyZc="		//API
#define DEV_ID      "28341104"							//…Ë±∏ID

uint32_t HTTP_PostPkt(char *pkt, char *key, char *devid, 
	char * air_temp,char * fun_temp,char * room_temp,
		char *room_humi,char *water_leakage,
			char *smoke_detector,char *room_door_isClose,char *cabinet_door_isClose,
	char *air_tempStr,char *fun_tempStr,char *room_tempStr,
		char *room_humiStr,char *water_leakageStr,
			char *smoke_detectorStr,char *room_door_isCloseStr,char *cabinet_door_isCloseStr);
		


#endif 
