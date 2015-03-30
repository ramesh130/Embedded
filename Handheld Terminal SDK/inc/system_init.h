
#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef  __SYSTEM_INIT_C
#define SYSTEM_INIT_SCOPE
#else
#define SYSTEM_INIT_SCOPE extern
#endif

SYSTEM_INIT_SCOPE void System_Init(void);

#endif
