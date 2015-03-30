
#define  __PC_COMM_C

#include "pc_pc_comm.h"

void PC_Configure(void)
{
	USART_Configure(PC_PORT, PC_USART_APB, PC_BITRATE/1.5, PC_APB_NUM);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  : USART_SendData
* Description    : Send a string to USARTx
* Input          : USART address and the string to be transfer.
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void PC_SendString(u8 Tx_Buf[])
{
	USART_SendString(PC_PORT, Tx_Buf);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void PC_SendChar(u8 Tx_Char)
{
	USART_SendChar(PC_PORT, Tx_Char);
}

vu8 PC_GetRxFlag(void)
{
	return PC_Rx_Flag;
}

vu8* PC_GetRxBuffer(void)
{
	return PC_Buffer;
}
