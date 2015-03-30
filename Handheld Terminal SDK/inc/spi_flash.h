
#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_

#ifdef __SPI_FLASH_C
#define SPI_SCOPE
#else
#define SPI_SCOPE  extern
#endif

#include "platform.h"


SPI_SCOPE s8 SPIFlash_PageErase(u16 Start_Page, u16 End_Page);
SPI_SCOPE s8 SPIFlash_BlockErase(u16 Start_Block, u16 End_Block);

SPI_SCOPE u8 SPI_FlashReadMemory(u16 Page_Addr, u8 *Rd_Buffer, u16 Nob);
SPI_SCOPE u8 SPI_FlashWriteMemory(u16 Page_Addr, u8 *Wr_Buffer, u16 Nob);

#endif
