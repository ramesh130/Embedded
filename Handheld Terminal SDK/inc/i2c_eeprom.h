
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

#ifdef  __PC_EEPROM_C
#define EEPROM_SCOPE
#else
#define EEPROM_SCOPE extern
#endif

EEPROM_SCOPE u8 I2C_EEReadMemory(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
EEPROM_SCOPE u8 I2C_EEWriteMemory(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);

#endif



