#include <stc15.h>
#include <intrins.h>
#include <stdio.h>
#include ".\USART\USART.h"
#include ".\AD\ADzh.h"
#include ".\systick\systick.h"
#include ".\DHT11\DHT11.h"
#include ".\BH1750\BH1750.h"

char voltage[10],illumination[20];
char tem[10],hum[10];

void main()
{	
//	P3M0 |= 0X40;
//  P3M1 |= 0X00;
	
	
	InitADC();
	UartInit(); 
  Init_BH1750();       //��ʼ��BH1750
	Delay1ms(1000);
	
	while(1) 
	{		
		Delay1ms(500);
		UartInit_fk("�����������ģʽ\r\n");
		PCON = 0X02;  //��Ƭ���������ģʽ
    _nop_;
		_nop_;
		_nop_;
		
		/**************************************
		��ѯDHT11����
		**************************************/
		Delay1ms(500);
		if(Dht11_ReadTemHumi() == 1)
		{
		  sprintf(tem,"%d\r\n",temp_value);
			sprintf(hum,"%d\r\n",humi_value);
			UartInit_fk(tem);
			UartInit_fk(hum);
		}
		else UartInit_fk("DHT11��ѯʧ��\r\n");
		
		/**************************************
		��ѯADC����  ��ص�ѹ
		**************************************/
		Delay1ms(500);
		EADC = 1;		  //Ϊ�����ͻ��ʹ��ADCʱ�ڿ����ж�   
		sprintf(voltage,"%.3f\r\n",V);
	  UartInit_fk(voltage);
		EADC = 0;     //Ϊ�����ͻ��ʹ��ADCʱ�ڹر��ж� 
		
		/**************************************
		��ѯBH1750���� ����ǿ��
		**************************************/
		Delay1ms(500);
		Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode

    Delay1ms(180);              //��ʱ180ms

    Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//�ϳ����ݣ�����������   
    temp=(float)dis_data/1.2;
		sprintf(illumination,"%.3f\r\n",temp);
		UartInit_fk(illumination);	
		
		if(V*2 < 6)
		{
			
			//��Ƭ����������ģʽ���ڷ�������
		}
	}
				

}



