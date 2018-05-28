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
  Init_BH1750();       //��ʼ��BH1750
	Delay1ms(1000);
	
	while(1) 
	{		
		Delay1ms(100);
	  MD1 = 1;
    MD0 = 0;			
    Delay1ms(100);
		PCON = 0X02;  //��Ƭ���������ģʽ
    _nop_;
		_nop_;
		_nop_;
		
		/**************************************
		��ѯDHT11����
		**************************************/
		Delay1ms(100);
		if(Dht11_ReadTemHumi() == 1)
		{
		  sprintf(tem,"%d\r\n",temp_value);
			sprintf(hum,"%d\r\n",humi_value);
		}
		/**************************************
		��ѯADC����  ��ص�ѹ
		**************************************/
		Delay1ms(100);
		EADC = 1;		  //Ϊ�����ͻ��ʹ��ADCʱ�ڿ����ж�   
		sprintf(voltage,"%.3f\r\n",V);
		EADC = 0;     //Ϊ�����ͻ��ʹ��ADCʱ�ڹر��ж� 
		
		/**************************************
		��ѯBH1750���� ����ǿ��
		**************************************/
		Delay1ms(100);
		Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode

    Delay1ms(180);              //��ʱ180ms

    Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//�ϳ����ݣ�����������   
    temp=(float)dis_data/1.2;
		sprintf(illumination,"%.3f\r\n",temp);
		
	  MD1 = 0;
    MD0 = 0;	
		Delay1ms(100); 
		SendData(0X00);
		SendData(0X02);
		SendData(0X18);
		UartInit_fk(tem);             //�¶�
	  UartInit_fk(hum);             //ʪ��
		UartInit_fk(voltage);         //��ص�ѹ\2
		UartInit_fk(illumination);	  //����ǿ��
		
   
		if(V*2 < 6)
		{
			PCON = 0X02;  //��Ƭ���������ģʽ
			ES=0;         //�ر������ж� ��Ƭ����������
	    EA=0;
			EADC = 0;
			//��Ƭ����������ģʽ���ڷ�������
		}
	}
				

}



