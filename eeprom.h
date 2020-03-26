
#ifndef __eeprom_h__
#define __eeprom_h__

#include "stdint.h"
#include "C:\Keil_v5\TExaSware\tm4c123gh6pm.h"

void EEPROM_init(void);
void EEPROM_write(uint32_t password);
uint32_t EEPROM_read(void);


#endif
