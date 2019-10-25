//------------------------------------------------------------------------------
//
//  Description: This file contains the timer interrupt routines
//
//
//  Sean Daniels
//  FEB 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//----

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>


volatile unsigned int Time_Sequence=FALSE;
volatile unsigned int one_time = FALSE;
volatile unsigned int debounce_count = FALSE;
volatile unsigned int Debounce = FALSE;
//volatile unsigned int blink_count = FALSE;



/*---------Main timer interrupt--------*/
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  Time_Sequence++;// INCREMENTED EVERY 20ms
  TB0CCR0 += TB0CCR0_INTERVAL;	
  one_time=TRUE;
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,RANGE_OF_FLAG_VECTOR)){
    case ZERO: 
      break;	// No interrupt
    case TWO:	
//...... Debounce timer. Once enabled, incremented every 100ms ......
      Debounce = TRUE;
      debounce_count++;
      TB0CCR1 += TB0CCR1_INTERVAL;	// Add Offset to TBCCR1
      break;
    case FOUR:
    //...... Blinker timer. Incremented every 50ms ......
     //blink_count++;
     TB0CCR2 += TB0CCR2_INTERVAL;	// Add Offset to TBCCR2
      break;
    case RANGE_OF_FLAG_VECTOR:	// overflow
//...... Add What you need happen in the interrupt ......
    break;
default: break;
} 
//----------------------------------------------------------------------------
}
