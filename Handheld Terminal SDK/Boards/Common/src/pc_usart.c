
#define  __USART_C

#include "pc_usart.h"

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  : USART_SendData
* Description    : Send a string to USARTx
* Input          : USART address and the string to be transfer.
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void USART_SendString(USART_TypeDef* USARTx, u8 Tx_Buf[])
{
	s16 index;
	for(index = 0; Tx_Buf[index] != '\0'; index++)
	{
		USART_SendChar(USARTx, Tx_Buf[index]);
	}
	USART_SendChar(USARTx, '\r');
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void USART_SendChar(USART_TypeDef* USARTx, u8 Tx_Char)
{
	/* Loop until the end of transmit */
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);

	USART_SendData(USARTx, Tx_Char);
}


