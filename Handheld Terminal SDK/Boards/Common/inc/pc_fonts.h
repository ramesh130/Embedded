
#ifndef _FONTS_H
#define _FONTS_H

#ifdef  __FONTS_C
#define FONTS_SCOPE
#else
#define FONTS_SCOPE extern
#endif

#include "stm32f10x.h"

#define BATT_WIDTH  15 /* Width of Battery Icon -- Shld be in the First Line of LCD */
#define NTWRK_WIDTH 17 /* Width of Network Icon -- Shld be in the First Line of LCD */

FONTS_SCOPE uc8 Batt_Full[];
FONTS_SCOPE uc8 Batt_L1[];
FONTS_SCOPE uc8 Batt_L2[];

FONTS_SCOPE uc8 Ntwrk_Full[];
FONTS_SCOPE uc8 Ntwrk_NA[];
FONTS_SCOPE uc8 Ntwrk_L1[];
FONTS_SCOPE uc8 Ntwrk_L2[];
FONTS_SCOPE uc8 Ntwrk_L3[];

FONTS_SCOPE uc16 table_8x6[];
FONTS_SCOPE uc16 table_8x8[];
FONTS_SCOPE uc16 table_8x12[];
FONTS_SCOPE uc16 table_12x8[];
FONTS_SCOPE uc16 table_16x12[];
FONTS_SCOPE uc16 table_16x6[];
FONTS_SCOPE uc16 norm_font[];
FONTS_SCOPE uc16 head_clean_16x12[];

#endif
