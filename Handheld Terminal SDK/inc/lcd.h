
#ifndef _LCD
#define _LCD

#include "platform.h"

#ifdef __GLCD_C
#define LCD_SCOPE
#else
#define LCD_SCOPE extern
#endif
/* Graphics LCD Specific Function Prototypes */
LCD_SCOPE void Glcd_Clear_Display( void);
LCD_SCOPE void Glcd_Display_Byte( u8 Chr);
LCD_SCOPE void Glcd_Disp_Batt_ChargeInd(void);
LCD_SCOPE void Glcd_Display_BMP( char *Bmpstr);
LCD_SCOPE void Glcd_Disp_Ntwrk_Signal(u8 Level);
LCD_SCOPE void Glcd_Display_Char( u8 Chr, u8 Page_no);
LCD_SCOPE void Glcd_Display_String( u8 *String, u8 Page_no);
LCD_SCOPE void Glcd_Display_On(void);
LCD_SCOPE void Glcd_Display_Off(void);
LCD_SCOPE void Glcd_Set_Contrast(void);
LCD_SCOPE void Glcd_Goto_XY(u8 row, u8 col);

#endif
