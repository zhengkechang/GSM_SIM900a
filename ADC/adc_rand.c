#include "adc_rand.h"
#include "stm32f10x_adc.h"

//开启通道14（PC4）                                                                      
void  Adc_Init(void)
{    
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1    , ENABLE );      //使能IO口时钟，ADC1通道时钟
 
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //éè??ADC·??μòò×ó6 72M/6=12,ADC×?′óê±??2??ü3?1y14M
 
    //PC4 作为模拟输入                    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;        //模拟输入引脚
    GPIO_Init(GPIOC, &GPIO_InitStructure);   
 
 
    ADC_DeInit(ADC1);  //复位ADC1
 
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;    //ADC工作模式：独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;    //魔术转换工作在单通道
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;    //单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;    //转换有软件启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    //ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;    //顺序进行规则转换
    ADC_Init(ADC1, &ADC_InitStructure);    //根据ADC_InitStruct中指定 的参数初始化外设ADCx的寄存器  
 
 
    ADC_Cmd(ADC1, ENABLE);    //使能指定的ADC1
 
    ADC_ResetCalibration(ADC1);    //使能复位校准
 
    while(ADC_GetResetCalibrationStatus(ADC1));    //等待复位校准结束
 
    ADC_StartCalibration(ADC1);     //开启AD校准
 
    while(ADC_GetCalibrationStatus(ADC1));     //等待校准结束
 
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);        //使能指定的ADC1的软件转换启动功能
 
}       

u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

double Get_Adc_Average(u8 ch,u8 times)
{
float temp_val=0;
u8 t;
double num;

	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}

num=temp_val/times;
return num;
}  

void genRandomString(int length,char*string)
{
  int  i;
 srand(SystemCoreClock); //将time_clock改成某个悬空adc值adcvalue也行 
  for (i = 0; i < length - 1; i++)
 {  
   rand()%3;
  
  }
  string[length - 1] = '\0';
}


double temp_random(void)
{
	double iSeed;
	double iRand;//

	Adc_Init();//ADC初始化

	iSeed=Get_Adc_Average(ADC_Channel_14,3);//通过模拟输入获取悬空引脚的电平产生随机种子
	srand(iSeed);
	iRand=(float)(rand()%10);//产生随机数0~92////22-32
	
	return iRand;


}
int humi_random(void)
{
	
	u16 iSeed=0,iRand=0;//

	Adc_Init();//ADC初始化

	iSeed=Get_Adc_Average(ADC_Channel_14,3);//通过模拟输入获取悬空引脚的电平产生随机种子
	srand(iSeed);
	iRand=(u16)(rand()%30+40);//产生随机数0~9
	
	return iRand;



}

int Close_random(void)
{
	
	u16 iSeed=0,iRand=0;//

	Adc_Init();//ADC初始化

	iSeed=Get_Adc_Average(ADC_Channel_14,3);//通过模拟输入获取悬空引脚的电平产生随机种子
	srand(iSeed);
	iRand=(u16)(rand()%1);//产生随机数0~9
	
	return iRand;
}


