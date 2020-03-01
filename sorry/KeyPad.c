
#include "KeyPad.h"

// connet rows to PA3-0 and columns to PA6-PA4
// inilize porta with PA4 as output rest is input and pullup resistors

uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of *
				 break;
		case 11: return 0;
				 break;
		case 12: return '#'; // ASCII Code of #
				 break;
		default: return button_number;
	}
}



uint8_t KeyPad_getPressedKey(void)
{
	uint8_t col,row;
	PortA_Init(0x10,0xEF);
   
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins include the row pins
			 */
			GPIO_PORTA_DIR_R = (0x10<<col) ;

			/*
			 * clear the output pin column in this trace and enable the internal
			 * pull up resistors for the rows pins
			 */
            KEYPAD_PORT_PUR = (~(0x10<<col));
            // what happens when i try to write on a input pin
            KEYPAD_PORT_DATA &= (~(0x10<<col));

			for(row=0;row<N_row;row++) /* loop for rows */
			{
				if(! (KEYPAD_PORT_DATA & (0x01<<row) ) ) /* if the switch is press in this row */
				{
					return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
				}
			}
		}
	}
}

