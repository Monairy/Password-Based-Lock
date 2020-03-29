#include "LCD.h"
#include "KeyPad.h"
#include "eeprom.h"
#include "timer.h"

uint32_t arrtodecimal(uint32_t *arr,uint8_t length);
void decimaltoarr (uint32_t *arr,uint32_t decimal);
int8_t validatepassword(uint32_t *input , uint32_t *rightpass);
void setnewpassword();


void initportf()
{
	uint32_t delay;
	SYSCTL_RCGC2_R |= 0x20;
	delay=0; //dummy var
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R=0XFF;
	GPIO_PORTF_AFSEL_R=0;
	GPIO_PORTF_PCTL_R=0;
	GPIO_PORTF_AMSEL_R=0;
	GPIO_PORTF_DIR_R |= 0X02;
	GPIO_PORTF_DIR_R &= ~0X01;
	GPIO_PORTF_DEN_R |= 0X03;
	GPIO_PORTF_PUR_R |= 0X01;
	GPIO_PORTF_DATA_R = 0x00;  		
}

int main(void)
{ volatile int8_t check;
	uint32_t in[4];
	uint32_t savedpassarr[4];
	uint8_t key,counter=0,i =0,y=0,timer=0;
	
	initportf();
  LCD_init();
	EEPROM_init();
	EEPROM_write(9999);
	
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
		key = KeyPad_getPressedKey();
		if(key=='#' || key=='*' ){continue;}
    in[i]=key;
    i++;		
		delayMs(500);
		LCD_data(intgerToString(key));
		delayMs(10);
		counter++;
	}
  if(counter>=4)
	{	 	 
		key = KeyPad_getPressedKey();
		if(key=='#')
			{
		    check=validatepassword(in,savedpassarr);
		    if(check==1){ //correct password
					GPIO_PORTF_DATA_R |= 0x02;
					LCD_clearScreen(); 
					LCD_displayString("Correct Password");	
         	delayMs(500);	
	
						 while( GPIO_PORTF_DATA_R & (0x01) ){} //not pressed
									 
						 while(!(GPIO_PORTF_DATA_R & (0x01) ))//pressed
                    {
											sysTick_delayMs(250);
											timer+=1;
                               }	
										
					 if(timer>1 && timer<20 ){ //close lock				
				       LCD_clearScreen();
						 
					    	 }		
					 if(timer>=20 ){	//new pass		
				       LCD_clearScreen();
						   LCD_displayString("EnterNewPassword");	
         	     delayMs(500);	
					     LCD_clearScreen();
						   setnewpassword();
					     }
	 
              GPIO_PORTF_DATA_R &= ~0x02;	
             i=0;	counter=0; timer=0;							 
				}
				
				
				
				else{
				counter=0;
				LCD_clearScreen();
				LCD_displayString("Wrong Password");
				delayMs(5000);	
        LCD_clearScreen();
				i=0;
				}
		  }
    
		
   }   

}
}


uint32_t arrtodecimal(uint32_t *arr,uint8_t length)
{	
  uint32_t weights[4]={1000,100,10,1};
	uint32_t x,decimal;
	decimal=0;
	for (x=0;x<length;x++)
	{decimal+= (arr[x])*weights[x];}
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

void setnewpassword()
{ uint8_t counter=0,z=0,key;
	uint32_t newpass;
	uint32_t in2[4];
	LCD_clearScreen();
	for(;;){
	   if(counter<4)
	 {	
	   	key = KeyPad_getPressedKey();
	   	if(key=='#' || key=='*' ){continue;}
      in2[z]=key;
      z++;		
	  	delayMs(500);
	  	LCD_data(intgerToString(key));
	  	delayMs(10);
	  	counter++;
	}
	
	if(counter>=4)
		{
			key = KeyPad_getPressedKey();
		if (key=='#')
			{
	     	newpass=arrtodecimal(in2,4);
				EEPROM_write(newpass);
				LCD_clearScreen();
				LCD_displayString("Saved");
				delayMs(5000);
				LCD_clearScreen();
				return;
		   }
	
	
	}
	}

}
