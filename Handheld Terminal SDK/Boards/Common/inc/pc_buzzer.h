
#ifndef _PC_BUZZER
#define _PC_BUZZER

#ifdef  __BUZZER_C
#define BUZZER_SCOPE
#else
#define BUZZER_SCOPE extern
#endif

#include "platform_config.h"
#include "buzzer.h"

BUZZER_SCOPE void Set_Buzzer(void);
BUZZER_SCOPE void Clear_Buzzer(void);

#endif
