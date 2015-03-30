
#define  __TIMER_C

#include "pc_timer.h"

void StartTimer()
{
TIM_Cmd(TIM2, ENABLE);
}

void StopTimer()
{
TIM_Cmd(TIM2, DISABLE);
}
