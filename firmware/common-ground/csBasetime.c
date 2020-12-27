/*

csBasetime.c
Basic timer function and system clock configuration 

IAR EW library for Coda 0.6/0.7 and compatible.

Property of Criterion Signalworks.
Do not distribute or reproduce without permission.
For more information, contact management@csw.cx or tim@csw.cx

TCS 2020 12

*/

#include <iostm8S103f3.h>

void csInitSysClk() {			// Initialize SysClk
	CLK_ICKR = 0;			//  Reset the Internal Clock Register
	CLK_ICKR_HSIEN = 1;		//  Enable the HSI
	CLK_ECKR = 0;			//  Disable the external clock
	while (CLK_ICKR_HSIRDY == 0);	//  Wait for the HSI to be ready for use
	CLK_CKDIVR = 0;			//  Ensure the clocks are running at full speed
	CLK_PCKENR1 = 0xff;		//  Enable all peripheral clocks
	CLK_PCKENR2 = 0xff;
	CLK_CCOR = 0;			//  Turn off CCO
	CLK_HSITRIMR = 0;		//  Turn off any HSIU trimming
	CLK_SWIMCCR = 0;		//  Set SWIM to run at clock / 2
	CLK_SWR = 0xe1;			//  Use HSI as the clock source
	CLK_SWCR = 0;			//  Reset the clock switch control register
	CLK_SWCR_SWEN = 1;		//  Enable switching
	while (CLK_SWCR_SWBSY != 0);	//  Pause while the clock switch is busy
}

unsigned long csDelayMsSysTick = 0;

void csDelayMs(unsigned long csDelayMsTarget){
  csDelayMsTarget = csDelayMsTarget- 1;
  unsigned long csDelayMsLimit = csDelayMsSysTick + csDelayMsTarget;
  while(csDelayMsLimit >= csDelayMsSysTick);
}

//  TIM2 interrupt handler for delay function 
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void)
{
	csDelayMsSysTick++;		//  System tick increment
	TIM2_SR1_UIF = 0;		//  Reset the interrupt
}

void csInitDelayMs() {		//  Setup Timer 2 to generate an interrupt every 1mS based on a 16MHz clock.
	TIM2_PSCR = 0x04;		//  Prescaler = 32. actually 16
	TIM2_ARRH = 0x03;		//  High byte of 940. 
	TIM2_ARRL = 0xe6;		//  Low byte 
	TIM2_IER_UIE = 1;		//  Enable the update interrupts.
	TIM2_CR1_CEN = 1;		//  Finally enable the timer.
}



