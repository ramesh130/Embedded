
#define  __PLATFORM_CONFIG_C

#include "platform_config.h"

DMA_InitTypeDef   sEEDMA_InitStructure;

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void RCC_Configure(void)
{
	ErrorStatus HSEStartUpStatus;

	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);

		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);

		/* PLLCLK = 12MHz * 6 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);

		/* Enable PLL */
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08);
	}
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void RTC_Configure(void)
{
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset Backup Domain */
	BKP_DeInit();

	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);

	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Sets Alarm value to 24*3600 */
	RTC_SetAlarm(86400);



	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}


/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void GPIO_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure all unused GPIO port pins in Analog Input mode (floating input
	trigger OFF), this will reduce the power consumption and increase the device
	immunity against EMI/EMC *--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
		RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
		RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |
		RCC_APB2Periph_GPIOG , ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
		RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
		RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |
		RCC_APB2Periph_GPIOG, DISABLE);
	/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
	RCC_APB2PeriphClockCmd(GSM_APB, ENABLE);
	RCC_APB2PeriphClockCmd(GSM_PWR_EN_APB, ENABLE);
	RCC_APB2PeriphClockCmd(GSM_PWR_KEY_APB, ENABLE);
	RCC_APB2PeriphClockCmd(GSM_DTR_APB, ENABLE);
	RCC_APB2PeriphClockCmd(LCD_APB_D0_D7, ENABLE);
	RCC_APB2PeriphClockCmd(KEYPAD_APB, ENABLE);
	RCC_APB2PeriphClockCmd(PRN_APB1, ENABLE);
	RCC_APB2PeriphClockCmd(PRN_APB2, ENABLE);
	RCC_APB2PeriphClockCmd(PRN_APB3, ENABLE);
	RCC_APB2PeriphClockCmd(PRN_PWR_APB, ENABLE);
	RCC_APB2PeriphClockCmd(SPI_APB1, ENABLE);
	RCC_APB2PeriphClockCmd(SPI_APB2, ENABLE);
	/*************************23/02/10******************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	/* Disable the Serial Wire Jtag Debug Port SWJ-DP */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	/***************************************************************************/

	/* Configure USART1 Tx (PA.2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GSM_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GSM_GPIO, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA.3) as input floating */
	GPIO_InitStructure.GPIO_Pin  = GSM_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GSM_GPIO, &GPIO_InitStructure);

	/* Configure PC Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = PC_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(PC_GPIO, &GPIO_InitStructure);

	/* Configure PC Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = PC_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(PC_GPIO, &GPIO_InitStructure);
	/* Configure RFID Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = RFID_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(RFID_GPIO, &GPIO_InitStructure);

	/* Configure RFID Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = RFID_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RFID_GPIO, &GPIO_InitStructure);
	/* Configure LCD Data Pins D0 to D7 */
	GPIO_InitStructure.GPIO_Pin = LCD_D0 | LCD_D1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_D0_D7, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_D2 | LCD_D3 | LCD_D4|
		LCD_D5 | LCD_D6 | LCD_D7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_D0_D7, &GPIO_InitStructure);

	/* Configure LCD RS Pin */
	GPIO_InitStructure.GPIO_Pin = LCD_RS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_RS_PORT, &GPIO_InitStructure);

	/* Configure LCD RST Pin */
	GPIO_InitStructure.GPIO_Pin = LCD_RST;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_RST_PORT, &GPIO_InitStructure);

	/* Configure LCD RW Pin */
	GPIO_InitStructure.GPIO_Pin = LCD_RW;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_RW_PORT, &GPIO_InitStructure);

	/* Configure LCD CS1 Pin */
	GPIO_InitStructure.GPIO_Pin = LCD_CS1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_CS1_PORT, &GPIO_InitStructure);

	/* Configure LCD Backlight Pin */
	GPIO_InitStructure.GPIO_Pin = LCD_BKLT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_BKLT_PORT, &GPIO_InitStructure);

	/* Configure GSM PWR Key Pin */
	GPIO_InitStructure.GPIO_Pin = GSM_PWR_KEY;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GSM_PWRKEY_PORT, &GPIO_InitStructure);

	/* Configure GSM PWR Enable Key Pin */
	GPIO_InitStructure.GPIO_Pin = GSM_PWR_EN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GSM_PWR_EN_PORT, &GPIO_InitStructure);

	/* Configure GSM PWR Enable Key Pin */
	GPIO_InitStructure.GPIO_Pin = GSM_DTR;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GSM_DTR_PORT, &GPIO_InitStructure);

	/* Configure Keypad's Column Pins (O/P) */
	GPIO_InitStructure.GPIO_Pin = COL_0 | COL_1 | COL_2 | COL_3 | COL_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);

	/* Configure Keypad's Row Pins (I/P) */
	GPIO_InitStructure.GPIO_Pin = ROW_0 | ROW_1 | ROW_2 | ROW_3 | ROW_4 | ROW_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);

	/* Config. Printer's Strobe,Data,Clock,Latch,Motor Pins*/
	GPIO_InitStructure.GPIO_Pin = PRN_STB2 | PRN_STB3 | PRN_STB4 |
		PRN_STB5 | PRN_STB6 | PRN_MOT1 |
		PRN_MOT2 | PRN_MOT3 | PRN_MOT4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PRN_PORT2, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PRN_STB1 | PRN_CLK |
		PRN_LAT | PRN_DIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PRN_PORT1, &GPIO_InitStructure);

	/* Configure Printer's Paper Sense Pin */
	GPIO_InitStructure.GPIO_Pin = PRN_PAP_SENSE;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PRN_PAP_PORT, &GPIO_InitStructure);

	/* Configure Printer's Paper Thermistor Pin */
	GPIO_InitStructure.GPIO_Pin = PRN_TH1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PRN_TH1_PORT, &GPIO_InitStructure);

	/* Configure Printer's Head Up Sense Pin */
	GPIO_InitStructure.GPIO_Pin = PRN_HUP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PRN_HUP_PORT, &GPIO_InitStructure);

	/* Configure Printer's Head Power Control Pin */
	GPIO_InitStructure.GPIO_Pin = PRN_PWR_CTRL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PRN_PWR_CTRL_PORT, &GPIO_InitStructure);

	/* Configure SPI Flash's CS, SO, SCK Pins */
	GPIO_InitStructure.GPIO_Pin = SPI_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_CS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI_SCK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_SCK_PORT, &GPIO_InitStructure);

	/* Configure SPI Flash's SI Pin */
	GPIO_InitStructure.GPIO_Pin = SPI_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_MISO_PORT, &GPIO_InitStructure);


}
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void NVIC_Configure(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the Priority Grouping with 1 bit */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the Timer3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the Timer2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel                   = RTC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void Timer_Configure(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* Enable Clock for Timer-2 --*--*--*--*--*--*--*--*--*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 7200;
	TIM_TimeBaseStructure.TIM_Prescaler = 10;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Prescaler configuration */
	TIM_PrescalerConfig(TIM2, 10, TIM_PSCReloadMode_Immediate);

	/* Enable Timer2 Update Interrupt */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* Selects the internal clock for TIM2 */
	TIM_InternalClockConfig(TIM2);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

	/* Enable Clock for Timer-3 --*--*--*--*--*--*--*--*--*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 7200;
	TIM_TimeBaseStructure.TIM_Prescaler = 3;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* Prescaler configuration */
	TIM_PrescalerConfig(TIM3, 3, TIM_PSCReloadMode_Immediate);

	/* Enable Timer3 Update Interrupt */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	/* Selects the internal clock for TIM3 */
	TIM_InternalClockConfig(TIM3);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Output         : None
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
void USART_Configure(USART_TypeDef* USARTx, u32 APB_CLK, u32 Baudrate, u8 APB_Num)
{
	USART_InitTypeDef USART_InitStructure;

	if(APB_Num == 1)
	{
		RCC_APB1PeriphClockCmd(APB_CLK, ENABLE);
	}
	else
	{
		RCC_APB2PeriphClockCmd(APB_CLK, ENABLE);
	}
	/* USART configured as follow:
	- BaudRate    = As said by Baudrate variable
	- Word Length = 8 Bits
	- One Stop Bit
	- No parity
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit enabled */
	USART_InitStructure.USART_BaudRate   = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART */
	USART_Init(USARTx, &USART_InitStructure);


	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

	/* Enable the USART */
	USART_Cmd(USARTx, ENABLE);
}

void sEE_LowLevel_DeInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* sEE_I2C Peripheral Disable */
	I2C_Cmd(sEE_I2C, DISABLE);

	/* sEE_I2C DeInit */
	I2C_DeInit(sEE_I2C);

	/*!< sEE_I2C Periph clock disable */
	RCC_APB1PeriphClockCmd(sEE_I2C_CLK, DISABLE);

	/*!< GPIO configuration */
	/*!< Configure sEE_I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(sEE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sEE_I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
	GPIO_Init(sEE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

	/* Configure and enable I2C DMA TX Channel interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Configure and enable I2C DMA RX Channel interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
	NVIC_Init(&NVIC_InitStructure);

	/* Disable and Deinitialize the DMA channels */
	DMA_Cmd(sEE_I2C_DMA_CHANNEL_TX, DISABLE);
	DMA_Cmd(sEE_I2C_DMA_CHANNEL_RX, DISABLE);
	DMA_DeInit(sEE_I2C_DMA_CHANNEL_TX);
	DMA_DeInit(sEE_I2C_DMA_CHANNEL_RX);
}

/**
* @brief  Initializes peripherals used by the I2C EEPROM driver.
* @param  None
* @retval None
*/
void sEE_LowLevel_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/*!< sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_APB2PeriphClockCmd(sEE_I2C_SCL_GPIO_CLK | sEE_I2C_SDA_GPIO_CLK, ENABLE);

	/*!< sEE_I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(sEE_I2C_CLK, ENABLE);

	/*!< GPIO configuration */
	/*!< Configure sEE_I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(sEE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sEE_I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
	GPIO_Init(sEE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

	/* Configure and enable I2C DMA TX Channel interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Configure and enable I2C DMA RX Channel interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
	NVIC_Init(&NVIC_InitStructure);

	/*!< I2C DMA TX and RX channels configuration */
	/* Enable the DMA clock */
	RCC_AHBPeriphClockCmd(sEE_I2C_DMA_CLK, ENABLE);

	/* I2C TX DMA Channel configuration */
	DMA_DeInit(sEE_I2C_DMA_CHANNEL_TX);
	sEEDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)sEE_I2C_DR_Address;
	sEEDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;   /* This parameter will be configured durig communication */
	sEEDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;    /* This parameter will be configured durig communication */
	sEEDMA_InitStructure.DMA_BufferSize = 0xFFFF;            /* This parameter will be configured durig communication */
	sEEDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	sEEDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	sEEDMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
	sEEDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	sEEDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	sEEDMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	sEEDMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(sEE_I2C_DMA_CHANNEL_TX, &sEEDMA_InitStructure);

	/* I2C RX DMA Channel configuration */
	DMA_DeInit(sEE_I2C_DMA_CHANNEL_RX);
	DMA_Init(sEE_I2C_DMA_CHANNEL_RX, &sEEDMA_InitStructure);

	/* Enable the DMA Channels Interrupts */
	DMA_ITConfig(sEE_I2C_DMA_CHANNEL_TX, DMA_IT_TC, ENABLE);
	DMA_ITConfig(sEE_I2C_DMA_CHANNEL_RX, DMA_IT_TC, ENABLE);
}


/**
* @brief  Initializes DMA channel used by the I2C EEPROM driver.
* @param  None
* @retval None
*/
void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction)
{
	/* Initialize the DMA with the new parameters */
	if (Direction == sEE_DIRECTION_TX)
	{
		/* Configure the DMA Tx Channel with the buffer address and the buffer size */
		sEEDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
		sEEDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		sEEDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
		DMA_Init(sEE_I2C_DMA_CHANNEL_TX, &sEEDMA_InitStructure);
	}
	else
	{
		/* Configure the DMA Rx Channel with the buffer address and the buffer size */
		sEEDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
		sEEDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		sEEDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
		DMA_Init(sEE_I2C_DMA_CHANNEL_RX, &sEEDMA_InitStructure);
	}
}


/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
//void Get_Number_Display(u8 *Str)
//{
//	u8 temp_cnt = 0, chr;
//
//	Glcd_Cmd_Write( LCD_Display_ON);
//	Glcd_Select_Page( 5);
//	Glcd_Column_Cmd( 0x00);
//	do
//	{
//		while(Get_KeyStatus() == FALSE);
//		chr = Get_KeyCode();
//		if(chr != '*')
//		{
//			if(chr >= 'K' && chr <= 'M')
//			{
//				chr = (chr - 'K') + '1';
//				Str[temp_cnt++] = chr;
//				Glcd_Display_Byte(chr);
//			}
//			else if(chr >= 'P' && chr <= 'R')
//			{
//				chr = (chr - 'P') + '4';
//				Str[temp_cnt++] = chr;
//				Glcd_Display_Byte(chr);
//			}
//			else if(chr >= 'U' && chr <= 'W')
//			{
//				chr = (chr - 'U') + '7';
//				Str[temp_cnt++] = chr;
//				Glcd_Display_Byte(chr);
//			}
//			else if(chr == 'Z')
//			{
//				chr = '0';
//				Str[temp_cnt++] = chr;
//				Glcd_Display_Byte(chr);
//			}
//		}
//	}while(chr != '*');
//	Str[temp_cnt++] = '\0';
//}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
//void Get_String_Display(u8 *Str)
//{
//	u8 temp_cnt = 0, chr;
//
//	Glcd_Cmd_Write( LCD_Display_ON);
//	Glcd_Select_Page( 5);
//	Glcd_Column_Cmd( 0x00);
//	do
//	{
//		while(Get_KeyStatus() == FALSE);
//		chr = Get_KeyCode();
//		if(chr != '*')
//		{
//			if(chr != 's')
//				Str[temp_cnt] = chr;
//			else
//				Str[temp_cnt] = ' ';
//			Glcd_Display_Byte(Str[temp_cnt]);
//			temp_cnt++;
//		}
//	}while(chr != '*');
//	Str[temp_cnt++] = '\0';
//}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          :
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
//void Get_IP_Display(u8 *Str)
//{
//	u8 temp_cnt = 0, chr, ii = 0;
//
//	Glcd_Cmd_Write( LCD_Display_ON);
//	Glcd_Select_Page( 5);
//	Glcd_Column_Cmd( 0x00);
//	do
//	{
//		while(Get_KeyStatus() == FALSE);
//		chr = Get_KeyCode();
//		if(chr != '*')
//		{
//			if(chr >= 'K' && chr <= 'M')
//			{
//				chr = (chr - 'K') + '1';
//			}
//			else if(chr >= 'P' && chr <= 'R')
//			{
//				chr = (chr - 'P') + '4';
//			}
//			else if(chr >= 'U' && chr <= 'W')
//			{
//				chr = (chr - 'U') + '7';
//			}
//			else if(chr == 'Z')
//			{
//				chr = '0';
//			}
//			else if(chr == 's')
//			{
//				chr = '.';
//			}
//			Str[temp_cnt++] = chr;
//			Glcd_Display_Byte(chr);
//		}
//		ii++;
//	}while(chr != '*');
//	Str[temp_cnt++] = '\0';
//}

void RealTimeClockConfigure(void)
{
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		/* Backup data register value is not correct or not yet programmed (when
		the first time the program is executed) */
		/* RTC Configuration */
		RTC_Configure();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
}


