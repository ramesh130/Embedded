
#ifndef __RTC
#define __RTC

#ifdef  __RTC_C
#define RTC_SCOPE
#else
#define RTC_SCOPE extern
#endif

#include "platform.h"

RTC_SCOPE void Get_Date(u8 *Tmp_DD, u8 *Tmp_MM, u16 *Tmp_YY);
RTC_SCOPE void Get_Time(u8 *Tmp_HH, u8 *Tmp_MM, u16 *Tmp_SS);
RTC_SCOPE void Time_Regulate(u8 Tmp_HH, u8 Tmp_MM, u8 Tmp_SS);
RTC_SCOPE void Date_Regulate(u8 Tmp_DD, u8 Tmp_MM, u16 Tmp_YY);

#endif


