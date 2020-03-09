#include "LCD.h"


void init(void);
void LCD_cmd(char cmd);
void LCD_char(char data);


void init(void)
{
   SYSCTL_RCGC2_R  |= 0x03;    //clock    
   
   LCD_DATA_DIR=0xFF;   //output D0-D7
   LCD_DATA_DEN=0xFF; //digial D0-D7
   LCD_DATA_AMSEL=0;
   LCD_DATA_AFSEL=0;
   LCD_DATA_PCTL=0;
   Delay1ms(##);
   LCD_CTRL_DIR=0xE0;  //1110,0000  rs rw e
   LCD_DATA_DEN=0xE0; //digital rs rw e
   LCD_CTRL_AMSEL=0;
   LCD_CTRL_AFSEL=0;
   LCD_CTRL_PCTL=0;
   

Delay1ms(##);
LCD_cmd(0x0F); //ON
Delay1ms(##);
LCD_cmd(0x30); //wakeup
Delay1ms(##);
LCD_cmd(0x01); //clear
Delay1ms(##);
LCD_cmd(0x38); //two lines
Delay1ms(##);
LCD_cmd(0x02); //cursor home 
Delay1ms(##);


}
	

	
void LCD_cmd(char cmd) //send control command
{
	LCD_CTRL=0; //rs,rw=0
	LCD_DATA=cmd; 
	
	LCD_CTRL=0x80; //enable=1
	
	Delay1ms(##);
	LCD_CTRL=0; //enable=0
	
}


void LCD_char(char data) //write character on screen
{
        LCD_CTRL|=0x20; //rs=1,rw=0	
        LCD_DATA=data;
	
	LCD_CTRL=0x80; //enable=1
	
	Delay1ms(##);
	LCD_CTRL=0; //enable=0	
	
}	


void LCD_displayString(const char *Str)
{
	uint8_t i=0;
	while(Str[i] != '\0')
	{
		LCD_char(Str[i]);
		i++;
	}
}

