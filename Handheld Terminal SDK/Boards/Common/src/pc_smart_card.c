
#define  __SMART_CARD_C

#include "pc_smart_card.h"

u8 membuf[BUF_LEN] = {0};
vu8 SMRTCARD_Buffer[PC_RX_SIZE] = {0};
vu8 SMRTCARDDATA_Buffer[32] = {0};

void Smart_Card_Configure(void)
{
	USART_Configure(RFID_PORT, RFID_USART_APB, RFID_BITRATE/1.5, RFID_APB_NUM);
}

void smrt_wrt(u8 ch)
{
	USART_SendChar(RFID_PORT, ch);
}

u8 Smart_Card_Send_Command(u8 cmd, u8 typ, u8 k, u8 ss, u8 bb, u8* dbuf, u8 auth)
{
	vu8 ks_flag=0,resp_flag=0,op_flag=0,dt_flag=0,bb_flag=0,csn_flag=0,dec_flag=0,key_flag=0;
	vu8 i,j,strt=0;
	smrt_cnt=0;

	switch(typ)
	{
	case POL_AUTH:
		csn_flag=1;
		Glcd_Clear_Display();
		Glcd_Goto_XY(4,1);
		Glcd_Display_String(" CHECKING CARD .... ", 2);
	case POL_PRES:
		strt=4;
		op_flag=1;
	case POL_STOP:
		ks_flag=1;
		resp_flag=1;
		break;
	}
	//set_baud(SMRT);
	smrt_wrt('$');
	smrt_wrt('1');
	smrt_wrt(cmd);
	if(typ)
		smrt_wrt(typ);
	switch(cmd)
	{
	case AUTH_INC:
	case AUTH_DEC:
		ks_flag=1;
	case INCREMENT:
	case DECREMENT:
		dec_flag=1;
		resp_flag=1;
		bb_flag=1;
		break;

	case AUTH_WRITE:
		ks_flag=1;
	case WRITE:
		dt_flag=1;
		resp_flag=1;
		break;

	case AUTH_READ:
		strt=2;
		ks_flag=1;
	case READ:
		strt=2;
		op_flag=1;
		break;
	case WRITE_KEYS:
		key_flag=1;
		resp_flag=1;
		break;
	}
	if(key_flag)
	{
		smrt_wrt(hextoasc(ss/0x10));			//	SECTOR MSB.
		smrt_wrt(hextoasc(ss&0x0f));			//	SECTOR LSB.
		smrt_wrt(hextoasc(k&0x01));			//	KEY TYPE.
		for(;*dbuf!='\0';dbuf++)
			smrt_wrt(*dbuf);					//	KEYS.
	}
	else
	{
		if(ks_flag)
		{
			smrt_wrt('0');
			smrt_wrt(hextoasc(k&0x01));		//	KEY TYPE.
			smrt_wrt(hextoasc(ss/0x10));		//	SECTOR MSB.
			smrt_wrt(hextoasc(ss&0x0f));		//	SECTOR LSB.
		}
		smrt_wrt(hextoasc(bb/0x10));		//	BLOCK MSB.
		smrt_wrt(hextoasc(bb&0x0f));		//	BLOCK LSB.
		if(bb_flag)
		{
			smrt_wrt(hextoasc(bb/0x10));		//	BLOCK MSB.
			smrt_wrt(hextoasc(bb&0x0f));		//	BLOCK LSB.
		}
	}
	if(dt_flag)
	{
		for(;*dbuf!='\0';dbuf++)
		{
			smrt_wrt(hextoasc(*dbuf/0x10));		//	BLOCK MSB.
			smrt_wrt(hextoasc(*dbuf&0x0f));		//	BLOCK LSB.
		}
	}
	if(dec_flag)
	{
		for(i=0;i<7;i++)
			smrt_wrt('0');
		smrt_wrt('1');
	}
	smrt_wrt('\n');
	if(resp_flag)
	{
		StartTimer();
		while((!rec_flag_rfid)&&(!tout_err));
		StopTimer();
		rec_flag_rfid=0;

		if((tout_err)||(SMRTCARD_Buffer[0]=='x'))
		{
			//set_baud(PCCM);
			//disable_serial();
			Glcd_Goto_XY(4,1);
			if(csn_flag)
				Glcd_Display_String("  CARD NOT FOUND !  ", 2);
			else
				Glcd_Display_String(" TRANSACTION ERROR! ", 2);
			Beep(ERRR);
			Glcd_Clear_Display();
			return 0;
		}
	}
	if(op_flag)
	{
		StartTimer();
		while((!rec_flag_rfid)&&(!tout_err));
		StopTimer();

		if((tout_err)||(SMRTCARD_Buffer[0]=='x'))
		{
//			set_baud(PCCM);
//			disable_serial();
			Glcd_Goto_XY(4,1);
			if(csn_flag)
				Glcd_Display_String("  CARD NOT FOUND !  ", 2);
			else
				Glcd_Display_String(" TRANSACTION ERROR! ", 2);
			Beep(ERRR);
			Glcd_Clear_Display();
			return 0;
		}

		Delay_mSec(60);


		for(i=1;SMRTCARD_Buffer[i]!='\0';i++)
		{
			membuf[i] = SMRTCARD_Buffer[i];
		}
		membuf[i]='\0';




		for(i=strt+1,j=0;i<smrt_cnt;i+=2,j++)
		{
			SMRTCARDDATA_Buffer[j]=((asctohex(membuf[i])<<4)&0xF0)|((asctohex(membuf[i+1]))&0x0F);
		}
		SMRTCARDDATA_Buffer[j]='\0';


	}
//	set_baud(PCCM);
//	disable_serial();
	return 1;
}
