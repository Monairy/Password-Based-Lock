#include "eeprom.h"

//void SystemInit(){}
	
	
void SystemInit(){}

void EEPROM_init(void)
{
	uint8_t i;

	SYSCTL_RCGCEEPROM_R |= 0x01;
   for(i = 0;i<6;i=i+1);
	while((EEPROM_EEDONE_R & 0x01)==1);
	SYSCTL_SREEPROM_R |=0x01;
	SYSCTL_SREEPROM_R &=0x7E;
   for(i = 0;i<6;i=i+1);
   while((EEPROM_EEDONE_R & 0x01)==1);
		
}
void EEPROM_write(uint32_t password)
{
	EEPROM_EEBLOCK_R = 0;
	EEPROM_EEOFFSET_R = 0;
	EEPROM_EERDWR_R= password;
}

uint32_t  EEPROM_read(void)
{
	uint32_t  pass;
	EEPROM_EEBLOCK_R = 0;
	EEPROM_EEOFFSET_R = 0;	
	pass=EEPROM_EERDWR_R;
  return pass;
}
