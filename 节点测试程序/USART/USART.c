#include ".\USART\USART.h"



void UartInit(void)		//115200bps@22.1184MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xD0;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	ES=1;
	EA=1;
}


void UartInit_fk(char *buf1)    //����1���ͺ���
{  unsigned char i=0;
   while (1)
   {  if (buf1[i]!=0)
     {  
	 	SBUF=buf1[i];       //����һ��byte������
        while(TI==0);      //�ȴ����ͽ���
		TI=0;
        i++;
     }
     else return;
   }   
}

/************************����1�жϺ���***********************/
void UART1_Routine() interrupt 4
{
	
	if(RI==1)
	{
		RI = 0;
	}
	
}




