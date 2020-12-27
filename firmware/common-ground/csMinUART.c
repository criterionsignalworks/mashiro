/*

csMinUART.h
Minimal UART library 

IAR EW library for Coda 0.6/0.7 and compatible.

Property of Criterion Signalworks.
Do not distribute or reproduce without permission.
For more information, contact management@csw.cx or tim@csw.cx

TCS 2020 12

*/

#include <iostm8S103f3.h>

void csInitSerial() { 			// Initialize UART. Expects master clock at 16 MHz 
	//  Setup the port to 115200,n,8,1.
	UART1_CR1_M = 0;		//  8 Data bits.
	UART1_CR1_PCEN = 0;		//  Disable parity.
	UART1_CR3_STOP = 0;		//  1 stop bit.
	UART1_BRR2 = 0x0a;		//  Set the baud rate registers to 115200 baud
	UART1_BRR1 = 0x08;		//  based upon a 16 MHz system clock.
	//  Turn on the UART transmit, receive and the UART clock.
	UART1_CR2_TEN = 1;
	UART1_CR2_REN = 1;
	UART1_CR3_CKEN = 1;
}

void csSerialPrint(uint8_t *message) {
	uint8_t *ch = message;
	while (*ch)
	{
		UART1_DR = (unsigned char) *ch;     //  Put the next character into the data transmission register.
		while (UART1_SR_TXE == 0);          //  Wait for transmission to complete.
		ch++;                               //  Grab the next character.
	}
}

void csDbg(uint8_t *dbg) { 
	csSerialPrint(dbg);
	csSerialPrint("\r\n");
}

void csDbe(uint8_t *dbg) { 
	csDbg(dbg);
	csDelayMs(500);
}

