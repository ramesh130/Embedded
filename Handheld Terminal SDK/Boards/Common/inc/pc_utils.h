
#ifndef _H_UTILITYFUNCTIONS
#define _H_UTILITYFUNCTIONS

//#include<StructUnion.h>
//#include<Globals.h>
#include "platform_config.h"
#include "utils.h"

void pk_unpk(volatile unsigned char pk,volatile unsigned char *unpk);
unsigned char unpk_pk(volatile unsigned char *unpk);
unsigned char hex_bcd(volatile unsigned char hex);
void hex_asc(volatile long hex, volatile unsigned char *asc, volatile unsigned char dig);
long asc_hex(volatile unsigned char *asc, volatile unsigned char dig);
void rem_zeros(volatile unsigned char *asc, volatile unsigned char dig);
long get_mins(volatile unsigned char dt, volatile unsigned char mt, volatile unsigned char yr, volatile unsigned char hr, volatile unsigned char mn);
unsigned char hextoasc(volatile unsigned char temp);
unsigned char asctohex(volatile unsigned char temp);
long rndup_ammt(volatile long ammt);
void tim_hex_asc(void);
void Delay_mSec(u16 Count_mSec);
void Delay_100uSec(u16 Count_100uSec);

void tim_asc_hex(void);
void tim_hex_asc_print(void);
void printUartIntToString(volatile int val,u8 *message);
void DisplayAndStay(char *message);


//32 bit utility functions
#ifdef  __UTILS_C
#define UTILS_SCOPE
#else
#define UTILS_SCOPE extern
#endif

//#include <stm32f10x_type.h>
//#include "stm32f10x.h"
/* Macro to calculate the sizeof a variable */
#define SIZEOF(X) (s8 *)((&X+1) - (&X))

#define BYTE     8     /* No. Of Bits for Byte */
#define HALFWORD 16    /* No. Of Bits for Half-Word */
#define WORD     32    /* No. Of Bits for Word */

#endif
