
#ifndef _PC_SPI_FLASH_H_
#define _PC_SPI_FLASH_H_

#ifdef __SPI_FLASH_C
#define SPI_SCOPE
#else
#define SPI_SCOPE  extern
#endif

#include <platform_config.h>
#include "spi_flash.h"

#define TOTAL_SPIPAGES     8192
#define TOTAL_SPIBLOCKS    1024
#define SPI_FLASH_PAGESIZE 528

#define BUFADDR_INDEX      0x00
#define PAGE_RD_BUFFER_OPCODE     0x53
#define PAGE_WR_OPCODE     0x82
#define PAGE_RD_OPCODE     0xD2
#define STATUS_OPCODE      0xD7
#define PAGE_ERASE_OPCODE  0x81
#define BLOCK_ERASE_OPCODE 0x50

SPI_SCOPE void SPI_FlashWait(void);
SPI_SCOPE void SendSPI_Command(u8 Refvalue);



u16 PGBYTS = 512;
u32 MB = 4194304;

SPI_SCOPE u8 SPI_FlashRead(void);
SPI_SCOPE s8 SPI_FlashPageRead(u16 Page_Cntr,u8 *Rd_Buffer,u16 Nob,u16 offset);
SPI_SCOPE s8 SPI_FlashReadBuffer(u16 Page_Cntr,u8 *Rd_Buffer,u16 Nob);
SPI_SCOPE s8 SPI_FlashReadPageToBuffer(u16 Page_Cntr);

SPI_SCOPE s8 SPI_FlashPageProgram(u16 Page_Cntr,u8 *Wr_Buffer, u16 Nob, u16 Offset);
SPI_SCOPE s8 SPI_FlashWriteBuffer(u16 Page_Cntr,u8 *Wr_Buffer, u16 Nob);

#endif
