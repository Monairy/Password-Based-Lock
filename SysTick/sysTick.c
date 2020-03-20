#include "sysTick.h"


void sysTick_Init(uint32_t count)
{
	NVIC_ST_CTRL_R = 0;   //clear ctrl reg
	NVIC_ST_RELOAD_R = count;
	NVIC_ST_CURRENT_R = 1;  //clear current reg by writting to it with any value
	NVIC_ST_CTRL_R |= 5; //set ENABLE & CLK_SRC bits
}


void sysTick_delayMs(uint32_t msecs)  //this function limited to 1000 msec
{
	uint32_t count = msecs*16*10*10*10-1;
	sysTick_Init(count);
	while(!(NVIC_ST_CTRL_R & 0x00010000));
}


void sysTick_delays(uint32_t secs)
{
	uint32_t count_sec=0; 
	sysTick_Init(16000000-1);  //set timer to count 1 sec
	while(count_sec != secs)
	{
		if((NVIC_ST_CTRL_R & 0x00010000))
			count_sec++;
	}
}