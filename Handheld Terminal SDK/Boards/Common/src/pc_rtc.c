#define  __RTC_C

#include "pc_rtc.h"

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Get_Date(u8 *Tmp_DD, u8 *Tmp_MM, u16 *Tmp_YY)
{
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	*Tmp_MM = BKP_ReadBackupRegister(BKP_DR2);

	PWR_BackupAccessCmd(ENABLE);
	*Tmp_DD = BKP_ReadBackupRegister(BKP_DR3);

	PWR_BackupAccessCmd(ENABLE);
	*Tmp_YY = BKP_ReadBackupRegister(BKP_DR4);
}

void Get_Time(u8 *Tmp_HH, u8 *Tmp_MM, u16 *Tmp_SS)
{
	vu32 temp_tim;
	temp_tim = RTC_GetCounter();
	*Tmp_HH = temp_tim / 3600;
	temp_tim = temp_tim % 3600;
	*Tmp_MM = temp_tim / 60;
	*Tmp_SS = temp_tim % 60;
}

/*******************************************************************************
* Function Name  : Time_Regulate
* Description    : Returns the time entered by user, using Hyperterminal.
* Input          : None
* Output         : None
* Return         : Current time RTC counter value
*******************************************************************************/
void Time_Regulate(u8 Tmp_HH, u8 Tmp_MM, u8 Tmp_SS)
{
	u32 Temp_Cnt = 0;

	Tmp_HH=hex_bcd(Tmp_HH);
	Tmp_MM=hex_bcd(Tmp_MM);
	Tmp_SS=hex_bcd(Tmp_SS);

	Temp_Cnt = (u32)(Tmp_HH*3600+ Tmp_MM*60 + Tmp_SS);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Change the current time */
	RTC_SetCounter(Temp_Cnt);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Date_Regulate(u8 Tmp_DD, u8 Tmp_MM, u16 Tmp_YY)
{
	/* Allow access to BKP Domain */
	Tmp_DD=hex_bcd(Tmp_DD);
	Tmp_MM=hex_bcd(Tmp_MM);
	Tmp_YY=hex_bcd(Tmp_YY);
	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR2, Tmp_MM);

	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR3, Tmp_DD);

	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR4, Tmp_YY);

	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR1, RTC_SET_CHECK);
}

