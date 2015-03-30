
#define __PRINTER_C

#include "pc_printer.h"

volatile unsigned char buf_ptr=0;
volatile unsigned char prn_buf[32]={0};
volatile unsigned char prt_stat;

u8 prnt_double_height=0;
u8 prnt_double_width=0;

static u16 Pixel;
static u16 *Data_Ptr;
static u8  Max_Chars;

void Init_Printer_Vars(void)
{
	PrintBusy  = 0;
	PrintAbort = 0;
	PrintOv_Flag = 1;
	PrintStart_Flag = 0;
	Print_Sol_State = 0;
	MotorSteps_state= 0;
}

u8 GetPrinter_Status(void)
{
	if(READ_PORT_PIN(PRN_PAP_PORT, PRN_PAP_SENSE) == 1)
		return 1;
	else if(PrintBusy == 1 || PrintStart_Flag == 1)
		return 2;
	else
		return 0;
}

void Set_Line(u8 *Str, uc8 Line, uc8 Font_H, uc8 Font_W)
{
	u16 dot_cnt, index;
	u8  ii, jj;

	switch(Font_H)
	{
	case 8:  /* Font Height */
		Data_Ptr = (u16 *)table_8x8;  /* 8 Height & 8 Width */
		Pixel = (0x80 >> Line);
		break;
	case 12: /* Font Height */			  /* 12 Height & 8 Width */
		Data_Ptr = (u16 *)table_12x8;
		Pixel = (0x800 >> Line);
		break;
	case 16: /* Font Height */		      /* 16 Height & 12 Width */
		Data_Ptr = (u16 *)table_16x12;
		Pixel = (0x8000 >> Line);
		break;
	default:/* Default Font Height */	  /* 8 Height & 8 Width */
		Data_Ptr = (u16 *)table_8x8;
		Pixel = (0x80 >> Line);
		break;
	}
	/* Maximum Printable Characters In A Line */
	Max_Chars = NUM_OF_DOTS/ Font_W;

	for(ii = 0, dot_cnt = 0; ii < Max_Chars && Str[ii] != '\0'; ii++)
	{
		if(Font_W != 8 && Font_W != 12)
			index = Str[ii] * 8;
		else
			index = Str[ii] * Font_W;

		for(jj = 0; jj < Font_W; jj++)
		{
			Dot_Buffer[dot_cnt++] = Data_Ptr[index + jj] & Pixel;

			if(prnt_double_width)
				Dot_Buffer[dot_cnt++] = Data_Ptr[index + jj] & Pixel;
		}
		if(dot_cnt >= NUM_OF_DOTS) break;
	}

	for(index = 0; index < NUM_OF_DOTS; index++)
	{
		if(Dot_Buffer[index])
			SET_PORT_PIN(PRN_DIN_PORT, PRN_DIN);
		else
			CLR_PORT_PIN(PRN_DIN_PORT, PRN_DIN);

		CLR_PORT_PIN(PRN_CLK_PORT, PRN_CLK);

		SET_PORT_PIN(PRN_CLK_PORT, PRN_CLK);
	}
}

u8 Start_Print(u8 *String, uc8 Font_H, uc8 Font_W)
{
	u16 ii;

	/* Enable Power to Print Head */
	SET_PORT_PIN(PRN_PWR_CTRL_PORT, PRN_PWR_CTRL);

	for(ii = 0; ii < Font_H; ii++)
	{
		Strnset((u8 *)Dot_Buffer, 0x00, NUM_OF_DOTS);
		Set_Line(String, ii, Font_H, Font_W);

		/* Data Latch Signal to Printer: L to H */
		CLR_PORT_PIN(PRN_LAT_PORT, PRN_LAT);
		SET_PORT_PIN(PRN_LAT_PORT, PRN_LAT);

		PrintOv_Flag = 0;
		PrintStart_Flag = 1;
		while(1)
		{
			if(PrintOv_Flag == 1)
			{
				Print_Sol_State=0;
				break;
			}
		}

		if(prnt_double_height)
		{
			Set_Line(String, ii, Font_H, Font_W);

			/* Data Latch Signal to Printer: L to H */
			CLR_PORT_PIN(PRN_LAT_PORT, PRN_LAT);
			SET_PORT_PIN(PRN_LAT_PORT, PRN_LAT);

			PrintOv_Flag = 0;
			PrintStart_Flag = 1;
			while(1)
			{
				if(PrintOv_Flag == 1)
				{
					Print_Sol_State=0;
					break;
				}
			}
		}
	}
	/* Disable Power to Print Head */
	CLR_PORT_PIN(PRN_PWR_CTRL_PORT, PRN_PWR_CTRL);
	Paper_Feed(1);
	return 0;
}

void Set_Line_Head_Clean(u8 *Str, uc8 Line, uc8 Font_H, uc8 Font_W)
{
	u16 dot_cnt, index;
	u8  ii, jj;


		Data_Ptr = (u16 *)head_clean_16x12;
		Pixel = (0x8000 >> Line);

	/* Maximum Printable Characters In A Line */
	Max_Chars = NUM_OF_DOTS/ Font_W;

	for(ii = 0, dot_cnt = 0; ii < Max_Chars && Str[ii] != '\0'; ii++)
	{
		if(Font_W != 8 && Font_W != 12)
			index = Str[ii] * 8;
		else
			index = Str[ii] * Font_W;

		for(jj = 0; jj < Font_W; jj++)
		{
			Dot_Buffer[dot_cnt++] = Data_Ptr[index + jj] & Pixel;

			if(prnt_double_width)
				Dot_Buffer[dot_cnt++] = Data_Ptr[index + jj] & Pixel;
		}
		if(dot_cnt >= NUM_OF_DOTS) break;
	}

	for(index = 0; index < NUM_OF_DOTS; index++)
	{
		if(Dot_Buffer[index])
			SET_PORT_PIN(PRN_DIN_PORT, PRN_DIN);
		else
			CLR_PORT_PIN(PRN_DIN_PORT, PRN_DIN);

		CLR_PORT_PIN(PRN_CLK_PORT, PRN_CLK);

		SET_PORT_PIN(PRN_CLK_PORT, PRN_CLK);
	}
}

u8 Start_Head_Clean(u8 *String, uc8 Font_H, uc8 Font_W)
{
	u16 ii, jj;

	/* Enable Power to Print Head */
	SET_PORT_PIN(PRN_PWR_CTRL_PORT, PRN_PWR_CTRL);

	for(ii = 0; ii < Font_H; ii++)
	{
		for(jj = 0; jj < 4; jj++)
	    {
			Strnset((u8 *)Dot_Buffer, 0x00, NUM_OF_DOTS);
			Set_Line_Head_Clean(String, ii, Font_H, Font_W);

			/* Data Latch Signal to Printer: L to H */
			CLR_PORT_PIN(PRN_LAT_PORT, PRN_LAT);
			SET_PORT_PIN(PRN_LAT_PORT, PRN_LAT);

			PrintOv_Flag = 0;
			PrintStart_Flag = 1;
			while(1)
			{
				if(PrintOv_Flag == 1)
				{
					Print_Sol_State=0;
					break;
				}
			}
		}
	}
	/* Disable Power to Print Head */
	CLR_PORT_PIN(PRN_PWR_CTRL_PORT, PRN_PWR_CTRL);
	//Paper_Feed(1);
	return 0;
}

void Paper_Feed(u8 No_Lines)
{
	u16 ii;  No_Lines = 2;

	for(ii = 0; ii < NUM_OF_DOTS; ii++)
	{
		CLR_PORT_PIN(PRN_DIN_PORT, PRN_DIN);

		CLR_PORT_PIN(PRN_CLK_PORT, PRN_CLK);

		SET_PORT_PIN(PRN_CLK_PORT, PRN_CLK);
	}

	SET_PORT_PIN(PRN_PWR_CTRL_PORT, PRN_PWR_CTRL);

	for(ii = 0; ii < No_Lines*8; ii++)
	{
		CLR_PORT_PIN(PRN_LAT_PORT, PRN_LAT);
		SET_PORT_PIN(PRN_LAT_PORT, PRN_LAT);

		PrintOv_Flag = 0;
		PrintStart_Flag = 1;

		while(1)
		{
			if(PrintOv_Flag == 1)
			{
				Print_Sol_State=0;
				break;
			}
		}
	}
	CLR_PORT_PIN(PRN_PWR_CTRL_PORT, PRN_PWR_CTRL);
	return;
}
