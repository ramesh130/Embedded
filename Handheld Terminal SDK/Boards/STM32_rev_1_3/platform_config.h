
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#ifdef  __PLATFORM_CONFIG_C
#define PLATFORM_SCOPE
#else
#define PLATFORM_SCOPE extern
#endif

#include "stm32f10x.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_i2c.h"

#include "pc_utils.h"



#define RTC_SET_CHECK 0xA5A5
#define DEFAULT_DAY   0x00
#define DEFAULT_MONTH 0x00
#define DEFAULT_YEAR  0x00

#define SET_PORT_PIN(PORT, PIN) GPIO_SetBits(PORT, PIN)
#define CLR_PORT_PIN(PORT, PIN) GPIO_ResetBits(PORT, PIN)

#define WRITE_PORT(PORT, DATA)  GPIO_Write(PORT, DATA)
#define WRITE_PORT_PIN(PORT, PIN, BIT) GPIO_WriteBit(PORT, PIN, BIT)

#define READ_PORT_PIN(PORT, PIN)  GPIO_ReadInputDataBit(PORT, PIN)

/*-*-*-*-*-*-*- Keypad Related Macros & Variables -*-*-*-*-*-*-*/
#define KEY_PORT    GPIOE
#define KEYPAD_APB	RCC_APB2Periph_GPIOE

#define KEY_DATASHFT  5
#define KEY_DATAMASK  0x07E0

#define KEY_STAT_TEST 0x001F

#define COL_0  GPIO_Pin_0
#define COL_1  GPIO_Pin_1
#define COL_2  GPIO_Pin_2
#define COL_3  GPIO_Pin_3
#define COL_4  GPIO_Pin_4

#define ROW_0  GPIO_Pin_5
#define ROW_1  GPIO_Pin_6
#define ROW_2  GPIO_Pin_7
#define ROW_3  GPIO_Pin_8
#define ROW_4  GPIO_Pin_9
#define ROW_5  GPIO_Pin_10

#define CLR_C0() GPIO_ResetBits(KEY_PORT, COL_0)
#define CLR_C1() GPIO_ResetBits(KEY_PORT, COL_1)
#define CLR_C2() GPIO_ResetBits(KEY_PORT, COL_2)
#define CLR_C3() GPIO_ResetBits(KEY_PORT, COL_3)
#define CLR_C4() GPIO_ResetBits(KEY_PORT, COL_4)
/*-*-*-*-*-*-*- PC Related Macros & Variables -*-*-*-*-*-*-*/
#define PC_TX        	GPIO_Pin_9
#define PC_RX	     	GPIO_Pin_10
#define PC_GPIO      	GPIOA
#define PC_PORT      	USART1
#define PC_APB		 	RCC_APB2Periph_GPIOA
#define PC_APB_NUM   	2             /* 1 = APB1 Clock, 2 = APB2 Clock */
#define PC_USART_APB 	RCC_APB2Periph_USART1

#define PC_BITRATE 115200  /* GSM Baudrate             */
/*-*-*-*-*-*-*- RFID Related Macros & Variables -*-*-*-*-*-*-*/
#define RFID_TX        	GPIO_Pin_10
#define RFID_RX	     	GPIO_Pin_11
#define RFID_GPIO      	GPIOB
#define RFID_PORT      	USART3
#define RFID_APB		RCC_APB2Periph_GPIOB
#define RFID_APB_NUM   	1             /* 1 = APB1 Clock, 2 = APB2 Clock */
#define RFID_USART_APB 	RCC_APB1Periph_USART3

#define RFID_BITRATE   	38400 //115200 //19200 //57600 //38400//57600//115200//9600//38400

/*-*-*-*-*-*-*- GSM Related Macros & Variables -*-*-*-*-*-*-*/
#define GSM_PWR_EN      GPIO_Pin_9
#define GSM_PWR_EN_PORT GPIOD
#define GSM_PWR_EN_APB	RCC_APB2Periph_GPIOD

#define GSM_PWR_ENABLE()  GPIO_SetBits(GSM_PWR_EN_PORT, GSM_PWR_EN)
#define GSM_PWR_DISABLE() GPIO_ResetBits(GSM_PWR_EN_PORT, GSM_PWR_EN)

#define GSM_PWR_KEY     GPIO_Pin_10
#define GSM_PWRKEY_PORT	GPIOD
#define GSM_PWR_KEY_APB	RCC_APB2Periph_GPIOD

#define GSM_PWR_KEY_OFF() GPIO_ResetBits(GSM_PWRKEY_PORT, GSM_PWR_KEY)
#define GSM_PWR_KEY_ON()  GPIO_SetBits(GSM_PWRKEY_PORT, GSM_PWR_KEY)

#define GSM_DTR       GPIO_Pin_4
#define GSM_DTR_PORT	GPIOA
#define GSM_DTR_APB	  RCC_APB2Periph_GPIOA

#define GSM_GSM_DTR_OFF() GPIO_ResetBits(GSM_DTR_PORT, GSM_DTR)
#define GSM_GSM_DTR_ON()  GPIO_SetBits(GSM_DTR_PORT, GSM_DTR)

#define GSM_TX        GPIO_Pin_2
#define GSM_RX	      GPIO_Pin_3
#define GSM_GPIO      GPIOA
#define GSM_PORT      USART2
#define GSM_APB		  RCC_APB2Periph_GPIOA
#define GSM_APB_NUM   1             /* 1 = APB1 Clock, 2 = APB2 Clock */
#define GSM_USART_APB RCC_APB1Periph_USART2

#define GSM_BITRATE 9600  /* GSM Baudrate             */
#define GSM_RX_SIZE 150   /* GSM Receive Buffer Size  */
#define GSM_TX_SIZE 512   /* GSM Transmit Buffer Size */

PLATFORM_SCOPE u16 GSM_Rx_Cnt;			/* Rx Characters Count   */

PLATFORM_SCOPE u8 GSM_Flag;
PLATFORM_SCOPE u8 GSM_Rx_Char;     /* Present  Rx Character */
PLATFORM_SCOPE u8 GSM_Prev_Char;   /* Previous Rx Character */
PLATFORM_SCOPE u8 GSM_Check_SendOk;/* "SEND OK" check flag */

PLATFORM_SCOPE u8 GSM_Tmr_OV_Flg;
PLATFORM_SCOPE u8 GSM_Time_Delay;
PLATFORM_SCOPE u8 GSM_Tmr_Stat_Flg;

PLATFORM_SCOPE vu8 GSM_Rx_Buffer[GSM_RX_SIZE];     /* GSM Receive Buffer   */
PLATFORM_SCOPE vu8 GSM_Tx_Buffer[GSM_TX_SIZE]; /* GSM Transmit Buffer  */

/*-*-*-*-*-*-*- LCD Related Macros & Variables -*-*-*-*-*-*-*/
#define LCD_D0    GPIO_Pin_0
#define LCD_D1    GPIO_Pin_1
#define LCD_D2	  GPIO_Pin_2
#define LCD_D3	  GPIO_Pin_3
#define LCD_D4	  GPIO_Pin_4
#define LCD_D5	  GPIO_Pin_5
#define LCD_D6	  GPIO_Pin_6
#define LCD_D7	  GPIO_Pin_7

#define LCD_D0_D7 GPIOG

#define LCD_APB_D0_D7 RCC_APB2Periph_GPIOG

#define LCD_RW        GPIO_Pin_9
#define LCD_RW_PORT   GPIOG

#define LCD_RS        GPIO_Pin_10
#define LCD_RS_PORT   GPIOG

#define LCD_RST       GPIO_Pin_11
#define LCD_RST_PORT  GPIOG

#define LCD_CS1       GPIO_Pin_12
#define LCD_CS1_PORT  GPIOG

#define LCD_BKLT      GPIO_Pin_13
#define LCD_BKLT_PORT GPIOG

#define SET_RS_PIN()   GPIO_SetBits(LCD_RS_PORT, LCD_RS)
#define SET_RW_PIN()   GPIO_SetBits(LCD_RW_PORT, LCD_RW)
#define SET_CS1_PIN()  GPIO_SetBits(LCD_CS1_PORT, LCD_CS1)
#define SET_RST_PIN()  GPIO_SetBits(LCD_RST_PORT, LCD_RST)
#define SET_BKLT_PIN() GPIO_SetBits(LCD_BKLT_PORT, LCD_BKLT)

#define CLR_RS_PIN()   GPIO_ResetBits(LCD_RS_PORT, LCD_RS)
#define CLR_RW_PIN()   GPIO_ResetBits(LCD_RW_PORT, LCD_RW)
#define CLR_CS1_PIN()  GPIO_ResetBits(LCD_CS1_PORT, LCD_CS1)
#define CLR_RST_PIN()  GPIO_ResetBits(LCD_RST_PORT, LCD_RST)
#define CLR_BKLT_PIN() GPIO_ResetBits(LCD_BKLT_PORT, LCD_BKLT)

/*-*-*-*-*-* Printer Related Macros & Variables *-*-*-*-*-*/
#define PRN_PORT1      GPIOB
#define PRN_PORT2      GPIOC

#define PRN_APB1       RCC_APB2Periph_GPIOB
#define PRN_APB2       RCC_APB2Periph_GPIOC
#define PRN_APB3       RCC_APB2Periph_GPIOD
/***********************************************************************/
//Added new Nilesh
#define PRN_PWR_APB    RCC_APB2Periph_GPIOG
#define PRN_TH1        GPIO_Pin_13
#define PRN_TH1_PORT   GPIOB
/***********************************************************************/
#define PRN_STB1       GPIO_Pin_9
#define PRN_STB1_PORT  GPIOB

#define PRN_STB2       GPIO_Pin_4
#define PRN_STB2_PORT  GPIOC

#define PRN_STB3       GPIO_Pin_3
#define PRN_STB3_PORT  GPIOC

#define PRN_STB4       GPIO_Pin_2
#define PRN_STB4_PORT  GPIOC

#define PRN_STB5       GPIO_Pin_1
#define PRN_STB5_PORT  GPIOC

#define PRN_STB6       GPIO_Pin_0
#define PRN_STB6_PORT  GPIOC

#define PRN_MOT1       GPIO_Pin_5
#define PRN_MOT1_PORT  GPIOC

#define PRN_MOT2       GPIO_Pin_6
#define PRN_MOT2_PORT  GPIOC

#define PRN_MOT3       GPIO_Pin_7
#define PRN_MOT3_PORT  GPIOC

#define PRN_MOT4       GPIO_Pin_8
#define PRN_MOT4_PORT  GPIOC

#define PRN_DIN        GPIO_Pin_14
#define PRN_DIN_PORT   GPIOB

#define PRN_CLK        GPIO_Pin_15
#define PRN_CLK_PORT   GPIOB

#define PRN_LAT        GPIO_Pin_12
#define PRN_LAT_PORT   GPIOB

#define PRN_HUP        GPIO_Pin_8
#define PRN_HUP_PORT   GPIOB

#define PRN_PAP_SENSE  GPIO_Pin_9
#define PRN_PAP_PORT   GPIOC

#define PRN_PWR_CTRL      GPIO_Pin_15
#define PRN_PWR_CTRL_PORT GPIOG

/*-*-*-*-*-*-		Battery Sense			   -*-*-*-*-*-*/
#define BAT_SENSE 		 GPIO_Pin_6
#define BAT_SENSE_PORT   GPIOF

/*-*-*-*-*-*-*- Buzzer related macros 		   -*-*-*-*-*-*/
#define BUZZER_PIN         GPIO_Pin_1
#define BUZZER_PIN_PORT    GPIOD

/*-*-*-*-*-*- Flash Related Macros & Variables -*-*-*-*-*-*/
#define SPI_APB1     RCC_APB2Periph_GPIOA
#define SPI_APB2     RCC_APB2Periph_GPIOB

#define SPI_CS         GPIO_Pin_15
#define SPI_CS_PORT    GPIOA

#define SPI_SCK        GPIO_Pin_3
#define SPI_SCK_PORT   GPIOB

#define SPI_MOSI       GPIO_Pin_5
#define SPI_MOSI_PORT  GPIOB

#define SPI_MISO       GPIO_Pin_4
#define SPI_MISO_PORT  GPIOB

//I2C
#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1
#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sEE_I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sEE_M24C64_32

#define sEE_I2C_DMA                      DMA1
#define sEE_I2C_DMA_CHANNEL_TX           DMA1_Channel6
#define sEE_I2C_DMA_CHANNEL_RX           DMA1_Channel7
#define sEE_I2C_DMA_FLAG_TX_TC           DMA1_IT_TC6
#define sEE_I2C_DMA_FLAG_TX_GL           DMA1_IT_GL6
#define sEE_I2C_DMA_FLAG_RX_TC           DMA1_IT_TC7
#define sEE_I2C_DMA_FLAG_RX_GL           DMA1_IT_GL7
#define sEE_I2C_DMA_CLK                  RCC_AHBPeriph_DMA1
#define sEE_I2C_DR_Address               ((uint32_t)0x40005410)
#define sEE_USE_DMA

#define sEE_I2C_DMA_TX_IRQn              DMA1_Channel6_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Channel7_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Channel6_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Channel7_IRQHandler
#define sEE_I2C_DMA_PREPRIO              0
#define sEE_I2C_DMA_SUBPRIO              0

#define sEE_DIRECTION_TX                 0
#define sEE_DIRECTION_RX                 1

/* Exported constants --------------------------------------------------------*/
/* IRQ Channels --------------------------------------------------------------*/
#define WWDG_IRQChannel              ((u8)0x00)  /* Window WatchDog Interrupt */
#define PVD_IRQChannel               ((u8)0x01)  /* PVD through EXTI Line detection Interrupt */
#define TAMPER_IRQChannel            ((u8)0x02)  /* Tamper Interrupt */
#define RTC_IRQChannel               ((u8)0x03)  /* RTC global Interrupt */
#define FLASH_IRQChannel             ((u8)0x04)  /* FLASH global Interrupt */
#define RCC_IRQChannel               ((u8)0x05)  /* RCC global Interrupt */
#define EXTI0_IRQChannel             ((u8)0x06)  /* EXTI Line0 Interrupt */
#define EXTI1_IRQChannel             ((u8)0x07)  /* EXTI Line1 Interrupt */
#define EXTI2_IRQChannel             ((u8)0x08)  /* EXTI Line2 Interrupt */
#define EXTI3_IRQChannel             ((u8)0x09)  /* EXTI Line3 Interrupt */
#define EXTI4_IRQChannel             ((u8)0x0A)  /* EXTI Line4 Interrupt */
#define DMA1_Channel1_IRQChannel     ((u8)0x0B)  /* DMA1 Channel 1 global Interrupt */
#define DMA1_Channel2_IRQChannel     ((u8)0x0C)  /* DMA1 Channel 2 global Interrupt */
#define DMA1_Channel3_IRQChannel     ((u8)0x0D)  /* DMA1 Channel 3 global Interrupt */
#define DMA1_Channel4_IRQChannel     ((u8)0x0E)  /* DMA1 Channel 4 global Interrupt */
#define DMA1_Channel5_IRQChannel     ((u8)0x0F)  /* DMA1 Channel 5 global Interrupt */
#define DMA1_Channel6_IRQChannel     ((u8)0x10)  /* DMA1 Channel 6 global Interrupt */
#define DMA1_Channel7_IRQChannel     ((u8)0x11)  /* DMA1 Channel 7 global Interrupt */
#define ADC1_2_IRQChannel            ((u8)0x12)  /* ADC1 et ADC2 global Interrupt */
#define USB_HP_CAN_TX_IRQChannel     ((u8)0x13)  /* USB High Priority or CAN TX Interrupts */
#define USB_LP_CAN_RX0_IRQChannel    ((u8)0x14)  /* USB Low Priority or CAN RX0 Interrupts */
#define CAN_RX1_IRQChannel           ((u8)0x15)  /* CAN RX1 Interrupt */
#define CAN_SCE_IRQChannel           ((u8)0x16)  /* CAN SCE Interrupt */
#define EXTI9_5_IRQChannel           ((u8)0x17)  /* External Line[9:5] Interrupts */
#define TIM1_BRK_IRQChannel          ((u8)0x18)  /* TIM1 Break Interrupt */
#define TIM1_UP_IRQChannel           ((u8)0x19)  /* TIM1 Update Interrupt */
#define TIM1_TRG_COM_IRQChannel      ((u8)0x1A)  /* TIM1 Trigger and Commutation Interrupt */
#define TIM1_CC_IRQChannel           ((u8)0x1B)  /* TIM1 Capture Compare Interrupt */
#define TIM2_IRQChannel              ((u8)0x1C)  /* TIM2 global Interrupt */
#define TIM3_IRQChannel              ((u8)0x1D)  /* TIM3 global Interrupt */
#define TIM4_IRQChannel              ((u8)0x1E)  /* TIM4 global Interrupt */
#define I2C1_EV_IRQChannel           ((u8)0x1F)  /* I2C1 Event Interrupt */
#define I2C1_ER_IRQChannel           ((u8)0x20)  /* I2C1 Error Interrupt */
#define I2C2_EV_IRQChannel           ((u8)0x21)  /* I2C2 Event Interrupt */
#define I2C2_ER_IRQChannel           ((u8)0x22)  /* I2C2 Error Interrupt */
#define SPI1_IRQChannel              ((u8)0x23)  /* SPI1 global Interrupt */
#define SPI2_IRQChannel              ((u8)0x24)  /* SPI2 global Interrupt */
#define USART1_IRQChannel            ((u8)0x25)  /* USART1 global Interrupt */
#define USART2_IRQChannel            ((u8)0x26)  /* USART2 global Interrupt */
#define USART3_IRQChannel            ((u8)0x27)  /* USART3 global Interrupt */
#define EXTI15_10_IRQChannel         ((u8)0x28)  /* External Line[15:10] Interrupts */
#define RTCAlarm_IRQChannel          ((u8)0x29)  /* RTC Alarm through EXTI Line Interrupt */
#define USBWakeUp_IRQChannel         ((u8)0x2A)  /* USB WakeUp from suspend through EXTI Line Interrupt */
#define TIM8_BRK_IRQChannel          ((u8)0x2B)  /* TIM8 Break Interrupt */
#define TIM8_UP_IRQChannel           ((u8)0x2C)  /* TIM8 Update Interrupt */
#define TIM8_TRG_COM_IRQChannel      ((u8)0x2D)  /* TIM8 Trigger and Commutation Interrupt */
#define TIM8_CC_IRQChannel           ((u8)0x2E)  /* TIM8 Capture Compare Interrupt */
#define ADC3_IRQChannel              ((u8)0x2F)  /* ADC3 global Interrupt */
#define FSMC_IRQChannel              ((u8)0x30)  /* FSMC global Interrupt */
#define SDIO_IRQChannel              ((u8)0x31)  /* SDIO global Interrupt */
#define TIM5_IRQChannel              ((u8)0x32)  /* TIM5 global Interrupt */
#define SPI3_IRQChannel              ((u8)0x33)  /* SPI3 global Interrupt */
#define UART4_IRQChannel             ((u8)0x34)  /* UART4 global Interrupt */
#define UART5_IRQChannel             ((u8)0x35)  /* UART5 global Interrupt */
#define TIM6_IRQChannel              ((u8)0x36)  /* TIM6 global Interrupt */
#define TIM7_IRQChannel              ((u8)0x37)  /* TIM7 global Interrupt */
#define DMA2_Channel1_IRQChannel     ((u8)0x38)  /* DMA2 Channel 1 global Interrupt */
#define DMA2_Channel2_IRQChannel     ((u8)0x39)  /* DMA2 Channel 2 global Interrupt */
#define DMA2_Channel3_IRQChannel     ((u8)0x3A)  /* DMA2 Channel 3 global Interrupt */
#define DMA2_Channel4_5_IRQChannel   ((u8)0x3B)  /* DMA2 Channel 4 and DMA2 Channel 5 global Interrupt */

/*-*-*-*-*-*-*- Platform Interface Functions -*-*-*-*-*-*-*/
PLATFORM_SCOPE void RCC_Configure(void);
PLATFORM_SCOPE void NVIC_Configure(void);
PLATFORM_SCOPE void GPIO_Configure(void);
PLATFORM_SCOPE void Timer_Configure(void);
PLATFORM_SCOPE void RTC_Configure(void);
PLATFORM_SCOPE void USART_Configure(USART_TypeDef* USARTx, u32 APB_CLK, u32 Baudrate, u8 APB_Num);
PLATFORM_SCOPE void sEE_LowLevel_DeInit(void);
PLATFORM_SCOPE void sEE_LowLevel_Init(void);
PLATFORM_SCOPE void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction);
PLATFORM_SCOPE void RealTimeClockConfigure(void);

#endif
