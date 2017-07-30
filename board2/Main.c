#include <STC89C5xRC.H>
#include "HarryBoard2.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

void handInHand();
void chess();
void timer0();
void medicine();
void say();
void stone();
void check();

sbit INPUT_FROM_BOARD_1 = P0^0; // 第一块板子的信号
sbit INPUT_01 = P0^1; //手牵手的输入
sbit OUTPUT_02 = P0^2;//手牵手正确之后输出 棋盘的射灯亮


//国际象棋
//7f+8e同时踩下后 触发闪灯
//7f灭 8e亮 1亮
//1灭 8e亮 2亮
//8e灭 2亮 3亮
//2灭 3亮 4亮
//3灭 4亮 5亮
//4灭 5亮 6亮
//5灭 6亮 7亮
//演示完 重新踩7F 8E
//每一步 30秒计时
sbit chess_0 = P1^0;//7F
sbit chess_1 = P1^1;//8E
sbit chess_2 = P1^2;//1
sbit chess_3 = P1^3;//2
sbit chess_4 = P1^4;//3
sbit chess_5 = P1^5;//4
sbit chess_6 = P1^6;//5
sbit chess_7 = P1^7;//6
sbit chess_8 = P3^5;//7

sbit chess_light_0 = P2^0;
sbit chess_light_1 = P2^1;
sbit chess_light_2 = P2^2;
sbit chess_light_3 = P2^3;
sbit chess_light_4 = P2^4;
sbit chess_light_5 = P2^5;
sbit chess_light_6 = P2^6;
sbit chess_light_7 = P2^7;
sbit chess_light_8 = P3^6;

sbit OUTPUT_ROOM4 = P0^3;
sbit INPUT_MEDICINE_1 = P0^4;
sbit INPUT_MEDICINE_2 = P0^5;

sbit INPUT_SAY = P0^6;
//魔法石的盒子
sbit OUTPUT_SAY_CORRECT = P0^7;
//拿掉魔法石
sbit INPUT_STONE = P3^3;
//最后的门
sbit OUTPUT_LAST_DOOR = P3^4;

int i = 0;
int chessStep = 0;

//初始化象棋的接口 
//7f 8e不在里面初始化
void initChessLight()
{
	chess_2 = 0;
	chess_3 = 0;
	chess_4 = 0;
	chess_5 = 0;
	chess_6 = 0;
	chess_7 = 0;
    chess_8 = 0;
	
	chess_light_0 = 1;
	chess_light_1 = 1;
	chess_light_2 = 1;
	chess_light_3 = 1;
	chess_light_4 = 1;
	chess_light_5 = 1;
	chess_light_6 = 1;
	chess_light_7 = 1;
    chess_light_8 = 1;
}

void init()
{
  INPUT_FROM_BOARD_1 = 0;
    
	INPUT_01 = 0;
	OUTPUT_02 = 1;
	
	chess_0 = 0;
	chess_1 = 0;
	
	initChessLight();
	
	OUTPUT_ROOM4 = 1;
	INPUT_MEDICINE_1 = 0;
	INPUT_MEDICINE_2 = 0;
	INPUT_SAY = 0;
	OUTPUT_SAY_CORRECT = 1;
	INPUT_STONE = 0;
	OUTPUT_LAST_DOOR = 1;
}

void main()
{
	delay_ms(500);
	init();
	uart_init();
	mp3_init();
	timer0();
	//定时器暂停
	ET0 = 0;
	delay_ms(5000);
	step = 0;
	
	//通电测试
	playMp3(MUSIC_INDOOR);
	
	while(1)
	{
		switch(step)
		{
			case 0:
				check();
				break;
			case 1:
				handInHand();
				break;
			case 2:
				chess();
				break;
			case 3:
				medicine();
				break;
			case 4:
				say();
				break;
			case 5:
				stone();
				break;
			 case 6:
				break;
		}
	}
}

void check()
{
    if(INPUT_FROM_BOARD_1 == 1)
    {
				delay_ms(50);
				if(INPUT_FROM_BOARD_1 == 1)
				{		
					playMp3(MUSIC_INDOOR);
					setStep(1);
				}
    }
}

void handInHand()
{
	if(INPUT_01 == 1)
	{
		delay_ms(500);
		if(INPUT_01 == 1)
		{
			OUTPUT_02 = 0;
			playMp3(MUSIC_HANDINHAND_CORRECT);
			setStep(2);
		}
	}
}

void stone()
{
	if(INPUT_STONE == 1)
	{
		playMp3(MUSIC_GET_STONE);
		OUTPUT_LAST_DOOR = 0;
		setStep(6);
	}
}

void say()
{
	if(INPUT_SAY == 1)
	{
		delay_ms(50);
		if(INPUT_SAY == 1)
		{
			OUTPUT_SAY_CORRECT = 0;
			setStep(5);
		}
	}
}

void medicine()
{
	if( (INPUT_MEDICINE_1 == 1) && (INPUT_MEDICINE_2 == 1))
	{
		delay_ms(50);
		if((INPUT_MEDICINE_1 == 1) && (INPUT_MEDICINE_2 == 1))
		{
			setStep(4);

			playMp3(MUSIC_MEDICINE_CORRECT);
		}
	}
}

//演示
void chessPlay()
{
	ET0 = 0;
	
	chess_light_0 = 0;
	chess_light_1 = 0; //7f + 8e亮
	delay_ms(1000);
	
	chess_light_0 = 1;//7f灭
	chess_light_2 = 0;//1亮
	delay_ms(1000);
	
	chess_light_2 = 1;//1灭
	chess_light_3 = 0;//2亮
	delay_ms(1000);
	
	chess_light_1 = 1;//8e灭
	chess_light_4 = 0;//3亮
	delay_ms(1000);
	
	chess_light_3 = 1;//2灭
	chess_light_5 = 0;//4亮
	delay_ms(1000);
	
	chess_light_4 = 1;//3灭
	chess_light_6 = 0;//5亮
	delay_ms(1000);
	
	chess_light_5 = 1;//4灭	
	chess_light_7 = 0;//6亮
	delay_ms(1000);
	
	chess_light_6 = 1;//5灭
	chess_light_8 = 0;//7亮
	delay_ms(1000);
	
	chess_light_7 = 1;
	chess_light_8 = 1; //熄灭67
	delay_ms(500);
	
	ET0 = 1;
	i = CHESS_TIME;		
}

void chessPressLight()
{
	if(chess_0 == 1){chess_light_0 = 1;}
	if(chess_0 == 0){chess_light_0 = 0;}
		
	if(chess_1 == 1){chess_light_1 = 1;}
	if(chess_1 == 0){chess_light_1 = 0;}
		
	if(chess_2 == 1){chess_light_2 = 1;}
	if(chess_2 == 0){chess_light_2 = 0;}
	
	if(chess_3 == 1){chess_light_3 = 1;}
	if(chess_3 == 0){chess_light_3 = 0;}
		
	if(chess_4 == 1){chess_light_4 = 1;}
	if(chess_4 == 0){chess_light_4 = 0;}
		
	if(chess_5 == 1){chess_light_5 = 1;}
	if(chess_5 == 0){chess_light_5 = 0;}
		
	if(chess_6 == 1){chess_light_6 = 1;}
	if(chess_6 == 0){chess_light_6 = 0;}

	if(chess_7 == 1){chess_light_7 = 1;}
	if(chess_7 == 0){chess_light_7 = 0;}
		
	if(chess_8 == 1){chess_light_8 = 1;}
	if(chess_8 == 0){chess_light_8 = 0;}
}

int isNeedPlay = 1; //是否需要演示
void chess()
{
	int isRight = 1;

	while(1)
	{		
		if((chess_0 == 1)&&(chess_1 == 1)&&(isNeedPlay == 1)) //7f 8e同时踩下
		{
			chessPlay();
			isNeedPlay = 0;//演示过了
		}
		
		//踩下亮对应的灯泡
		chessPressLight();			
		
		switch(chessStep)
		{
			case 0: //7f+8e
				if((chess_0 == 1)&&(chess_1 == 1))
				{
					chessStep = 1;
					i = CHESS_TIME;	
				}
				break;
			case 1://7f灭 8e亮 1亮
				if((chess_0 == 0)&&(chess_1 == 1)&&(chess_2 == 1))
				{
					chessStep = 2;
					i = CHESS_TIME;	
				}
				break;
			case 2://1灭 8e亮 2亮
				if((chess_2 == 0)&&(chess_1 == 1)&&(chess_3 == 1))
				{
					chessStep = 3;
					i = CHESS_TIME;	
				}
				break;
			case 3://8e灭 2亮 3亮
				if((chess_1 == 0)&&(chess_3 == 1)&&(chess_4 == 1))
				{
					chessStep = 4;
					i = CHESS_TIME;	
				}
				break;
			case 4://2灭 3亮 4亮
				if((chess_3 == 0)&&(chess_4 == 1)&&(chess_5 == 1))
				{
					chessStep = 5;
					i = CHESS_TIME;	
				}
				break;
			case 5://3灭 4亮 5亮
				if((chess_4 == 0)&&(chess_5 == 1)&&(chess_6 == 1))
				{
					chessStep = 6;
					i = CHESS_TIME;	
				}
				break;
			case 6://4灭 5亮 6亮
				if((chess_5 == 0)&&(chess_6 == 1)&&(chess_7 == 1))
				{
					chessStep = 7;
					i = CHESS_TIME;	
				}
				break;
			case 7://5灭 6亮 7亮
				if((chess_6 == 0)&&(chess_7 == 1)&&(chess_8 == 1))
				{
					setStep(3);
					ET0 = 0;
					playMp3(MUSIC_CHESS);
					
					//开第四个房间的门
					OUTPUT_ROOM4 = 0;
					return;
				}
				break;
		}
	}
}

void Timer_Routine(void) interrupt 1
{
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值

    i--;

    if(i == 0)
	{
		i = CHESS_TIME;		
		chessStep = 0;
		initChessLight();
		isNeedPlay = 1;
    }        
}


void timer0()
{
	//10秒
    i = CHESS_TIME;	

	TMOD = 0x01; //16位定时器
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	ET0 = 1; //允许T0中断
    EA  = 1; //开放中断
    TR0 = 1;

}
