
#ifndef __GPIO
#define __GPIO

#ifdef  __GPIO_C
#define GPIO_SCOPE
#else
#define GPIO_SCOPE extern
#endif

#include "platform.h"

GPIO_SCOPE u8 get_charger_ip(void);

#endif


