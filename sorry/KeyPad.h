#ifndef __KEYPAD__H__
#define __KEYPAD__H__

#include "std_types.h"
#include "IO_ports.h"

#define N_col 3
#define N_row 4

// can i make it like this
#define KEYPAD_PORT_DATA GPIO_PORTA_DATA_R
#define KEYPAD_PORT_DIR GPIO_PORTA_DIR_R
#define KEYPAD_PORT_PUR GPIO_PORTA_PUR_R

uint8_t KeyPad_getPressedKey(void);


#endif
