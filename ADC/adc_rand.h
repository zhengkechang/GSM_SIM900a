#ifndef __ADC_RAND_H
#define __ADC_RAND_H
#include "sys.h"

void  Adc_Init(void);
u16 Get_Adc(u8 ch) ;
double Get_Adc_Average(u8 ch,u8 times);
void genRandomString(int length,char*string);

double temp_random(void);
int humi_random(void);
int Close_random(void);

#endif
