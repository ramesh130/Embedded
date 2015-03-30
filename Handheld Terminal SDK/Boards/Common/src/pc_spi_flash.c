
#define __SPI_FLASH_C

#include "pc_spi_flash.h"

static vu32 DataToTransmit = 0;
static vu16 PageEraseCount = 0;
static vu16 BlockEraseCount = 0;



#ifdef SPI_DEBUG
static u8 DBug_Buf[100];
#endif

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void SendSPI_Command(u8 Refvalue)
{
	u8 data, next_test;

	data = Refvalue;
	next_test = 0x80;

	while(next_test)
	{
		/* Put Data On Serial-Out Pin */
		if((data & next_test))
			SET_PORT_PIN(SPI_MOSI_PORT, SPI_MOSI);
		else
			CLR_PORT_PIN(SPI_MOSI_PORT, SPI_MOSI);

		SET_PORT_PIN(SPI_SCK_PORT, SPI_SCK); /* Clock High	*/
		Delay_100uSec(1);					 /* Sync. Delay */
		CLR_PORT_PIN(SPI_SCK_PORT, SPI_SCK); /* Clock Low	*/

		next_test = next_test >> 1;  /* Next Bit to Test */
	}
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void SPI_FlashWait(void)
{
	u8 test;

	while(1)
	{
		CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
		SendSPI_Command(STATUS_OPCODE);    /* Request Flash Status */
		test = SPI_FlashRead(); 		   /* Read Data from Flash */
		SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
		if((test & 0x80) == 0x80)
			break;
	}
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
u8 SPI_FlashRead(void)
{
	vu8 data_read, cnt;

	for(cnt = 0, data_read = 0; cnt < 8; cnt++)
	{

		/*************************23/02/10******************************************/
		CLR_PORT_PIN(SPI_SCK_PORT, SPI_SCK); /* Clock Low	*/

		Delay_100uSec(2);					/* Sync. Delay */
		SET_PORT_PIN(SPI_SCK_PORT, SPI_SCK); /* Clock High	*/

		/**************************************************************************/

		if((READ_PORT_PIN(SPI_MISO_PORT, SPI_MISO)) != 0x00)
			data_read = data_read | 0x01;
		else
			data_read = data_read & 0xFE;

		if(cnt != 7)
			data_read = data_read << 1;
	}
	CLR_PORT_PIN(SPI_SCK_PORT, SPI_SCK); /* Clock Low */

	return ((u8)data_read);
}

s8 SPI_FlashPageProgram(u16 Page_Cntr, u8 *Wr_Buffer, u16 Nob, u16 Offset)
{
	u8  *pntr;
	u16 cnt;

	if(Page_Cntr > TOTAL_SPIPAGES) /* Page Number Error */
		return -1;



	DataToTransmit  = Page_Cntr;
	DataToTransmit  = DataToTransmit << 10;
	DataToTransmit |= Offset;//BUFADDR_INDEX;

	pntr = (u8 *)(&DataToTransmit);

#ifdef SPI_DEBUG
	USART_SendString(PC_PORT, "Write Page Address");
	USART_SendChar(PC_PORT, *(pntr+2));
	USART_SendChar(PC_PORT, *(pntr+1));
	USART_SendChar(PC_PORT, *(pntr+0));
#endif

	CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
	SendSPI_Command(PAGE_WR_OPCODE);
	SendSPI_Command(*(pntr+2));
	SendSPI_Command(*(pntr+1));
	SendSPI_Command(*(pntr+0));

	for(cnt = 0; cnt < Nob; cnt++)
	{
		SendSPI_Command(Wr_Buffer[cnt]);
#ifdef SPI_DEBUG
		ItoA32(Wr_Buffer[cnt], DBug_Buf);
		USART_SendString(PC_PORT, DBug_Buf);
#endif
	}
	SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
	SPI_FlashWait();
	DataToTransmit = 0;
	return 0;
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 :
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 SPI_FlashWriteBuffer(u16 Page_Cntr,u8 *Wr_Buffer, u16 Nob)
{
	u8  *pntr;
	u16 cnt;
	DataToTransmit  = Page_Cntr;


	pntr = (u8 *)(&DataToTransmit);

#ifdef SPI_DEBUG
	USART_SendString(PC_PORT, "Write Page Address");
	USART_SendChar(PC_PORT, *(pntr+2));
	USART_SendChar(PC_PORT, *(pntr+1));
	USART_SendChar(PC_PORT, *(pntr+0));
#endif

	CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
	SendSPI_Command(PAGE_WR_OPCODE);
	SendSPI_Command(*(pntr+2));
	SendSPI_Command(*(pntr+1));
	SendSPI_Command(*(pntr+0));

	for(cnt = 0; cnt < Nob; cnt++)
	{
		SendSPI_Command(Wr_Buffer[cnt]);
#ifdef SPI_DEBUG
		ItoA32(Wr_Buffer[cnt], DBug_Buf);
		USART_SendString(PC_PORT, DBug_Buf);
#endif
	}
	SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
	SPI_FlashWait();
	DataToTransmit = 0;
	return 0;
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 SPI_FlashReadBuffer(u16 Page_Cntr,u8 *Rd_Buffer,u16 Nob)
{
	u8  *pntr;
	u16 cntr;



	DataToTransmit = Page_Cntr;


	pntr = (u8 *)(&DataToTransmit);

#ifdef SPI_DEBUG
	USART_SendString(PC_PORT, "Read Page Address");
	USART_SendChar(PC_PORT, *(pntr+2));
	USART_SendChar(PC_PORT, *(pntr+1));
	USART_SendChar(PC_PORT, *(pntr+0));
#endif

	CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
	SendSPI_Command(PAGE_RD_OPCODE);
	SendSPI_Command(*(pntr+2));
	SendSPI_Command(*(pntr+1));
	SendSPI_Command(*(pntr+0));

	SendSPI_Command(0x00);
	SendSPI_Command(0x00);
	SendSPI_Command(0x00);
	SendSPI_Command(0x00);

	for(cntr = 0; cntr < Nob; cntr++)
	{
		Rd_Buffer[cntr] = SPI_FlashRead();
#ifdef SPI_DEBUG
		ItoA32(Rd_Buffer[cntr], DBug_Buf);
		USART_SendString(PC_PORT, DBug_Buf);
#endif
	}
	SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
	SPI_FlashWait();
	DataToTransmit = 0;
	return 0;
}


/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 SPI_FlashPageRead(u16 Page_Cntr,u8 *Rd_Buffer,u16 Nob,u16 offset)
{
	u8  *pntr;
	u16 cntr;

	if(Page_Cntr > TOTAL_SPIPAGES) /* Page Number Error */
		return -1;



	DataToTransmit = Page_Cntr;
	DataToTransmit = DataToTransmit << 10;
	DataToTransmit |= offset;//BUFADDR_INDEX;

	pntr = (u8 *)(&DataToTransmit);

#ifdef SPI_DEBUG
	USART_SendString(PC_PORT, "Read Page Address");
	USART_SendChar(PC_PORT, *(pntr+2));
	USART_SendChar(PC_PORT, *(pntr+1));
	USART_SendChar(PC_PORT, *(pntr+0));
#endif

	CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
	SendSPI_Command(PAGE_RD_OPCODE);
	SendSPI_Command(*(pntr+2));
	SendSPI_Command(*(pntr+1));
	SendSPI_Command(*(pntr+0));

	SendSPI_Command(0x00);
	SendSPI_Command(0x00);
	SendSPI_Command(0x00);
	SendSPI_Command(0x00);

	for(cntr = 0; cntr < Nob; cntr++)
	{
		Rd_Buffer[cntr] = SPI_FlashRead();
#ifdef SPI_DEBUG
		ItoA32(Rd_Buffer[cntr], DBug_Buf);
		USART_SendString(PC_PORT, DBug_Buf);
#endif
	}
	SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
	SPI_FlashWait();
	DataToTransmit = 0;
	return 0;
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 SPIFlash_PageErase(u16 Start_Page, u16 End_Page)
{
	u8  *eptr;
	u16 cntr;

	if(End_Page > TOTAL_SPIPAGES)
		return -1;

	if(Start_Page > End_Page)
		return -2;

	eptr = (u8 *)(&PageEraseCount);

	for(cntr = Start_Page; cntr < End_Page; cntr++)
	{
		PageEraseCount = cntr << 2;

#ifdef	SPI_DEBUG
		USART_SendString(PC_PORT, "Page Address");
		USART_SendChar(PC_PORT, *(eptr));
		USART_SendChar(PC_PORT, *(eptr+1));
#endif

		CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
		SendSPI_Command(PAGE_ERASE_OPCODE);
		SendSPI_Command(*(eptr+1));
		SendSPI_Command(*(eptr));
		SendSPI_Command(0x00);
		SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
		SPI_FlashWait();
	}
	PageEraseCount = 0;
	return 0;
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 SPIFlash_BlockErase(u16 Start_Block, u16 End_Block)
{
	u8  *bptr;

	u16 cntr;

	if(End_Block > TOTAL_SPIBLOCKS)
		return -1;

	if(Start_Block > End_Block)
		return -2;

	bptr = (u8 *)(&BlockEraseCount);

	for(cntr = Start_Block; cntr < End_Block; cntr++)
	{
		BlockEraseCount = cntr << 5;

#ifdef	SPI_DEBUG
		USART_SendString(PC_PORT, "Block Address");
		USART_SendChar(PC_PORT, *(bptr));
		USART_SendChar(PC_PORT, *(bptr+1));
#endif

		CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
		SendSPI_Command(BLOCK_ERASE_OPCODE);
		SendSPI_Command(*(bptr+1));
		SendSPI_Command(*(bptr));
		SendSPI_Command(0x00);
		SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
		SPI_FlashWait();

#ifdef	SPI_DEBUG
		ItoA32(cntr, temp_buf);
		USART_SendString(PC_PORT, temp_buf);
#endif
	}
	BlockEraseCount = 0;
	return 0;
}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description	 :
* Input 		 :
* Return		 : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
s8 SPI_FlashReadPageToBuffer(u16 Page_Cntr) //Ramesh
{
	u8  *pntr;

	DataToTransmit = Page_Cntr;
	DataToTransmit = DataToTransmit << 10;
	DataToTransmit |= BUFADDR_INDEX; //Dont care bits

	pntr = (u8 *)(&DataToTransmit);

#ifdef SPI_DEBUG
	USART_SendString(PC_PORT, "Read Page Address");
	USART_SendChar(PC_PORT, *(pntr+2));
	USART_SendChar(PC_PORT, *(pntr+1));
	USART_SendChar(PC_PORT, *(pntr+0));
#endif

	CLR_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select Low */
	SendSPI_Command(PAGE_RD_BUFFER_OPCODE);
	SendSPI_Command(*(pntr+2));
	SendSPI_Command(*(pntr+1));
	SendSPI_Command(*(pntr+0));

	SET_PORT_PIN(SPI_CS_PORT, SPI_CS); /* Chip Select High */
	SPI_FlashWait();
	DataToTransmit = 0;
	return 0;
}

u8 SPI_FlashWriteMemory(u16 flshaddr, u8 *buff, u16 length)
{
	volatile unsigned int data_no, mm_page_no,cnt=0;
	volatile long templength, kk;
	volatile unsigned orglength=length;
	if(length<1)
		return 0;
	mm_page_no = flshaddr / PGBYTS;
	data_no = flshaddr % PGBYTS;


	do
	{

		if((data_no + length)  >  PGBYTS)
		{
			templength = PGBYTS - data_no;
		}
		else
			templength = length;
		SPI_FlashReadPageToBuffer(mm_page_no); //Ramesh
		SPI_FlashPageProgram(mm_page_no,buff, templength,data_no);

		length = length - templength;
		if(length  >  0)
		{
			mm_page_no = mm_page_no + 1;
			data_no = 0;
			buff = buff +  templength;
		}
	}while(length  >  0);

	return (1);

}


u8 SPI_FlashReadMemory(u16 flshaddr, u8 *buff, u16 length)
{
	volatile unsigned int data_no, mm_page_no;
	volatile long kk, jj;
	volatile unsigned char cc;
	volatile long templength;

	if((flshaddr + length) > MB)
		return (0);

	mm_page_no = flshaddr / PGBYTS;
	data_no = flshaddr % PGBYTS;

	do
	{
		if((data_no + length)  >  PGBYTS)
		{
			templength = PGBYTS - data_no;
		}
		else
			templength = length;


		SPI_FlashPageRead(mm_page_no,buff,templength,data_no);

		length = length - templength;
		if(length  >  0)
		{
			mm_page_no = mm_page_no + 1;
			data_no = 0;
			buff = buff +  templength;
		}
	}while(length  >  0);

	return (1);


}
