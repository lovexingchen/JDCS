#ifndef __DHT11_H__
#define __DHT11_H__

extern int temp_value,humi_value;

sbit dht11=P3^6;

#define OK 1
#define ERROR 0

static unsigned char Dht11_ReadValue(void);
extern unsigned char Dht11_ReadTemHumi(void);
#endif