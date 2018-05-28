#include ".\systick\systick.h"


void Delay1ms(int n)		//@22.1184MHz
{
	unsigned char i, j;
	unsigned int k;
	
  for(k=0;k<n;k++)
	{
		_nop_();
	  _nop_();
	  i = 22;
	  j = 128;
	  do
	  {
	  	while (--j);
	  } while (--i);
	}	
}

void Delay1us(char n)		//@22.1184MHz
{
	unsigned char i;
	unsigned int j;

	for(j=0;j<n;j++)
	{
		i = 3;
	  while (--i);
	}	
}

