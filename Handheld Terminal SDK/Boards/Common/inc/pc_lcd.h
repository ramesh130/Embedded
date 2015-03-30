
#ifndef _PC_LCD
#define _PC_LCD

#include "lcd.h"
#include "pc_utils.h"
#include "platform_config.h"
#include "pc_fonts.h"

LCD_SCOPE u8 double_height;
LCD_SCOPE u8 double_width;

#ifdef __GLCD_C
#define LCD_SCOPE
#else
#define LCD_SCOPE extern
#endif

#include "stm32f10x.h"

#define MAX_PAGES    8
#define MAX_ROWS     64
#define MAX_COLUMNS  128

#define GSM_BATT_PAGE  0 /* GSM ICON Page */

/*-*-*-*-*-*-*-*-*-*-* LCD Commands *-*-*-*-*-*-*-*-*-*-*/
#define LCD_Display_ON          0xAF
#define LCD_Display_OFF         0xAE

#define LCD_Coladdr_MSB          0x10
#define LCD_Coladdr_LSB          0x00

#define LCD_Seg_Normal_Dir      0xA0
#define LCD_Seg_Reverse_Dir     0xA1

#define LCD_Reverse_Display     0xA7
#define LCD_Normal_Display      0xA6

#define LCD_Entire_Disp_Rev     0xA5
#define LCD_Entire_Disp_Normal  0xA4

#define LCD_Bias_0              0xA2
#define LCD_Bias_1              0xA3

#define LCD_Col_Normal_Dir      0xC0
#define LCD_Col_Reverse_Dir     0xC8

#define LCD_Static_Inductor_ON  0xAD
#define LCD_Static_Inductor_OFF 0xAC

#define LCD_Contrast            0x17
#define LCD_Reg_Res_Ratio       0x24
#define LCD_InitDisp_Line       0x40  /* Column 0 Addr */
#define LCD_Power_Control       0x2F
#define LCD_Software_Reset      0xE2
#define LCD_Ref_Voltage_Mode    0x81

#define LCD_Page_Addr0          0xB0
#define LCD_Page_Addr1          0xB1
#define LCD_Page_Addr2          0xB2
#define LCD_Page_Addr3          0xB3
#define LCD_Page_Addr4          0xB4
#define LCD_Page_Addr5          0xB5
#define LCD_Page_Addr6          0xB6
#define LCD_Page_Addr7          0xB7
#define LCD_Page_Addr8          0xB8

LCD_SCOPE void Glcd_Init(void);
LCD_SCOPE void Glcd_Cmd_Write(u8 Cmd);
LCD_SCOPE void Glcd_Data_Write(u8 Data);
LCD_SCOPE void Send_Data_To_LCD(u8 Data);
LCD_SCOPE void Glcd_Column_Cmd( u8 Column);
LCD_SCOPE s8 Glcd_Select_Page( u8 Page);
LCD_SCOPE void Glcd_Elongate(volatile unsigned char disp_temp, volatile unsigned char *hi_part, volatile unsigned char *lo_part);

#endif
