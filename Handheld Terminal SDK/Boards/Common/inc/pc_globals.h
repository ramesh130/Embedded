
#ifndef _PC_GLOBALS_H
#define _PC_GLOBALS_H

#ifdef  __GLOBALS_C
#define GLOBALS_SCOPE
#else
#define GLOBALS_SCOPE extern
#endif

#include "platform_config.h"

#define PC_RX_SIZE 300

GLOBALS_SCOPE vu8 PC_Buffer[PC_RX_SIZE];
GLOBALS_SCOPE vu8 PC_Rx_Cnt;
GLOBALS_SCOPE vu8 PC_Rx_Flag;
GLOBALS_SCOPE vu32 smrt_cnt;
GLOBALS_SCOPE vu8 rec_flag_rfid;
GLOBALS_SCOPE vu8 tout_err;

GLOBALS_SCOPE vu8 rec_flag;

#endif
