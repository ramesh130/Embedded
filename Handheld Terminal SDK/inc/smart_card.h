
#ifndef __SMART_CARD_H
#define __SMART_CARD_H

#ifdef  __SMART_CARD_C
#define SMART_CARD_SCOPE
#else
#define SMART_CARD_SCOPE extern
#endif

#include "platform.h"

#define READ		'R'
#define AUTH_READ	'X'
#define WRITE		'W'
#define AUTH_WRITE	'Y'
#define DECREMENT	'Q'
#define AUTH_DEC	'L'
#define INCREMENT	'O'
#define AUTH_INC	'K'
#define POLL		'P'
#define POL_STOP	'0'
#define POL_PRES	'1'
#define POL_AUTH	'2'
#define WRITE_KEYS	'J'

SMART_CARD_SCOPE void Smart_Card_Configure(void);

#endif
