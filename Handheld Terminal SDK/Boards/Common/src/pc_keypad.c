
#define __KEYPAD_C

#include "pc_keypad.h"

u8 keypad_table[2][30]=
{
	{'*', 5, 10, 15, 20, 25,		//	LOWER FUNCTIONS.
	'<', 6, 11, 16, 21, 26,
	'^', 7,'1','4','7', 27,
	'V', 8,'2','5','8','0',
	4, 9,'3','6','9','#'},

	{'*','D','I','N','S', 25, 		//	UPPER FUNCTIONS.
	'A','E','J','O','T','X',
	'B','F','K','P','U','Y',
	'C','G','L','Q','V','Z',
	4 ,'H','M','R','W','#'}
};
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 Get_KeyStatus(void)
{
	u8 retval = 0xff;

	CLR_PORT_PIN(KEY_PORT, COL_0 | COL_1 | COL_2 | COL_3 | COL_4);
	Delay_mSec(10);
	retval = READ_PORT_PIN(KEY_PORT, ROW_0) & READ_PORT_PIN(KEY_PORT, ROW_1) &
		READ_PORT_PIN(KEY_PORT, ROW_2) & READ_PORT_PIN(KEY_PORT, ROW_3) &
		READ_PORT_PIN(KEY_PORT, ROW_4) & READ_PORT_PIN(KEY_PORT, ROW_5);
	if(retval == 0)
		return TRUE;   //A key is pressed
	else
		return FALSE;  // No key is pressed
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 Get_KeyCode(u8 Shift)
{
	u8 chr = 0;
	unsigned char shftt = 0;
	if(Shift)
		shftt = 1;
	else
		shftt = 0;

	if(Get_KeyStatus() == FALSE)
		return 0; // No key is pressed, return

	/* For Col_0 */
	GPIO_SetBits(KEY_PORT, COL_0 | COL_1 | COL_2 | COL_3 | COL_4);
	GPIO_ResetBits(KEY_PORT, COL_0);
	if(READ_PORT_PIN(KEY_PORT, ROW_0) == 0)
	{
		chr = (keypad_table[shftt][0]);
	}
	else if(READ_PORT_PIN(KEY_PORT, ROW_1) == 0)
	{
		chr = (keypad_table[shftt][1]);
	}
	else if(READ_PORT_PIN(KEY_PORT, ROW_2) == 0)
	{
		chr = (keypad_table[shftt][2]);
	}
	else if(READ_PORT_PIN(KEY_PORT, ROW_3) == 0)
	{
		chr = (keypad_table[shftt][3]);
	}
	else if(READ_PORT_PIN(KEY_PORT, ROW_4) == 0)
	{
		chr = (keypad_table[shftt][4]);
	}
	else if(READ_PORT_PIN(KEY_PORT, ROW_5) == 0)
	{
		chr = (keypad_table[shftt][5]);
	}
	if(chr == 0)
	{
		/* For Col_1 */
		GPIO_SetBits(KEY_PORT, COL_0 | COL_1 | COL_2 | COL_3 | COL_4);
		GPIO_ResetBits(KEY_PORT, COL_1);
		if(READ_PORT_PIN(KEY_PORT, ROW_0) == 0)
		{
			chr = (keypad_table[shftt][6]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_1) == 0)
		{
			chr = (keypad_table[shftt][7]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_2) == 0)
		{
			chr = (keypad_table[shftt][8]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_3) == 0)
		{
			chr = (keypad_table[shftt][9]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_4) == 0)
		{
			chr = (keypad_table[shftt][10]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_5) == 0)
		{
			chr = (keypad_table[shftt][11]);
		}
	}

	if( chr == 0)
	{
		/* For Col_2 */
		GPIO_SetBits(KEY_PORT, COL_0 | COL_1 | COL_2 | COL_3 | COL_4);
		GPIO_ResetBits(KEY_PORT, COL_2);
		if(READ_PORT_PIN(KEY_PORT, ROW_0) == 0)
		{
			chr = (keypad_table[shftt][12]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_1) == 0)
		{
			chr = (keypad_table[shftt][13]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_2) == 0)
		{
			chr = (keypad_table[shftt][14]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_3) == 0)
		{
			chr = (keypad_table[shftt][15]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_4) == 0)
		{
			chr = (keypad_table[shftt][16]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_5) == 0)
		{
			chr = (keypad_table[shftt][17]);
		}
	}

	if( chr == 0)
	{
		/* For Col_3 */
		GPIO_SetBits(KEY_PORT, COL_0 | COL_1 | COL_2 | COL_3 | COL_4);
		GPIO_ResetBits(KEY_PORT, COL_3);
		if(READ_PORT_PIN(KEY_PORT, ROW_0) == 0)
		{
			chr = (keypad_table[shftt][18]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_1) == 0)
		{
			chr = (keypad_table[shftt][19]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_2) == 0)
		{
			chr = (keypad_table[shftt][20]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_3) == 0)
		{
			chr = (keypad_table[shftt][21]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_4) == 0)
		{
			chr = (keypad_table[shftt][22]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_5) == 0)
		{
			chr = (keypad_table[shftt][23]);
		}
	}

	if( chr == 0)
	{
		/* For Col_4 */
		GPIO_SetBits(KEY_PORT, COL_0 | COL_1 | COL_2 | COL_3 | COL_4);
		GPIO_ResetBits(KEY_PORT, COL_4);
		if(READ_PORT_PIN(KEY_PORT, ROW_0) == 0)
		{
			chr = (keypad_table[shftt][24]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_1) == 0)
		{
			chr = (keypad_table[shftt][25]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_2) == 0)
		{
			chr = (keypad_table[shftt][26]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_3) == 0)
		{
			chr = (keypad_table[shftt][27]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_4) == 0)
		{
			chr = (keypad_table[shftt][28]);
		}
		else if(READ_PORT_PIN(KEY_PORT, ROW_5) == 0)
		{
			chr = (keypad_table[shftt][29]);
		}
	}

	while(Get_KeyStatus() == TRUE); //Loop till the Key is Released

	return (chr);
}




