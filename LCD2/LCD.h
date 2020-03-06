#ifndef __LCD__H__
#define __LCD__H__


#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "std_types.h"
#include "IO_ports.h"

#define LCD_CTRL_PORT GPIO_PORTA_DATA_R
#define LCD_DATA_PORT GPIO_PORTB_DATA_R       


#define RS 0x20 /* PORTA BIT5 mask */
#define RW 0x40 /* PORTA BIT6 mask */
#define EN 0x80 /* PORTA BIT7 mask */




void delayMs(int n);
void delayUs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);


#endif


