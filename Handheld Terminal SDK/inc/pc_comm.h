
#ifndef __PC_COMM
#define __PC_COMM

#ifdef  __PC_COMM_C
#define PC_COMM_SCOPE
#else
#define PC_COMM_SCOPE extern
#endif

#include "platform.h"

PC_COMM_SCOPE void PC_SendChar(u8 Tx_Char);
PC_COMM_SCOPE void PC_SendString(u8 Tx_Buf[]);
PC_COMM_SCOPE vu8 PC_GetRxFlag(void);
PC_COMM_SCOPE vu8* PC_GetRxBuffer(void);

#endif


