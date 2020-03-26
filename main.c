#include "LCD.h"
#include "KeyPad.h"
#include "eeprom.h"
int32_t arrtodecimal(char *arr,uint8_t length);
void decimaltoarr (uint32_t *arr,uint32_t decimal);
int8_t validatepassword(uint32_t *input , uint32_t *rightpass);

void initportf()
{
	uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x20;
	delay=0; //dummy var
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R=0XFF;
	GPIO_PORTF_AFSEL_R=0;
	GPIO_PORTF_PCTL_R=0;
	GPIO_PORTF_AMSEL_R=0;
	GPIO_PORTF_DIR_R=0X02;
	GPIO_PORTF_DEN_R=0X02;
	GPIO_PORTF_PUR_R=0X00;
	GPIO_PORTF_DATA_R = 0x0;  		
}

int main(void)
{ volatile int8_t check;
	uint32_t in[4];
	uint32_t savedpassarr[4];
	uint8_t key,counter=0,i =0,y=0;
	
	initportf();
  LCD_init();
	EEPROM_init();
	EEPROM_write(9999);
  //password=arrtodecimal(arrr,4);
	/*/LCD_command(2);
	
	//delayMs(10);
	//LCD_command(1); //clear display
	//delayMs(10);
	//LCD_displayString("Enter password");
 delayMs(50);	
	LCD_command(2);
	delayMs(50);
	LCD_displayString("Enter password");
	delayMs(500);
	LCD_command(0x02);
	delayMs(500);
  LCD_command(0x80); //lcd cursor location 
  delayMs(500);
  LCD_displayString("Enter password");
  delayMs(500);
	*/
	KeyPad_init();
	delayMs(500);
		 
for(;;)
{	decimaltoarr(savedpassarr,EEPROM_read());
		 

	if(counter<4)
	{
		counter++;
		key = KeyPad_getPressedKey();
    in[i]=key;
    i++;		
		delayMs(500);
		LCD_data(intgerToString(key));
		delayMs(10);
	}
  if(counter>=4)
	{	 	 
		 check=validatepassword(in,savedpassarr);
     	GPIO_PORTF_DATA_R  |= 0x02;	
   }   

}
}


int32_t arrtodecimal(char *arr,uint8_t length)
{	
  int32_t weights[4]={1,10,100,1000};
	int32_t x,decimal;
	decimal=0;
	for (x=0;x<=length;x++)
	{decimal+= (arr[x]-'0')*weights[x];}
	return decimal;
}
void decimaltoarr (uint32_t *arr,uint32_t decimal)
{	
	uint8_t y;
	for (y=0;y<4;y++)
	{
	arr[3-y]=decimal%10;
	decimal=decimal/10;
  }
}

int8_t validatepassword(uint32_t *input , uint32_t *rightpass)
{	 
	uint8_t z;
	for ( z=0; z<4;z++)
	  {
	     if (input[z]!=rightpass[z]) 
		   return 0;
	   }
	return 1;
}
