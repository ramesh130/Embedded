
#ifndef __PC_USART
#define __PC_USART

#ifdef  __USART_C
#define USART_SCOPE
#else
#define USART_SCOPE extern
#endif

#include "platform_config.h"
#include "stm32f10x_it.h"

USART_SCOPE void USART_SendChar(USART_TypeDef* USARTx, u8 Tx_Char);
USART_SCOPE void USART_SendString(USART_TypeDef* USARTx, u8 Tx_Buf[]);

#endif


