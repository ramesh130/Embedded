
#ifndef _PC_H_PRINTER
#define _PC_H_PRINTER

#ifdef  __PRINTER_C
#define PRINTER_SCOPE
#else
#define PRINTER_SCOPE extern
#endif

#include "printer.h"
#include "platform_config.h"
#include "pc_fonts.h"

#define NUM_OF_DOTS 384

PRINTER_SCOPE vu8  PrintBusy;
PRINTER_SCOPE vu8  StopPrint;
PRINTER_SCOPE vu8  PrintAbort;
PRINTER_SCOPE vu8  PrintOv_Flag;
PRINTER_SCOPE vu8  PrintStart_Flag;
PRINTER_SCOPE vu8  Print_Sol_State;
PRINTER_SCOPE vu8  MotorSteps_state;
PRINTER_SCOPE vu8  print_buf[50];


PRINTER_SCOPE vu16  Dot_Buffer[NUM_OF_DOTS];

PRINTER_SCOPE void Init_Printer_Vars(void);
PRINTER_SCOPE void Set_Line(u8 *Str, uc8 Line, uc8 Font_H, uc8 Font_W);
PRINTER_SCOPE u8 GetHeightWidth(volatile u8 Fonth,unsigned char *FontH,unsigned char *Fontw);

#endif
