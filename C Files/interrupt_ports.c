//------------------------------------------------------------------------------
//
//  Description: This file contains the port interrupt routines
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

char sw1Count=FALSE;
char sw2Count=FALSE;
volatile unsigned char Switch1 = FALSE;
volatile unsigned char Switch2 = FALSE;


/*------------Switch 1 interrupt---------
triggered when switch 1 is pressed
debounce timer is enabled, backlight is turned off, Switch1 variable set to true, switch interrupt disabled 
until debounce complete
*/
#pragma vector=PORT4_VECTOR
__interrupt void switch_interruptOne(void){
if (P4IFG & SW1) {
Switch1=TRUE;
TB0CCTL1 |= CCIE; //enable debounce timer
P4IE &= ~SW1; //disable switch interrupt
}
}

/*------------Switch 2 interrupt---------
triggered when switch 2 is pressed
debounce timer is enabled, backlight is turned off, Switch2 variable set to true, switch interrupt disabled 
until debounce complete
*/
#pragma vector=PORT2_VECTOR
__interrupt void switch_interruptTwo(void){
  // Switch 2
if (P2IFG & SW2) {
Switch2 = TRUE;
TB0CCTL1 |= CCIE; //enable debounce timer
P2IE &= ~SW2; //disable switch interrupt
}

  
}