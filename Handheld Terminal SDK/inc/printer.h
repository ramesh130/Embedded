
#ifndef _H_PRINTER
#define _H_PRINTER

#include "platform.h"

#ifdef  __PRINTER_C
#define PRINTER_SCOPE
#else
#define PRINTER_SCOPE extern
#endif

PRINTER_SCOPE void Paper_Feed(u8 No_Lines);
PRINTER_SCOPE void Init_Printer_Vars(void);
PRINTER_SCOPE u8 GetPrinter_Status(void);
PRINTER_SCOPE u8 Start_Print(u8 *String, uc8 Font_H, uc8 Font_W);
PRINTER_SCOPE u8 Start_Head_Clean(u8 *String, uc8 Font_H, uc8 Font_W);

#endif
