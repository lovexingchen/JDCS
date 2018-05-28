#include ".\USART\USART.h"



void UartInit(void)		//115200bps@22.1184MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0xD0;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
	ES=1;
	EA=1;
}


void UartInit_fk(char *buf1)    //串口1发送函数
{  unsigned char i=0;
   while (1)
   {  if (buf1[i]!=0)
     {  
	 	SBUF=buf1[i];       //发送一个byte到串口
        while(TI==0);      //等待发送结束
		TI=0;
        i++;
     }
     else return;
   }   
}

/************************串口1中断函数***********************/
void UART1_Routine() interrupt 4
{
	
	if(RI==1)
	{
		RI = 0;
	}
	
}




