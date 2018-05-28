#ifndef __BH1750_H__
#define __BH1750_H__

#include <stc15.h>
#include ".\systick\systick.h"
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>


#define   uchar unsigned char
#define   uint unsigned int	
	
extern float  temp;
extern int    dis_data;	
extern uchar  BUF[8];

void  conversion(uint temp_data);
void  Single_Write_BH1750(uchar REG_Address);               //����д������
void  Multiple_Read_BH1750();                               //�����Ķ�ȡ�ڲ��Ĵ�������
//------------------------------------
void BH1750_Start();                    //��ʼ�ź�
void BH1750_Stop();                     //ֹͣ�ź�
void BH1750_SendACK(bit ack);           //Ӧ��ACK
bit  BH1750_RecvACK();                  //��ack
void BH1750_SendByte(uchar dat);        //IIC�����ֽ�д
uchar BH1750_RecvByte();                //IIC�����ֽڶ�


void Init_BH1750(void);


//-----------------------------------

#endif