#include <stc15.h>
#include <intrins.h>
#include <stdio.h>
#include ".\USART\USART.h"
#include ".\AD\ADzh.h"
#include ".\systick\systick.h"
#include ".\DHT11\DHT11.h"
#include ".\BH1750\BH1750.h"

sbit MD1 = P3^2;
sbit MD0 = P3^3;

char voltage[10],illumination[20];
char tem[10],hum[10];

void main()
{	
	InitADC();
	UartInit(); 
  Init_BH1750();       //初始化BH1750
	Delay1ms(1000);
	
	while(1) 
	{		
		Delay1ms(100);
	  MD1 = 1;
    MD0 = 0;			
    Delay1ms(100);
		PCON = 0X02;  //单片机进入掉电模式
    _nop_;
		_nop_;
		_nop_;
		
		/**************************************
		查询DHT11数据
		**************************************/
		Delay1ms(100);
		if(Dht11_ReadTemHumi() == 1)
		{
		  sprintf(tem,"%d\r\n",temp_value);
			sprintf(hum,"%d\r\n",humi_value);
		}
		/**************************************
		查询ADC数据  电池电压
		**************************************/
		Delay1ms(100);
		EADC = 1;		  //为避免冲突在使用ADC时在开启中断   
		sprintf(voltage,"%.3f\r\n",V);
		EADC = 0;     //为避免冲突不使用ADC时在关闭中断 
		
		/**************************************
		查询BH1750数据 光照强度
		**************************************/
		Delay1ms(100);
		Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode

    Delay1ms(180);              //延时180ms

    Multiple_Read_BH1750();       //连续读出数据，存储在BUF中

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//合成数据，即光照数据   
    temp=(float)dis_data/1.2;
		sprintf(illumination,"%.3f\r\n",temp);
		
	  MD1 = 0;
    MD0 = 0;	
		Delay1ms(100); 
		SendData(0X00);
		SendData(0X02);
		SendData(0X18);
		UartInit_fk(tem);             //温度
	  UartInit_fk(hum);             //湿度
		UartInit_fk(voltage);         //电池电压\2
		UartInit_fk(illumination);	  //光照强度
		
   
		if(V*2 < 6)
		{
			PCON = 0X02;  //单片机进入掉电模式
			ES=0;         //关闭所有中断 单片机不被唤醒
	    EA=0;
			EADC = 0;
			//单片机进入休眠模式不在发送数据
		}
	}
				

}



