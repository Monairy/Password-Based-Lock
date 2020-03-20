#include "GPTM.h"


void gptm_inIt(uint64_t count)
{
	uint8_t delay;
	SYSCTL_RCGCWTIMER_R |= 0X01; //enable clk for timer0
	delay=0; //dummy variable
	delay=1;
	WTIMER0_CTL_R = 0;  //disable timerA
	WTIMER0_CFG_R = 0;    //For a 32/64-bit wide timer, this value selects the 64-bit timer configuration
	WTIMER0_TAMR_R = 0x2;  //periodic mode and down-counter
	WTIMER0_TAILR_R = count-1;
	WTIMER0_ICR_R = 0x1; //clear the TimerA timeout flag
	WTIMER0_CTL_R |= 0x01;  //enable timerA afte initialization
}


void gptm_delayMs(uint32_t msecs) 
{
	gptm_inIt(msecs*16*10*10*10);
	while((WTIMER0_RIS_R & 0x1) == 1) ; //wait to count msec
	//WTIMER0_ICR_R &= ~1; //clear the TimerA timeout flag
}