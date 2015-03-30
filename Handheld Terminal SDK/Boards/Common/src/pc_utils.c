
#define  __UTILS_C

#include "pc_utils.h"



//------------------------------------------------------------------------
//				CONVERSIONS IN BETWEEN HEX, BCD, ASCII.
//------------------------------------------------------------------------
void pk_unpk(volatile unsigned char pk,volatile unsigned char *unpk)
{
	unpk[1]	= ( (pk & 0x0F)		  | 0x30);
	unpk[0]	= (((pk & 0xF0) >> 4) | 0x30);
}
//------------------------------------------------------------------------
unsigned char unpk_pk(volatile unsigned char *unpk)
{
	return ( ((unpk[0] & 0x0F) << 4) | (unpk[1] & 0x0F) );
}
//------------------------------------------------------------------------
unsigned char hex_bcd(volatile unsigned char hex)
{
	return ( ((hex / 16) * 10) + (hex % 16) );
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void hex_asc(volatile long hex, volatile unsigned char *asc, volatile unsigned char dig)
{
	volatile unsigned char i;

	asc[dig] = '\0';
	for(i = dig ; i ; i--, hex /= 10)
	{
		asc[i-1] = (hex % 10) | 0x30;
	}
}
//------------------------------------------------------------------------
long asc_hex(volatile unsigned char *asc, volatile unsigned char dig)
{
	volatile long hex;
	volatile long j;
	volatile unsigned char i;

	for(i = dig, j = 1, hex = 0 ; i ; i--, j *= 10)
	{
		hex += (asc[i-1] & 0x0F) * j;
	}
	return (hex);
}
//------------------------------------------------------------------------
void rem_zeros(volatile unsigned char *asc, volatile unsigned char dig)
{
	volatile unsigned char i;

	for(i = 0 ; ((asc[i]=='0') && (i<dig)) ; i++)
	{
		asc[i] = ' ';
	}
}

//------------------------------------------------------------------------
long get_mins(volatile unsigned char dt, volatile unsigned char mt, volatile unsigned char yr, volatile unsigned char hr, volatile unsigned char mn)
{
	volatile unsigned char i;
	volatile long mins;
	volatile unsigned int days;

	dt=hex_bcd(dt);
	mt=hex_bcd(mt);
	yr=hex_bcd(yr);
	hr=hex_bcd(hr);
	mn=hex_bcd(mn);

	days= (unsigned int)yr*365;
	days+=((yr-1)/4);
	for(i=1;i<mt;i++)
		switch(i)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days+=31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days+=30;
			break;
		case 2:
			if(yr%4)
				days+=28;
			else
				days+=29;
			break;
	}
	days+=(dt-1);

	mins=(long)days*1440;
	mins+=((long)hr*60);
	mins+=mn;

	return mins;
}
unsigned char hextoasc(unsigned char temp)
{
	if(temp>9)
		return ((temp-10)+'A');
	return (temp+'0');
}
unsigned char asctohex(volatile unsigned char temp)
{
	if((temp>='0')&&(temp<='9'))
		return(temp-'0');
	if((temp>='A')&&(temp<='F'))
		return((temp+10)-'A');
	if((temp>='a')&&(temp<='f'))
		return((temp+10)-'a');
	return 0;
}
//------------------------------------------------------------------------
long rndup_ammt(volatile long ammt)
{

	if((ammt%100)>=50)
		return ((long)((ammt/100)+1)*100);
	if((ammt%100)<50)
		return ((long)(ammt/100)*100);

	return 0;
}
//void tim_asc_hex_print (void)
//{
//
//	hex_asc(tim.tim.dd, dd2, 2);
//	hex_asc(tim.tim.mm, mm2, 2);
//	hex_asc(tim.tim.yy, yy2, 2);
//	hex_asc(tim.tim.hr, hr2, 2);
//	hex_asc(tim.tim.mn, mn2, 2);
//	hex_asc(tim.tim.sc, sc2, 2);
//
//}
//void tim_hex_asc (void)
//{
//
//	hex_asc(tim.tim.dd, dd2, 2);
//	hex_asc(tim.tim.mm, mm2, 2);
//	hex_asc(tim.tim.yy, yy2, 2);
//	hex_asc(tim.tim.hr, hr2, 2);
//	hex_asc(tim.tim.mn, mn2, 2);
//	hex_asc(tim.tim.sc, sc2, 2);
//
//}
//------------------------------------------------------------------------
//	void tim_hex_asc(void)
//	INPUTS	:	void
//	OUTPUTS	:	void
//	converts hex values stored in in tim union and
//	stores in dd2, mm2, yy2, hr2, mn2, sc2 arrays.
//void tim_hex_asc_print(void)
//{
//
//
//	pk_unpk(tim.tim.dd, dd2);
//	pk_unpk(tim.tim.mm, mm2);
//	pk_unpk(tim.tim.yy, yy2);
//	pk_unpk(tim.tim.hr, hr2);
//	pk_unpk(tim.tim.mn, mn2);
//	pk_unpk(tim.tim.sc, sc2);
//}
//------------------------------------------------------------------------
//	void tim_asc_hex(void)
//	INPUTS	:	void
//	OUTPUTS	:	void
//	converts ascii values stored in dd2, mm2, yy2, hr2, mn2, sc2 arrays in hex and
//	stores in tim union.
//void tim_asc_hex(void)
//{
//	tim.tim.dd = unpk_pk(dd2);
//	tim.tim.mm = unpk_pk(mm2);
//	tim.tim.yy = unpk_pk(yy2);
//	tim.tim.hr = unpk_pk(hr2);
//	tim.tim.mn = unpk_pk(mn2);
//	tim.tim.sc = unpk_pk(sc2);
//}

//------------------------------------------------------------------------
//void delay(volatile unsigned int nCount)  //added
//{
//	for(; nCount != 0; nCount--);
//}

void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/


/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Clrbuf(u8 *Str, u32 Len)
{
	u32 ii;
	for(ii= 0; ii< Len; ii++)
	{
		Str[ii] = '\0';
	}
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u16 Strlen( const u8 *str)
{
	u16 ii;
	for(ii= 0; *(str+ii) != '\0'; ii++);
	return ii;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 *Strcpy(u8 *dest, const u8 *src)
{
	u16 ii;
	for(ii= 0; *(src+ii) != '\0'; ii++)
		*(dest+ii) = *(src+ii);
	return dest;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 *Strncpy(u8 *dest, const u8 *src, u16 maxlen)
{
	u16 ii;
	for(ii= 0; ii< maxlen; ii++)
	{
		if(*(src+ii) != '\0')
			*(dest+ii) = *(src+ii);
		else
			break;
	}
	return dest;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 *Strcat(u8 *dest, const u8 *src)
{
	u16 ii, dest_len;
	dest_len = Strlen(dest);
	for(ii= 0; *(src+ii) != '\0'; ii++)
		*(dest+dest_len+ii) = *(src+ii);
	*(dest+dest_len+ii) = '\0';
	return dest;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 Strcmp(const u8 *s1, const u8*s2)
{
	u16 ii;
	for(ii = 0; *(s1+ii) != '\0' && *(s2+ii) != '\0'; ii++)
	{
		if(*(s1+ii) < *(s2+ii))
			return -1;
		else
			if(*(s1+ii) > *(s2+ii))
				return +1;
	}
	if(*(s1+ii) != '\0' && *(s2+ii) == '\0')
		return +1;
	else
		if(*(s1+ii) == '\0' && *(s2+ii) != '\0')
			return -1;
		else
			return 0;
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  : To compare given number of characters in two strings
Input  : string1, string2 and no. of characters in string2 to compare with string1
Output : if
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
s8 Strncmp( const u8 *str1, const u8 *str2, u16 nob)
{
	u16 index;

	index = 0;
	while(str1[index] != '\0' && str2[index] != '\0' && nob != 0)
	{
		if( str1[index] > str2[index])
			return 1;
		else
			if( str1[index] < str2[index])
				return -1;
		index++;
		nob--;
	}
	if( nob != 0)
	{
		if( str1[index] == '\0' && str2[index] != '\0')
			return -1;
		else
			return 1;
	}
	else
		return 0;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 *Strnset(u8 *str, u16 ch, u16 n)
{
	u16 ii;
	for(ii= 0; ii< n; ii++)
		*(str+ii) = ch;
	return str;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 *strset(u8 *s, u16 ch)
{
	u16 ii;
	for(ii= 0; *(s+ii) != '\0'; ii++)
		*(s+ii) = ch;
	return s;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ItoA( const unsigned long value, unsigned char *str)
{
	u8  ii = 0, num, index = 0, tmpstr[8];
	u32 tmpvalue;

	tmpvalue = value;
	do{
		num = tmpvalue % 10;
		if( num < 10)
			tmpstr[index++] = num + '0';
		else
			tmpstr[index++] = ( num - 10) + 'A';
		tmpvalue = tmpvalue /10;
	}while( tmpvalue != 0);

	do{
		str[ii++] = tmpstr[--index];
	}while( index != 0);
	str[ii] = '\0';
}

/*F*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
float AtoF(s8 *str)
{
	u16   ii, Dividend =1;
	s8    chr, point, decimal;
	float Value;

	point = 0;
	Value = 0;
	decimal= 0;
	for(ii= 0; str[ii] != '\0'; ii++)
	{
		if( str[ii] == '.')
		{
			decimal= 1;
		}
		else
		{
			if(decimal == 1)
				point++;
			chr = str[ii] - 0x30;
			Value = (Value *10) + chr;
		}
	}
	while(point-- != 0)  Dividend = Dividend*10;
	Value = Value/ (double)Dividend;

	return Value;
}

/*F*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
u32 AtoI( u8 *str)
{
	u32 Value;
	u8  chr, index;

	for( index = 0, Value = 0; str[index] != '\0'; index++)
	{
		chr = str[index];
		if( chr >= '0' && chr <= '9')
			Value = ( Value * 10) + ( chr - '0');
		else
			break;
	}
	return Value;
}

/*F*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void Rev_String(u8 *str)
{
	u16 ii, jj;
	u8  ch;

	for(ii = 0, jj = (Strlen(str)-2); ii < jj; ii++, jj--)
	{
		ch = str[jj];
		str[jj] = str[ii];
		str[ii] = ch;
	}
}
/*F*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
u8 Rev_ByteBits(u8 byte)
{
	u8 tbit, rev, ii, mskd_bit;

	tbit = 0x01;
	rev  = 0x00;
	for(ii = 0; ii< 8; ii++)
	{
		mskd_bit = (byte & tbit) ? (1 << ((BYTE-1)-ii)):0;
		rev |= mskd_bit;
		tbit <<= 1;
	}
	return rev;
}

/*F*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
u16 Rev_HalfWordBits(u16 byte)
{
	u16 tbit, rev, ii, mskd_bit;

	tbit = 0x01;
	rev  = 0x00;
	for(ii = 0; ii< 16; ii++)
	{
		mskd_bit = (byte & tbit) ? (1 << ((HALFWORD-1)-ii)):0;
		rev |= mskd_bit;
		tbit <<= 1;
	}
	return rev;
}

/*F*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Desc.  :
Input  :
Output :
Example:
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
u32 Rev_WordBits(u32 byte)
{
	u32 tbit, rev, ii, mskd_bit;

	tbit = 0x01;
	rev  = 0x00;
	for(ii = 0; ii< 32; ii++)
	{
		mskd_bit = (byte & tbit) ? (1 << ((WORD-1)-ii)):0;
		rev |= mskd_bit;
		tbit <<= 1;
	}
	return rev;
}

void Delay_mSec(u16 Count_mSec)
{
	u16 Count_uSec;
	unsigned char Count_100uSec;

	while(Count_mSec--)
	{
		for(Count_100uSec=10;Count_100uSec != 0;Count_100uSec--)
		{
			for(Count_uSec=1000;Count_uSec != 0;Count_uSec--)
			{

			}
		}
	}
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Delay_100uSec(u16 Count_100uSec)
{
	u16 Count_uSec;

	while(Count_100uSec--)
	{
		for(Count_uSec=10;Count_uSec != 0;Count_uSec--)
		{

		}
	}
}
//void printUartIntToString(volatile int val,u8 *message)
//{
//	u8 strBuff[256];
//	ItoA(val,strBuff);
//	USART_SendString(PC_PORT, message);
//	USART_SendString(PC_PORT, strBuff);
//
//}
//void DisplayAndStay(char *message)
//{
//	clrscr();
//	gotoxy(2,1);
//	lcdprint(message);
//	gotoxy(4,1);
//	lcdprint("Pree Key to Continue");
//	while(!(key_chk()));
//}
