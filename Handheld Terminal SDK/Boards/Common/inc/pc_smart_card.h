
#ifndef __PC_SMART_CARD_H
#define __PC_SMART_CARD_H

#ifdef  __SMART_CARD_C
#define SMART_CARD_SCOPE
#else
#define SMART_CARD_SCOPE extern
#endif

#include "smart_card.h"
#include "pc_usart.h"
#include "pc_lcd.h"
#include "pc_buzzer.h"
#include "pc_globals.h"
#include "pc_timer.h"

#define BUF_LEN		165
#define STRCHR		'#'
#define ENDCHR 		'\n'

SMART_CARD_SCOPE vu8 SMRTCARD_Buffer[PC_RX_SIZE];
SMART_CARD_SCOPE vu8 SMRTCARDDATA_Buffer[32];

#endif


