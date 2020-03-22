#include "EEPROM.h"

void SystemInit(){}
	
void EEPROM_init(void)
{
	uint8_t x=0;
	SYSCTL_RCGCEEPROM_R |= 0x01;
	x=x+1;
	while(EEPROM_EEDONE_R &= 0x01 ==1)
	{}
	SYSCTL_SREEPROM_R |=0x01;
	x=x+1;
	while(EEPROM_EEDONE_R &= 0x01 ==1)
	{}	
}
void EEPROM_write(uint32_t password)
{
	uint8_t x;
	x=x=x+1;
	EEPROM_EERDWR_R= password;
}
uint8_t EEPROM_read(void)
{
	uint8_t x;
	x=x=x+1;
return EEPROM_EERDWR_R &=0x11;

}
----------------------------------------------------------------------------------------------------------------------------------
#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

void EEPROM_init(void);
void EEPROM_write(uint8_t password);
uint8_t EEPROM_read(void);
