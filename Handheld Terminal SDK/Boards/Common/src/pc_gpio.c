
#define  __GPIO_C

#include"pc_gpio.h"

u8 get_charger_ip()
{
	if(READ_PORT_PIN(BAT_SENSE_PORT,BAT_SENSE))
		return 0;
	else
		return 1;
	//chk the pin status whn it 1 and whn it 0.
}
