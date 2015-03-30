
#define __GLCD_C

#include "pc_lcd.h"

static u8 LCD_LineNo = 0;	// added variable
static u8 LCD_ColumnNo = 0;	// added variable
u8 LCD_pitch_width = 6;	// based on selected font table



void Glcd_Set_Contrast(void)
{
//	Glcd_Cmd_Write(0x81);
//	delay(2);
//	Glcd_Cmd_Write((mc.mc.lcd_con & 0x0F) << 2);
//	delay(2);
//	Glcd_Cmd_Write(((mc.mc.lcd_con & 0x7F) >> 4) | 0x20);
//	delay(2);
//	if(mc.mc.lcd_con & 0x80)
//		Glcd_Cmd_Write(0xC0);
//	else
//		Glcd_Cmd_Write(0xC8);
//	delay(2);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Send_Data_To_LCD(u8 Data)
{
	u16  D0toD7;

	D0toD7 = (GPIO_ReadOutputData(LCD_D0_D7) & 0xFF00) | ((u16)(Data));
	GPIO_Write(LCD_D0_D7, D0toD7);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Init(void)
{
	Delay_100uSec(100);
	CLR_RST_PIN();
	Delay_100uSec(50);
	SET_RST_PIN();
	Delay_100uSec(5);

	Glcd_Cmd_Write(LCD_Bias_0);
	Glcd_Cmd_Write(LCD_Col_Reverse_Dir);
	Glcd_Cmd_Write(0x25);
	Glcd_Cmd_Write(LCD_Ref_Voltage_Mode);
	Glcd_Cmd_Write(0x20);
	Glcd_Cmd_Write(0x00);
	Glcd_Cmd_Write(LCD_Power_Control);
	Glcd_Cmd_Write(LCD_Static_Inductor_OFF);
	Glcd_Cmd_Write(LCD_Entire_Disp_Normal);
	Glcd_Cmd_Write(LCD_InitDisp_Line);
	Glcd_Cmd_Write(LCD_Display_ON);
	Glcd_Cmd_Write(LCD_Page_Addr0);
	Glcd_Cmd_Write(LCD_Coladdr_MSB);
	Glcd_Cmd_Write(LCD_Coladdr_LSB);

	Glcd_Clear_Display();

	double_height = 0;
	double_width = 0;
	return;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Cmd_Write(u8 Cmd)
{
	Send_Data_To_LCD(Cmd);
	CLR_RS_PIN();	  /* Select Command Mode, RS = 0 */
	CLR_CS1_PIN();  /* Select Data Lines Enable, CS1 = 0 */
	Delay(10);
	SET_CS1_PIN();
	SET_RS_PIN();
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Data_Write(u8 Data)
{
	Send_Data_To_LCD(Data);
	CLR_RS_PIN();   /* Select Data Mode, RS = 0 */
	CLR_CS1_PIN();  /* Select Data Lines Enable, CS1 = 0 */
	Delay(10);
	SET_RS_PIN();
	SET_CS1_PIN();
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Column_Cmd( u8 Column)
{
	union
	{
		u8 col;
		struct
		{
			u8 lsb : 4;
			u8 msb : 4;
		}nib;
	} col_byte;

	col_byte.col = Column;
	Glcd_Cmd_Write( col_byte.nib.lsb);		 /* Sending LSB of column */
	Glcd_Cmd_Write( col_byte.nib.msb | 0x10);  /* Sending MSB of cloumn */
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 Glcd_Select_Page( u8 Page)
{
	switch( Page)
	{

	case 1:  Glcd_Cmd_Write(LCD_Page_Addr0);  break;
	case 2:  Glcd_Cmd_Write(LCD_Page_Addr1);  break;
	case 3:  Glcd_Cmd_Write(LCD_Page_Addr2);  break;
	case 4:  Glcd_Cmd_Write(LCD_Page_Addr3);  break;
	case 5:  Glcd_Cmd_Write(LCD_Page_Addr4);  break;
	case 6:  Glcd_Cmd_Write(LCD_Page_Addr5);  break;
	case 7:  Glcd_Cmd_Write(LCD_Page_Addr6);  break;
	case 8:  Glcd_Cmd_Write(LCD_Page_Addr7);  break;
	default: return -1; /* Error: Wrong Page Number */
	}
	return 0;
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Clear_Display( void)
{
	u8 tmp_page, tmp_column;

	Glcd_Cmd_Write( LCD_Display_ON);
	for( tmp_page = 0; tmp_page <= MAX_PAGES; tmp_page++)
	{
		Glcd_Select_Page( tmp_page);
		Glcd_Column_Cmd( 0x00);
		for( tmp_column = 0; tmp_column < MAX_COLUMNS; tmp_column++)
		{
			Glcd_Data_Write( 0x00);
		}
	}
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/


void Glcd_Display_String( u8 *String, u8 Page_no)
{
	u8 ii, index;
	u32 width;
	u16 const *ptr, *tblptr;
	u8 hi_part[6], lo_part[6];

	Glcd_Cmd_Write( LCD_Display_ON);
	Glcd_Select_Page( Page_no);
	Glcd_Column_Cmd( LCD_ColumnNo);

	width=6;
	tblptr = norm_font;

	if(double_height){
		for( index = 0; String[index] != '\0'; index++)
		{
			Glcd_Elongate(String[index], hi_part , lo_part);
			for( ii = 0; ii < width; ii++)
			{
				Glcd_Data_Write( lo_part[ii]);
				if(double_width)
					Glcd_Data_Write( lo_part[ii]);
			}
		}

		Glcd_Cmd_Write( LCD_Display_ON);
		Glcd_Select_Page(Page_no+1);
		Glcd_Column_Cmd( LCD_ColumnNo);

		for( index = 0; String[index] != '\0'; index++)
		{
			Glcd_Elongate(String[index], hi_part , lo_part);
			for( ii = 0; ii < width; ii++)
			{
				Glcd_Data_Write( hi_part[ii]);
				if(double_width)
					Glcd_Data_Write( hi_part[ii]);
			}
		}
	}
	else
	{
		for( index = 0; String[index] != '\0'; index++)
		{
			ptr = &tblptr[ String[index] * width];
			for( ii = 0; ii < width; ii++)
			{
				Glcd_Data_Write( *(ptr + ii));
				if(double_width)
					Glcd_Data_Write( *(ptr + ii));
			}
		}
	}


	LCD_ColumnNo += (index*width);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/


void Glcd_Display_Char( u8 Chr, u8 Page_No)
{
	u8 ii;
	u16 const *ptr;
	u32 width;
	u8 hi_part[6], lo_part[6];

	Glcd_Cmd_Write( LCD_Display_ON);
	Glcd_Select_Page( Page_No);
	Glcd_Column_Cmd( LCD_ColumnNo);

	width=6;
	ptr = &norm_font[ Chr * width];


	if(double_height){
		Glcd_Elongate(Chr, hi_part , lo_part);
		for( ii = 0; ii < width; ii++)
		{
			Glcd_Data_Write( lo_part[ii]);
			if(double_width)
				Glcd_Data_Write( lo_part[ii]);
		}
		Page_No++;
		Glcd_Cmd_Write( LCD_Display_ON);
		Glcd_Select_Page(Page_No);
		Glcd_Column_Cmd( LCD_ColumnNo);


		for( ii = 0; ii < width; ii++)
		{

			Glcd_Data_Write( hi_part[ii]);
			if(double_width)
				Glcd_Data_Write( hi_part[ii]);
		}
	}
	else
	{
		for( ii = 0; ii < width; ii++)
		{
			Glcd_Data_Write( *(ptr + ii));
			if(double_width)
				Glcd_Data_Write( *(ptr + ii));
		}
	}

	if(double_width)
	{
		LCD_pitch_width = 12;
	}
	else
	{
		LCD_pitch_width = 6;
	}

	LCD_ColumnNo += LCD_pitch_width;

}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Display_Byte( u8 Chr)
{
	u8 ii, tempchr;
	u16 const *ptr;

	ptr = &table_8x6[ Chr * 6];
	for( ii = 0; ii < 6; ii++)
	{
		tempchr = Rev_ByteBits( *(ptr + ii));
		Glcd_Data_Write( tempchr);
	}
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Display_BMP( char *Bmpstr)
{
	unsigned char ii=0,jj=0,kk=0,bit=0x01,temp=0x00,ch_bit=0x01,page;

	Glcd_Cmd_Write(LCD_Display_ON);

	for(page=0;page < 8;page++) /* Pages from 0 to 7 */
	{
		Glcd_Column_Cmd( 0x03);  /* strating Line */
		Glcd_Select_Page(page);

		for(kk=0;kk<16;kk++) /* taking total bytes in a Page(i.e 16bytes in one page) */
		{
			for(jj=0;jj<8;jj++)
			{
				for(ii=0;ii<8;ii++)
				{
					if(Bmpstr[(page*8*16)+ (ii*16)+kk] & bit)
						temp = temp | ch_bit;
					ch_bit <<= 0x01;
				}
				Glcd_Data_Write(~temp);
				temp = 0x00;
				ch_bit=0x01;
				bit <<= 1;
			}
			bit = 0x01;ch_bit=0x01;
		}
	}
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Disp_Ntwrk_Signal(u8 Level)
{
	u8 const *ptr;
	u8 ii;

	if(Level == 99 || Level == 0 || Level <= 1)
	{
		ptr = &Ntwrk_NA[0];
	}
	else if(Level >= 20)
	{
		ptr = &Ntwrk_Full[0];
	}
	else if(Level >= 15)
	{
		ptr = &Ntwrk_L1[0];
	}
	else if(Level >= 10)
	{
		ptr = &Ntwrk_L2[0];
	}
	else
	{
		ptr = &Ntwrk_L3[0];
	}

	Glcd_Select_Page(GSM_BATT_PAGE);
	Glcd_Column_Cmd( MAX_COLUMNS - NTWRK_WIDTH);
	for(ii = 0; ii < NTWRK_WIDTH; ii++)
	{
		Glcd_Data_Write( *(ptr+ii));
	}
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Glcd_Disp_Batt_ChargeInd(void)
{
	static u8 level = 0;
	u8 const *ptr;
	u8 ii;

	switch(level)
	{
	case 0:
		ptr = &Batt_Full[0];
		break;
	case 1:
		ptr = &Batt_L1[0];
		break;
	case 2:
		ptr = &Batt_L2[0];
		break;
	default:
		level = 0;
		return;
	}
	level++;

	Glcd_Select_Page(GSM_BATT_PAGE);
	Glcd_Column_Cmd(0);
	for(ii = 0; ii < BATT_WIDTH; ii++)
	{
		Glcd_Data_Write( *(ptr+ii));
	}
}



//	void blon(void)
//	INPUTS	:	void
//	OUTPUTS	:	void
//	it will make lcd backlight on.
//	baklit flag is set as a status flag
void Glcd_Display_On(void)
{

	Glcd_Cmd_Write(LCD_Display_ON);
}

//	void bloff(void)
//	INPUTS	:	void
//	OUTPUTS	:	void
//	it will make lcd backlight off.
//	baklit flag is cleared as a status flag
void Glcd_Display_Off(void)
{
	Glcd_Cmd_Write(LCD_Display_OFF);
}

//	void gotoxy(char row,char col)
//	INPUTS	:	char row - row no.
//				char col - col no.
//	OUTPUTS	:	void
//	it will decide starting postion of the char to be displayed.
void Glcd_Goto_XY(u8 row, u8 col)
{
	LCD_LineNo = row;

	if(double_width)
	{
		LCD_pitch_width = 12;
	}
	else
	{
		LCD_pitch_width = 6;
	}

	LCD_ColumnNo = (col*LCD_pitch_width);
}

void Glcd_Elongate(volatile unsigned char disp_temp, volatile unsigned char *hi_part, volatile unsigned char *lo_part)
{
	volatile unsigned char i,haf1,haf2;

	for(i = 0 ; i < 6 ; i++)
	{
		hi_part[i] = 0;
		lo_part[i] = 0;
		haf1 = ((norm_font[(disp_temp * 6) + i]) & 0xF0) >> 4;
		haf2 = (norm_font[(disp_temp * 6) + i]) & 0x0F;
		if(haf1 & 0x01)
			hi_part[i] |= 0x03;
		if(haf1 & 0x02)
			hi_part[i] |= 0x0C;
		if(haf1 & 0x04)
			hi_part[i] |= 0x30;
		if(haf1 & 0x08)
			hi_part[i] |= 0xC0;
		if(haf2 & 0x01)
			lo_part[i] |= 0x03;
		if(haf2 & 0x02)
			lo_part[i] |= 0x0C;
		if(haf2 & 0x04)
			lo_part[i] |= 0x30;
		if(haf2 & 0x08)
			lo_part[i] |= 0xC0;
	}


}
