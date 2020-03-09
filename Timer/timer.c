#include "timer.h"

void Systick_Init(void)
{
  NVIC_ST_CTRL_R = 0;
  NVIC_ST_RELOAD_R = 0x00FFFFFF;
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 0x00000005;
}

// Delay for a very little time (under 200ms) 
void Systick_Delay(unsigned long delay)
{
  NVIC_ST_RELOAD_R = delay - 1;
  NVIC_ST_CURRENT_R = 0;

  while((NVIC_ST_CTRL_R & 0x00010000) == 0)
  {}
}

// One millisecond delay
void Systick_Delay_1ms(void)
{
  NVIC_ST_CTRL_R = 0;
  NVIC_ST_RELOAD_R = 0x0001387F; //80000-1 
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 0x00000005;

  while((NVIC_ST_CTRL_R & 0x00010000) == 0)
  {}
}

// Wait for some time
void Systick_Wait(unsigned long delay)
{
  for(int i = 0; i < delay; i++)
  {
    Systick_Delay_1ms();
  }
}

// Five seconds 
// To be used with a push button for password reset
void Systick_Delay_5s(void)
{
  for(int i = 0; i < 5000; i++)
  {
    Systick_Delay_1ms();
  }
}