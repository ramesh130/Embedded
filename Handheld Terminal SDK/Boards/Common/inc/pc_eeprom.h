
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PC_EEPROM_H
#define __PC_EEPROM_H

#ifdef  __PC_EEPROM_C
#define EEPROM_SCOPE
#else
#define EEPROM_SCOPE extern
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "i2c_eeprom.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */

/** @addtogroup Common
  * @{
  */

/** @addtogroup STM32_EVAL_I2C_EE
  * @{
  */

/** @defgroup STM32_EVAL_I2C_EE_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32_EVAL_I2C_EE_Exported_Constants
  * @{
  */
#if !defined (sEE_M24C08) && !defined (sEE_M24C64_32)
/* Use the defines below the choose the EEPROM type */
/*#define sEE_M24C08*/  /* Support the device: M24C08. */
/* note: Could support: M24C01, M24C02, M24C04 and M24C16 if the blocks and
   HW address are correctly defined*/
#define sEE_M24C64_32  /* Support the devices: M24C32 and M24C64 */
#endif

#ifdef sEE_M24C64_32
/* For M24C32 and M24C64 devices, E0,E1 and E2 pins are all used for device
  address selection (ne need for additional address lines). According to the
  Harware connection on the board (on STM3210C-EVAL board E0 = E1 = E2 = 0) */

 #define sEE_HW_ADDRESS     0xA0   /* E0 = E1 = E2 = 0 */

#elif defined (sEE_M24C08)
/* The M24C08W contains 4 blocks (128byte each) with the adresses below: E2 = 0
   EEPROM Addresses defines */
 #define sEE_Block0_ADDRESS 0xA0   /* E2 = 0 */
 /*#define sEE_Block1_ADDRESS 0xA2*/ /* E2 = 0 */
 /*#define sEE_Block2_ADDRESS 0xA4*/ /* E2 = 0 */
 /*#define sEE_Block3_ADDRESS 0xA6*/ /* E2 = 0 */

#endif /* sEE_M24C64_32 */

#define I2C_SPEED              200000
#define I2C_SLAVE_ADDRESS7     0xA0

//#if defined (sEE_M24C08)
// #define sEE_PAGESIZE    16
//#elif defined (sEE_M24C64_32)
// #define sEE_PAGESIZE    32
//#endif
#define sEE_PAGESIZE    8 //as per datasheet

/* Defintions for the state of the DMA transfer */
#define sEE_STATE_READY         0
#define sEE_STATE_BUSY          1

/* Maximum timeout value for counting before exiting waiting loop on DMA
   Trasnfer Complete. This value depends directly on the maximum page size and
   the sytem clock frequency. */
#define sEE_TIMEOUT_MAX         0x10000;
/**
  * @}
  */

/** @defgroup STM32_EVAL_I2C_EE_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32_EVAL_I2C_EE_Exported_Functions
  * @{
  */

EEPROM_SCOPE void sEE_DeInit(void);
EEPROM_SCOPE void sEE_Init(void);
EEPROM_SCOPE void sEE_WriteByte(uint8_t* pBuffer, uint16_t WriteAddr);
EEPROM_SCOPE void sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
EEPROM_SCOPE void sEE_WaitEepromStandbyState(void);
EEPROM_SCOPE void sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
EEPROM_SCOPE void sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);

#endif
