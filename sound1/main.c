/***************************·ÉÃô¹¤×÷ÊÒÓ****************************
**  ¹¤³ÌÃû³Æ£ºYS-V0.7ÓïÒôÊ¶±ğÄ£¿éÇı¶¯³ÌĞò
**	CPU: STC11L08XE
**	¾§Õñ£º22.1184MHZ
**	²¨ÌØÂÊ£º9600 bit/S
**	ÅäÌ×²úÆ·ĞÅÏ¢£ºYS-V0.7ÓïÒôÊ¶±ğ¿ª·¢°å
**                http://shop106678316.taobao.com/
**  ÁªÏµÈº£º374834376
**  ĞŞ¸ÄÈÕÆÚ£º2013.9.13
**  ËµÃ÷£ºÆÕÍ¨Ä£Ê½£ºÖ±½Ó·¢ÓïÒôÊ¶±ğ
/***************************·ÉÒôÔÆµç×Ó******************************/
#include "config.h"
/************************************************************************************/
//	nAsrStatus ÓÃÀ´ÔÚmainÖ÷³ÌĞòÖĞ±íÊ¾³ÌĞòÔËĞĞµÄ×´Ì¬£¬²»ÊÇLD3320Ğ¾Æ¬ÄÚ²¿µÄ×´Ì¬¼Ä´æÆ÷
//	LD_ASR_NONE:		±íÊ¾Ã»ÓĞÔÚ×÷ASRÊ¶±ğ
//	LD_ASR_RUNING£º		±íÊ¾LD3320ÕıÔÚ×÷ASRÊ¶±ğÖĞ
//	LD_ASR_FOUNDOK:		±íÊ¾Ò»´ÎÊ¶±ğÁ÷³Ì½áÊøºó£¬ÓĞÒ»¸öÊ¶±ğ½á¹û
//	LD_ASR_FOUNDZERO:	±íÊ¾Ò»´ÎÊ¶±ğÁ÷³Ì½áÊøºó£¬Ã»ÓĞÊ¶±ğ½á¹û
//	LD_ASR_ERROR:		±íÊ¾Ò»´ÎÊ¶±ğÁ÷³ÌÖĞLD3320Ğ¾Æ¬ÄÚ²¿³öÏÖ²»ÕıÈ·µÄ×´Ì¬
/***********************************************************************************/
uint8 idata nAsrStatus=0;	
void MCU_init(); 
void ProcessInt0(); //Ê¶±ğ´¦Àíº¯Êı
void  delay(unsigned long uldata);
void 	User_handle(uint8 dat);//ÓÃ»§Ö´ĞĞ²Ù×÷º¯Êı
void Delay200ms();
uint8_t G0_flag=DISABLE;//ÔËĞĞ±êÖ¾£¬ENABLE:ÔËĞĞ¡£DISABLE:½ûÖ¹ÔËĞĞ 
sbit LED=P1^7;//ĞÅºÅÖ¸Ê¾µÆ

/***********************************************************
* Ãû    ³Æ£º void  main(void)
* ¹¦    ÄÜ£º Ö÷º¯Êı	³ÌĞòÈë¿Ú
* Èë¿Ú²ÎÊı£º  
* ³ö¿Ú²ÎÊı£º
* Ëµ    Ã÷£º 					 
* µ÷ÓÃ·½·¨£º 
**********************************************************/ 
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i=0;
	MCU_init();
	LD_Reset();
	UartIni(); /*´®¿Ú³õÊ¼»¯*/
	nAsrStatus = LD_ASR_NONE;		//	³õÊ¼×´Ì¬£ºÃ»ÓĞÔÚ×÷ASR
	
	#ifdef TEST	
    PrintCom("Ò»¼¶¿ÚÁî£ºĞ¡½Ü\r\n"); /*text.....*/
	PrintCom("¶ş¼¶¿ÚÁî£º1¡¢´úÂë²âÊÔ\r\n"); /*text.....*/
	PrintCom("	2¡¢¿ª·¢°åÑéÖ¤\r\n"); /*text.....*/
	PrintCom("	3¡¢¿ªµÆ\r\n"); /*text.....*/
	PrintCom("	4¡¢¹ØµÆ\r\n"); /*text.....*/
	PrintCom("  5¡¢±±¾©\r\n"); /*text.....*/
	PrintCom("	6¡¢ÉÏº£\r\n"); /*text.....*/
	PrintCom("	7¡¢¹ãÖİ\r\n"); /*text.....*/
	#endif

  	LED = 1;
	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
				break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	/*	Æô¶¯Ò»´ÎASRÊ¶±ğÁ÷³Ì£ºASR³õÊ¼»¯£¬ASRÌí¼Ó¹Ø¼ü´ÊÓï£¬Æô¶¯ASRÔËËã*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	Ò»´ÎASRÊ¶±ğÁ÷³Ì½áÊø£¬È¥È¡ASRÊ¶±ğ½á¹û*/
			{				
				nAsrRes = LD_GetResult();		/*»ñÈ¡½á¹û*/
				User_handle(nAsrRes);//ÓÃ»§Ö´ĞĞº¯Êı 
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		}// switch	 			
	}// while

}

/***********************************************************
* Ãû    ³Æ£º void MCU_init()
* ¹¦    ÄÜ£º µ¥Æ¬»ú³õÊ¼»¯
* Èë¿Ú²ÎÊı£º  
* ³ö¿Ú²ÎÊı£º
* Ëµ    Ã÷£º 					 
* µ÷ÓÃ·½·¨£º 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	LD_MODE = 0;		//	ÉèÖÃMD¹Ü½ÅÎªµÍ£¬²¢ĞĞÄ£Ê½¶ÁĞ´
	IE0=1;
	EX0=1;
	EA=1;
}
/***********************************************************
* Ãû    ³Æ£º	ÑÓÊ±º¯Êı
* ¹¦    ÄÜ£º
* Èë¿Ú²ÎÊı£º  
* ³ö¿Ú²ÎÊı£º
* Ëµ    Ã÷£º 					 
* µ÷ÓÃ·½·¨£º 
**********************************************************/ 
void Delay200us()		//@22.1184MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 5;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void  delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	while(uldata--)
	Delay200us();
}

void Delay200ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
/***********************************************************
* Ãû    ³Æ£º ÖĞ¶Ï´¦Àíº¯Êı
* ¹¦    ÄÜ£º
* Èë¿Ú²ÎÊı£º  
* ³ö¿Ú²ÎÊı£º
* Ëµ    Ã÷£º 					 
* µ÷ÓÃ·½·¨£º 
**********************************************************/ 
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				/*	LD3320 ËÍ³öÖĞ¶ÏĞÅºÅ£¬°üÀ¨ASRºÍ²¥·ÅMP3µÄÖĞ¶Ï£¬ĞèÒªÔÚÖĞ¶Ï´¦Àíº¯ÊıÖĞ·Ö±ğ´¦Àí*/
}
/***********************************************************
* Ãû    ³Æ£ºÓÃ»§Ö´ĞĞº¯Êı 
* ¹¦    ÄÜ£ºÊ¶±ğ³É¹¦ºó£¬Ö´ĞĞ¶¯×÷¿ÉÔÚ´Ë½øĞĞĞŞ¸Ä 
* Èë¿Ú²ÎÊı£º ÎŞ 
* ³ö¿Ú²ÎÊı£ºÎŞ
* Ëµ    Ã÷£º 					 
**********************************************************/
void 	User_handle(uint8 dat)
{
     //UARTSendByte(dat);//´®¿ÚÊ¶±ğÂë£¨Ê®Áù½øÖÆ£©

			 switch(dat)		   /*¶Ô½á¹ûÖ´ĞĞÏà¹Ø²Ù×÷,¿Í»§ĞŞ¸Ä*/
			  {
				  case CODE_DMCS:			/*ÃüÁî¡°²âÊÔ¡±*/
						PrintCom("¡°´úÂë²âÊÔ¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_KFBYZ:	 /*ÃüÁî¡°È«¿ª¡±*/
						PrintCom("¡°¿ª·¢°åÑéÖ¤¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_KD:		/*ÃüÁî¡°¸´Î»¡±*/				
						PrintCom("¡°¿ªµÆ¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_GD:		/*ÃüÁî¡°¸´Î»¡±*/				
						PrintCom("¡°¹ØµÆ¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_BJ:		/*ÃüÁî¡°¸´Î»¡±*/				
						PrintCom("¡°±±¾©¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_SH:		/*ÃüÁî¡°¸´Î»¡±*/				
						PrintCom("¡°ÉÏº£¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_GZ:		/*ÃüÁî¡°¸´Î»¡±*/				
						PrintCom("¡°¹ãÖİ¡±ÃüÁîÊ¶±ğ³É¹¦\r\n"); /*text.....*/
						break;
					case CODE_ALA:
						PrintCom("°¢À­»ô¶´¿ª\r\n");
						LED = 0;
						break;																				
					default:
						PrintCom("ÇëÖØĞÂÊ¶±ğ·¢¿ÚÁî\r\n"); /*text.....*/
						break;
				}	
}	 
