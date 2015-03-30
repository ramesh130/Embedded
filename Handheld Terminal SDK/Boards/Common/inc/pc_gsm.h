
#ifndef __PC_GSM
#define __PC_GSM

#ifdef  __GSM_C
#define GSM_SCOPE
#else
#define GSM_SCOPE extern
#endif

#include "pc_gsm_commands.h"
#include "platform_config.h"
#include "gsm.h"
#include "pc_utils.h"
#include "pc_usart.h"



GSM_SCOPE u8 GSM_READY;      /* GSM Network Indicator */

#endif

