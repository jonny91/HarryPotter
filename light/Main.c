#include <STC89C5xRC.H>
#include "BackRoom.h"

void init()
{
	P00 = 1;
	P01 = 1;
	P02 = 1;
	P03 = 1;
	P04 = 1;
	P05 = 1;
	P06 = 1;
	P07 = 1;
}
void main()
{
	init();
	
	//7个灯 每个灯亮1秒钟循环 24247654
	while(1)
	{
		P02 = 0;
		delay_ms(1000);
		P02 = 1;
		
		P04 = 0;
		delay_ms(1000);
		P04 = 1;
		
		P02 = 0;
		delay_ms(1000);
		P02 = 1;
		
		P04 = 0;
		delay_ms(1000);
		P04 = 1;
		
		P07 = 0;
		delay_ms(1000);
		P07 = 1;
		
		P06 = 0;
		delay_ms(1000);
		P06 = 1;
		
		P05 = 0;
		delay_ms(1000);
		P05 = 1;
		
		P04 = 0;
		delay_ms(1000);
		P04 = 1;
	}
}