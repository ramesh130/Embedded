
#ifndef __UTILS_H
#define __UTILS_H


#include "platform.h"

//32 bit utility functions
#ifdef  __UTILS_C
#define UTILS_SCOPE
#else
#define UTILS_SCOPE extern
#endif




UTILS_SCOPE  void Delay(vu32 nCount);
UTILS_SCOPE  void Clrbuf(u8 *Str, u32 Len);

UTILS_SCOPE  float AtoF(s8 *str);
UTILS_SCOPE  u32   AtoI( u8 *str);
UTILS_SCOPE  void ItoA( const unsigned long value, unsigned char *str);

UTILS_SCOPE  void Rev_String(u8 *str);
UTILS_SCOPE  u16  Strlen( const u8 *str);
UTILS_SCOPE  u8   Rev_ByteBits(u8 byte);
UTILS_SCOPE  u32  Rev_WordBits(u32 byte);
UTILS_SCOPE  u16  Rev_HalfWordBits(u16 byte);

UTILS_SCOPE  u8 *strset(u8 *s, u16 ch);
UTILS_SCOPE  u8 *Strnset(u8 *str, u16 ch, u16 n);
UTILS_SCOPE  u8 *Strcpy(u8 *dest, const u8  *src);
UTILS_SCOPE  u8 *Strcat(u8 *dest, const u8  *src);
UTILS_SCOPE  u8 *Strncpy(u8 *dest, const u8 *src, u16 maxlen);

UTILS_SCOPE  s8  Strcmp(const u8 *s1, const u8 *s2);
UTILS_SCOPE  s8  Strncmp( const u8 *str1, const u8 *str2, u16 nob);

#endif
