#include <stc15.h>
#include ".\DHT11\DHT11.h"
#include <intrins.h>
#include ".\systick\systick.h"

#define NUM 254
#define SIZE 5

static unsigned char status;
static unsigned char value_array[SIZE];
int temp_value=0,humi_value=0;


static unsigned char Dht11_ReadValue(void)
{
	unsigned char count,value=0,i;
	status = OK;   //设定标志为正常状态
	for(i=0;i<8;i++)
	{
		//高位在先
		value<<=1;
    count=0;
		//每一位数据前会有一个50us的低电平时间，等待50us低电平结束
		while(dht11==0&&count++<NUM);
		if(count>=NUM)
		{
			status=ERROR;   //设定错误标志
			return 0;   //函数执行过程发生错误就退出函数
		}
		//26-28us的高电平表示该位是0，若70us高电平表示该位是1
		Delay1us(30);
		//延时30us后检测数据线是否还是高电平
		if(dht11==1)
		{
			//表示该位是1
			value++;
			//等待剩余高电平时间结束
			while(dht11==1&&count++<NUM)  dht11=1;
			if(count>=NUM)
		  {
		  	status=ERROR;   
		  	return 0;   
		  }			
		}		
	}
	return (value);
}

//读温度和湿度函数，读一次的数据共五字节，读出成功函数返回OK，错误返回ERROR
extern unsigned char Dht11_ReadTemHumi(void)
{
	unsigned char i=0,check_value=0,count=0;

	//拉低数据线大于18ms发送开始信号
	dht11=0;
  Delay1ms(20);	
	dht11=1;   //释放数据总线，用于检测低电平的应答信号
	//延时20-40us，等待一段时间后检测应答信号，应答信号是从拉低数据线80us
	Delay1us(40);
	//检测应答信号，应答信号是低电平
	if(dht11!=0)   
	{
		//无应答
		return ERROR;
	}
	else   //有应答
	{		
		while(dht11==0&&count++<NUM);   //等待应答信号结束

		if(count>=NUM)  //检测计数器是否超过了设定的范围
		{
			dht11=1;
			return ERROR;   //读数据出错，退出函数
		}

		count=0;
		dht11=1;   //释放数据总线
		//应答信号后会有一个80us的高电平，等待高电平结束
		while(dht11!=0&&count++<NUM);
		if(count>=NUM)  //检测计数器是否超过了设定的范围
		{
			dht11=1;
			count=0;
			return ERROR;   //退出函数
		}
		
		//读出湿、温度值
		for(i=0;i<SIZE;i++)
		{
			value_array[i]=Dht11_ReadValue();
			if(status==ERROR)   //调用Dht11_ReadValue()读数据出错会设定status为ERROR
			{
				dht11=1;
				return ERROR;
			}
			//读出的最后一个值是校验值，不需要加上去
			if(i!=SIZE-1)
			{
				check_value+=value_array[i];
			}
		}  
		//在没有发生函数调用失败时进行校验
		if(check_value==value_array[SIZE-1])
		{
			humi_value=value_array[0];
			temp_value=value_array[2];
			dht11=1;
			return OK;   //正确的读出dht11输出的数据
		}
		else
		{
			return ERROR;
		}
	}
}









