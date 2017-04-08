#include <STC12C5A60S2.H>
#include "HarryBoard2.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

void handInHand();
void chess();

sbit INPUT_06 = P0^6; //手牵手的输入
sbit OUTPUT_10 = P1^0;//手牵手正确之后输出 继电器柜门和激光切换

void init()
{
	INPUT_06 = 0;
	OUTPUT_10 = 1;
}

void main()
{
	init();
	uart_init();
	mp3_init();
	
	delay_ms(5000);
	playMp3(MUSIC_INDOOR);
	
	while(1)
	{
		switch(step)
		{
			case 0:
				handInHand();
				break;
			case 1:
				chess();
				break;
		}
	}
}

void handInHand()
{
	if(INPUT_06 == 1)
	{
		delay_ms(500);
		if(INPUT_06 == 1)
		{
			OUTPUT_10 = 0;
			playMp3(MUSIC_HANDINHAND_CORRECT);
			setStep(1);
		}
	}
}

void chess()
{
	
}