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
void  Single_Write_BH1750(uchar REG_Address);               //单个写入数据
void  Multiple_Read_BH1750();                               //连续的读取内部寄存器数据
//------------------------------------
void BH1750_Start();                    //起始信号
void BH1750_Stop();                     //停止信号
void BH1750_SendACK(bit ack);           //应答ACK
bit  BH1750_RecvACK();                  //读ack
void BH1750_SendByte(uchar dat);        //IIC单个字节写
uchar BH1750_RecvByte();                //IIC单个字节读


void Init_BH1750(void);


//-----------------------------------

#endif