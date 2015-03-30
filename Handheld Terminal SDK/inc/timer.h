
#ifndef __TIMER_H
#define __TIMER_H

#ifdef  __TIMER_C
#define TIMER_SCOPE
#else
#define TIMER_SCOPE extern
#endif

#include "platform.h"

TIMER_SCOPE void StartTimer(void);
TIMER_SCOPE void StopTimer(void);

#endif


