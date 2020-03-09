#ifndef __TIMER__H__
#define __TIMER__H__

#include "inc/tm4c123gh6pmh"
//#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "stdint.h"

void Systick_Init(void);

void Systick_Delay(unsigned long delay);

void Systick_Delay_1ms(void);

void Systick_Wait(unsigned long delay);

void Systick_Delay_5s(void);

#endif