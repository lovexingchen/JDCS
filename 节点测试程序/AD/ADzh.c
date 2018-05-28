#include "ADzh.h"
#include ".\systick\systick.h"

#define ADC_POWER  0X80
#define ADC_SPEEDLL 0X00
#define ADC_START 0X08
#define ADC_FLAG 0X10

float V=0.0;

void InitADC()
{
		P1ASF=0X20;
		ADC_RES=0;
		ADC_CONTR=ADC_POWER|ADC_SPEEDLL|ADC_START|5;
    Delay1ms(100);
}


void  adc_isr()  interrupt 5  using 1
{
		ADC_CONTR&=!ADC_FLAG;
	  V=(ADC_RES*5.1)/256;  //实测电压值100倍
//		if(++ch>7)	ch=0;         //检查八位通道
		ADC_CONTR=ADC_POWER|ADC_SPEEDLL|ADC_START|5;		
}









