#include <STC12C5A60S2.H>
#include "HarryBoard1.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"


unsigned int step = 0;

sbit INPUT_DOOR_00 = P0^0; //开始的电磁锁门
sbit OUTPUT_DOOR_01 = P0^1; //竖琴正确 打开的门
sbit INPUT_LASER_02 = P0^2;//激光输入
sbit INPUT_LASER_03 = P0^3;//语音输入
sbit OUTPUT_DOOR_04 = P0^4;//下个房间的门

sbit INPUT_HARP_0 = P1^0; //do
sbit INPUT_HARP_1 = P1^1;	//re
sbit INPUT_HARP_2 = P1^2;	//mi
sbit INPUT_HARP_3 = P1^3;	//fa
sbit INPUT_HARP_4 = P1^4;	//so
sbit INPUT_HARP_5 = P1^5;	//la
sbit INPUT_HARP_6 = P1^6;	//si

void start();
void setStep(int s);
void harp();
void laser_and_say();

void main()
{
	init();
	uart_init();
	mp3_init();

	while(1)
	{
		switch(step)
		{
			case 0:
				start();
				break;
			case 1:
				//弹竖琴
				harp();
				break;
			case 2:
				laser_and_say();
				break;
			case 3:
				break;
		}
	}
}

void start()
{
	if(INPUT_DOOR_00 == 1)
	{
		delay_ms(8000);
		playMp3(MUSIC_INDOOR);
		setStep(1);		
	}
}

void harp()
{
	int answerLength = sizeof(HARP_ANSWER)/sizeof(char) - 1;
	unsigned int harpStep = 0;
	char selectHarp = 0;
	while(1)
	{
		if(INPUT_HARP_0 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_0 == 1)
			{
				selectHarp = DO;
				playMp3(MUSIC_DO);
				harpStep++;
			}
		}
		else if(INPUT_HARP_1 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_1 == 1)
			{
				selectHarp = RE;
				playMp3(MUSIC_RE);
				harpStep++;
			}
		}
		else if(INPUT_HARP_2 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_2 == 1)
			{
				selectHarp = MI;
				playMp3(MUSIC_MI);
				harpStep++;
			}
		}
		else if(INPUT_HARP_3 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_3 == 1)
			{
				selectHarp = FA;
				playMp3(MUSIC_FA);
				harpStep++;
			}
		}
		else if(INPUT_HARP_4 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_4 == 1)
			{
				selectHarp = SO;
				playMp3(MUSIC_SO);
				harpStep++;
			}
		}
		else if(INPUT_HARP_5 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_5 == 1)
			{
				selectHarp = LA;
				playMp3(MUSIC_LA);
				harpStep++;
			}
		}
		else if(INPUT_HARP_6 == 0)
		{
			delay_ms(50);
			if(INPUT_HARP_6 == 1)
			{
				selectHarp = SI;
				playMp3(MUSIC_SI);
				harpStep++;
			}
		}
		
		if(HARP_ANSWER[harpStep] == selectHarp)
		{
			//全部正确
			if(harpStep == answerLength)
			{
				playMp3(MUSIC_HARP_CORRECT);
				setStep(2);
				
				OUTPUT_DOOR_01 = 1;
				return;
			}
		}
		else
		{
			harpStep = 0;
			playMp3(MUSIC_HARP_ERROR);
		}
	}
}

void laser_and_say()
{
	while(1)
	{
		if((INPUT_LASER_03 == 1)&& (INPUT_LASER_02 == 1))
		{
			OUTPUT_DOOR_04 = 1;
			playMp3(MUSIC_LASER_SAY_CORRECT);
			setStep(3);		
			return;
		}
	}
}

void setStep(int s)
{
	step = s;
}