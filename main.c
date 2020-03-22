#include "LCD.h"
#include "KeyPad.h"


int main(void)
{
  char passwd[5]= {'1','1','1','1','\0'};
	char in[5];
	uint8_t key,counter=0,i =0,y=0,flag=1;
	
	LCD_init();

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
	//key = KeyPad_getPressedKey(); 
for(;;)
{
	
	if(counter<4)
	{
		counter++;
		key = KeyPad_getPressedKey();
    in[i]=intgerToString(key);
     i++;		
		delayMs(500);
		LCD_data(intgerToString(key));
		delayMs(10);
	}
  if(counter==4 && flag==1)
	{
	  for ( y=0; y<4;y++)
	  {
	     if (in[y]!=passwd[y]) 
		   flag=0;
	
	   }
     
   }   

}
}
