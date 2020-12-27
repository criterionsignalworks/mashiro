/*

csCommon.h
Common Ground library for rapid prototyping 

IAR EW header for Coda 0.6/0.7 and compatible.

Property of Criterion Signalworks.
Do not distribute or reproduce without permission.
For more information, contact management@csw.cx or tim@csw.cx

TCS 2020 12

*/

#include <iostm8S103f3.h>
#include <stdint.h> 

#define CommonGroundVersion  "20201212.13" 

// Feature selection - uncomment to remove from inclusion 
//#define FEATURE_CSBASETIME // Master clock config and delay ms 
//#define FEATURE_CSMINUART // Serial print 
//#define FEATURE_CSFALSEBIN // Pseudo binary conversion 
//#define FEATURE_CSINITCOMMON // Greeting message and bundled init 

#ifndef FEATURE_CSBASETIME
#define FEATURE_CSBASETIME
#include "csBasetime.c"

// Initialize master system clock to run at 16 MHz.
void csInitSysClk();

// Initialize millisecond blocking delay function. This uses TIM2.
void csInitDelayMs();
// Delay for x milliseconds. This is neither accurate nor energy efficient.
void csDelayMs(unsigned long csDelayMsTarget);

#endif 

#ifndef FEATURE_CSMINUART
#define FEATURE_CSMINUART
#include "csMinUART.c"

// Initialize UART to 115200,n,8,1. Expects 16 MHz
void csInitSerial();
// Write data to UART 
void csSerialPrint(uint8_t *message);
// Write mildly formatted data to UART 
void csDbg(uint8_t *message);
// Regular debug with time delay and led toggle
void csDbe(uint8_t *message);

#endif 

#ifndef FEATURE_CSFALSEBIN
#define FEATURE_CSFALSEBIN

#include <intrinsics.h>
// Pseudo binary conversion for rapid prototyping, consider using hexadecimal for production
#define B(x) stb(#x)
static inline unsigned long long stb(const char *s) {
        unsigned long long i = 0;
        while (*s) {
                i <<= 1;
                i += *s++ - '0';
        }
        return i;
}

#endif 

#ifndef FEATURE_CSINITCOMMON
#define FEATURE_CSINITCOMMON

void csInitCommon() {
	__disable_interrupt();
	//#ifndef FEATURE_CSBASETIME
	csInitSysClk();
	csInitDelayMs();
	//#endif
	//#ifndef FEATURE_CSMINUART
	csInitSerial();
	//#endif
	__enable_interrupt();
	csSerialPrint("\n\rCommon Ground V");
	csSerialPrint(CommonGroundVersion);
	csSerialPrint(" successfully initialized.\n\r(C) Criterion Signalworks.\n\rContact management@csw.cx or tim@csw.cx for more information.\n\n\r");
}

#endif 