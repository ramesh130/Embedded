
#define  __SYSTEM_INIT_C

#include "system_init.h"
#include "platform_config.h"
#include "pc_printer.h"
#include "pc_lcd.h"
#include "pc_eeprom.h"

#include "pc_pc_comm.h"

void System_Init()
{
	Init_Printer_Vars();
	RCC_Configure();
	GPIO_Configure();
	USART_Configure(PC_PORT, PC_USART_APB, PC_BITRATE/1.5, PC_APB_NUM);
	USART_Configure(RFID_PORT, RFID_USART_APB, RFID_BITRATE/1.5, RFID_APB_NUM);
	RealTimeClockConfigure();
	Timer_Configure();
	NVIC_Configure();
	sEE_Init();
	Glcd_Init();
	Init_ISR();
}
