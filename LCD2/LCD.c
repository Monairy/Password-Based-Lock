#include "LCD.h"



/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3180; j++)
{} /* do nothing for 1 ms */
}



/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} /* do nothing for 1 us */
}



void LCD_init(void)
{
	
	PortA_Init(0XE0,0X00);
	PortB_Init(0XFF,0X00);
	
	delayMs(20); /* initialization sequence */
  LCD_command(0x30);  //wakeup
  delayMs(5);
	 LCD_command(0x30);  //wakeup
  delayMs(100);
	LCD_command(0x30);
	LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
  LCD_command(0x06); /* move cursor right */
  LCD_command(0x01); /* clear screen, move cursor to home */
  LCD_command(0x0F); /* turn on display, cursor blinking */
}

void LCD_command(unsigned char command)
{
	LCD_CTRL_PORT=0;   /* RS = 0, R/W = 0 */
	LCD_DATA_PORT=command;
	LCD_CTRL_PORT=EN;
	delayMs(0);
	LCD_CTRL_PORT=0;
	delayMs(0);
	LCD_CTRL_PORT=0;
	if (command < 4)
			delayUs(2); /* command 1 and 2 needs up to 1.64ms */
			else
			delayUs(40);
}


void LCD_data(unsigned char data)
{
	LCD_CTRL_PORT=RS;
	LCD_DATA_PORT=data;
	LCD_CTRL_PORT=EN | RS;
	delayMs(0);
	LCD_DATA_PORT=0;
	delayUs(40);
}