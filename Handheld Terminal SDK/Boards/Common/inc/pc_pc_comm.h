
#ifndef __PC_PC_COMM
#define __PC_PC_COMM

#ifdef  __PC_COMM_C
#define PC_COMM_SCOPE
#else
#define PC_COMM_SCOPE extern
#endif

#include "pc_comm.h"
#include "pc_usart.h"

PC_COMM_SCOPE void PC_Configure(void);

#endif


