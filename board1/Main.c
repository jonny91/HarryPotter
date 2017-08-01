#include <STC89C5xRC.H>
#include "HarryBoard1.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_DOOR_00 = P0^0;	//开始的电磁锁门

sbit INPUT_FIVE_STATUE = P0^1; //雕像放对了
sbit OUTPUT_FIVE_STATUE_DOOR = P0^2;//雕像放对了的柜门 
sbit INPUT_ROOM_1_SAY = P0^3;//第一个房间说话输入对错
sbit OUTPUT_ROOM2_DOOR = P0^4;//第二个房间的房门

sbit OUTPUT_HARP_SWITCH = P1^7; //竖琴的开关
sbit INPUT_HARP_0 = P1^0;	//do
sbit INPUT_HARP_1 = P1^1;	//re
sbit INPUT_HARP_2 = P1^2;	//mi
sbit INPUT_HARP_3 = P1^3;	//fa
sbit INPUT_HARP_4 = P1^4;	//so
sbit INPUT_HARP_5 = P1^5;	//la
sbit INPUT_HARP_6 = P1^6;	//si

sbit OUTPUT_DOOR_34 = P2^0;	//竖琴正确 打开的门
sbit OUTPUT_DOOR_37 = P2^1;	//竖琴正确 打开柜门
sbit INPUT_LASER_06 = P2^3;	//语音输入
sbit OUTPUT_DOOR_35 = P2^4;	//第三个房间
sbit OUTPUT_SIG_BOARD2 = P2^5; //第二块板子的电源b

void start();
void setStep(int s);
void harp();
void laser_and_say();
void fiveStatue();
void room1Say();

void init()
{
	INPUT_DOOR_00 = 0;
	OUTPUT_DOOR_34 = 1;
	OUTPUT_DOOR_37 = 1;
	INPUT_LASER_06 = 0;
	OUTPUT_DOOR_35 = 1;
	
	INPUT_HARP_0 = 0;
	INPUT_HARP_1 = 0;
	INPUT_HARP_2 = 0;
	INPUT_HARP_3 = 0;
	INPUT_HARP_4 = 0;
	INPUT_HARP_5 = 0;
	INPUT_HARP_6 = 0;

	INPUT_FIVE_STATUE = 0;
	OUTPUT_FIVE_STATUE_DOOR = 1;
	INPUT_ROOM_1_SAY = 0;
	OUTPUT_ROOM2_DOOR = 1;
	
	OUTPUT_SIG_BOARD2 = 1;
	OUTPUT_HARP_SWITCH = 1;
}
void main()
{
	init();
	uart_init();
	mp3_init();

	delay_ms(100);								   
	
	while(1)
	{
		switch(step)
		{
			case 0: //关门
				start();
				break;
			case 1: //5个雕像
				fiveStatue();
				break;
			case 2: //声控口令
				room1Say();
				break;
			case 3://弹竖琴		
				OUTPUT_HARP_SWITCH = 0;
				delay_ms(3000);
				harp();
				break;
			case 4: //激光语音
				laser_and_say();
				break;
			case 5:
				OUTPUT_HARP_SWITCH = 1;
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

void fiveStatue()
{
	if(INPUT_FIVE_STATUE == 1)//P01
	{
		delay_ms(500);
		if(INPUT_FIVE_STATUE == 1)
		{
			playMp3(FIVE_STATUE_CORRECT);
			OUTPUT_FIVE_STATUE_DOOR = 0;//P02
			delay_ms(500);
			setStep(2);	
		}
	}
}

void room1Say()
{
	if(INPUT_ROOM_1_SAY == 1)//P0^3
	{		
		delay—_ms(50);
		if(INPUT_ROOM_1_SAY == 1)
		{
			playMp3(ROOM_1_SAY_CORRECT);//P0^2
			OUTPUT_ROOM2_DOOR = 0;
			setStep(3);	
		}
	}
}

void harp()
{
	int answerLength = 10;
	unsigned int harpStep = 0;
	int selectHarp = 0;
	int lastHarp = 0;
	int myAnswer[10] = {0,0,0,0,0,0,0,0,0,0};
	int isCorrect = 0;
	int i;
	
	while(1)
	{
		if(INPUT_HARP_0 == 1)
		{
			delay_ms(50);
			
			playMp3(MUSIC_DO);
			while(INPUT_HARP_0 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 1;			
		}		

		if(INPUT_HARP_1 == 1)
		{
			delay_ms(50);
			playMp3(MUSIC_RE);
			while(INPUT_HARP_1 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 2;
		}
		
		if(INPUT_HARP_2 == 1)
		{
			delay_ms(50);
			playMp3(MUSIC_MI);
			while(INPUT_HARP_2 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 3;

			
		}
		
		if(INPUT_HARP_3 == 1)
		{
			delay_ms(50);
			playMp3(MUSIC_FA);
			while(INPUT_HARP_3 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 4;
			
		}


		if(INPUT_HARP_4 == 1)
		{
			delay_ms(50);
			playMp3(MUSIC_SO);
			while(INPUT_HARP_4 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 5;
			
		}


		if(INPUT_HARP_5 == 1)
		{
			delay_ms(50);
			playMp3(MUSIC_LA);
			while(INPUT_HARP_5 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 6;
			
		}

		if(INPUT_HARP_6 == 1)
		{
			delay_ms(50);
			playMp3(MUSIC_SI);
			while(INPUT_HARP_6 == 1){}
			
			for(i = 0 ; i < answerLength-1 ; i++ )
			{
				myAnswer[i] = myAnswer[i+1];
			}
			myAnswer[9] = 7;
			
		}	
        
        for (i = 0; i < answerLength; i++) {
            if(HARP_ANSWER[i] == myAnswer[i])
            {
                if(i == answerLength -1)
                {
                   isCorrect = 1;
               }
            }
			else
			{
				break;
			}
        }
		
		if(isCorrect == 1)
		{
			//全部争正确
      playMp3(MUSIC_HARP_CORRECT);
      setStep(4);
      //断电开门
      OUTPUT_DOOR_34 = 0;
      //打开柜门
      OUTPUT_DOOR_37 = 0;
	
			delay_ms(500);
      return;
		}
	}
}

void laser_and_say()
{
		if(INPUT_LASER_06 == 1)
		{
			delay_ms(50);
			if(INPUT_LASER_06 == 1)
			{
				OUTPUT_DOOR_35 = 0;
				//playMp3(MUSIC_LASER_SAY_CORRECT);
				OUTPUT_SIG_BOARD2 = 0;//下一块板子信号
				setStep(5);
				return;
			}		
		}
}
