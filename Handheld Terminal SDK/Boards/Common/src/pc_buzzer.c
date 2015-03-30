
#define  __BUZZER_C

#include "pc_buzzer.h"

void Clear_Buzzer()  //buzzer ON
{
	CLR_PORT_PIN(BUZZER_PIN_PORT,BUZZER_PIN);

}

void Set_Buzzer()  //buzzer OFF
{
	SET_PORT_PIN(BUZZER_PIN_PORT,BUZZER_PIN);

}
//------------------------------------------------------------------------
//	void beep(volatile unsigned char typ)
//	INPUTS	:	volatile unsigned char typ
//	OUTPUTS	:	void
//	depending on beep type it will make buzzer on & off.
void Beep(volatile unsigned char typ)
{
	u8 exit;
	unsigned char i, delcnt = 1;

	for(i = 0, exit = 0 ; (!exit) && (i < 3) ; i++)
	{
		Clear_Buzzer();
		switch(typ)
		{
		case NORM:
			Delay_mSec(50);
			exit = 1;
			break;
		case LONG:
			Delay_mSec(100);
			exit = 1;
			break;
		case SHRT:
			Delay_mSec(5);
			exit = 1;
			break;
		case OKKK:
			Delay_mSec(50);
			delcnt = 50;
			break;
		case ERRR:
			Delay_mSec(100);
			delcnt = 100;
			break;
		default:
			break;
		}
		Set_Buzzer();	//buzzer = 1;
		if(!exit)
			Delay_mSec(delcnt);
	}
}

