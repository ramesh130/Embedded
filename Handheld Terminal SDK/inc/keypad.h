
#ifndef _PC_KEYPAD
#define _PC_KEYPAD

#ifdef  __KEYPAD_C
#define KEYPAD_SCOPE
#else
#define KEYPAD_SCOPE extern
#endif

KEYPAD_SCOPE u8 Get_KeyCode(u8 Shift);
KEYPAD_SCOPE u8 Get_KeyStatus(void);

#endif
