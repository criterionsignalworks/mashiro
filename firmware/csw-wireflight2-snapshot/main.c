/*

csw-wireflight
Ground up programming blink demo

IAR EW project for Ranka N1 and compatible.

Property of Criterion Signalworks.
Do not distribute or reproduce without permission.
For more information, contact management@csw.cx or tim@csw.cx

TCS 2020 10

*/

#include <stdint.h>

unsigned long sy; // one two three four retard at the door 

// PB BASE 0x40020400
// PB MODER 0x00000000, 01 = GP output
// PB ODR 0x00000014
// TIM2 boundry 0x4000 0000 - 0x4000 03FF 
// TIMx PSC offset 0x28
// TIMx ARR offset 0x2C - reset 0xFFFF FFFF high / low byte
// TIMx interrupt enable / DMA offset 0x0C - UIE (update enable) at bit 0 
// TIMx master enable (CEN) at bit 0 of CR1 offset 0x00 reset 0x0000 - write 0x0001 to enable 
// because its at the end ok 
// hello hello SR pending update at bit 0 offset 0x10 (UIF) yes ok 
// tim2 global interrupt addr 0x0000 00B0 position 28 priority 35 

volatile uint32_t *M = (volatile uint32_t *)0x40020400;
volatile uint32_t *O = (volatile uint32_t *)0x40020414;
volatile uint32_t *T2ARR = (volatile uint32_t *)0x4000002C;
volatile uint32_t *T2PSC = (volatile uint32_t *)0x40000028;
volatile uint32_t *T2hello = (volatile uint32_t *)0x4000000C;
volatile uint32_t *T2homo = (volatile uint32_t *)0x40000000;
volatile uint32_t *T2rererererererersdfadsfasdf = (volatile uint32_t *)0x40000010;
volatile uint32_t *coolest = (volatile uint32_t *)0xE000E100UL;

void delay(unsigned long tg){
  tg = tg- 1;
  unsigned long lm = sy + tg;
  while(lm >= sy);
}

void inittim2()			//  Setup Timer 2 to generate an interrupt every 1mS based on a 16MHz clock. (copied from coda)
{
    *T2PSC = 0x05;		//  prescaler is 32.
    *T2ARR = 0x000001f4; 	// is this correct?????
    *T2hello = 0x1;		//  enable update interrupt by writing 1 to UIE
    *T2homo = 0x1;		//  enable timer by writing 1 to CEN
}

/*
#pragma vector = 28
__interrupt void TIM2_IRQHandler(void) {
    sy++;			//  timer increment
    *T2rererererererersdfadsfasdf = 0x0;		//  no more interrupt!!!!!!!!!!!!!!!!!!!!!!  
}

// NVIC ISER 0xE000E100UL
// 1   0    0   0    0   0    0   0 
// 00010000 00000000 00000000 00000000
*/





int main()
{
	*coolest = 0x10000000;
	*M = 0x55;
	while(1) {
	*O = 0x00;
	*O = 0xFF;
	}
}
