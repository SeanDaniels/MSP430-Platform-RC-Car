//------------------------------------------------------------------------------
//
//  Description: This file contains the Port initialization Routine
//
//
//  Sean Daniels
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------ 

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>
 

//declarations
void Init_Ports(int condVal);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(int condVal);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);


/*
Initializing ports 1 through 6
port 3 is passed a conditional value in order to trigger either GPIO or smclk
*/
void Init_Ports(int condVal){
  Init_Port1();
  Init_Port2();
  Init_Port3(condVal);
  Init_Port4();
  Init_Port5();
  Init_Port6();
    }
/*
Port 1
Pin 0: Red LED
Pin 1: A1_SEEED
Pin 2: V_DETECT_L
Pin 3: V_DETECT_R
Pin 4: A4_SEEED
Pin 5: V_Thumb
Pin 6: UCA0RXD
Pin 7: UCA0TXD
*/
void Init_Port1(void){
 P1DIR = DIR_INIT; // Set P1 direction to output NO CLUE WHY THIS IS 
 P1OUT = OUT_INIT; // P1 set Low NO CLUE WHY THIS IS
 //PIN 0
 P1SEL0 &= ~RED_LED;
 P1SEL1 &= ~RED_LED;
 P1DIR |= RED_LED;
 //PIN 1
 P1SEL0 |= A1_SEEED;
 P1SEL1 |= A1_SEEED; 
 //PIN 2
 P1SEL0 |= V_DETECT_L; // P2_2 GPIO operation
 P1SEL1 |= V_DETECT_L; // P2_2 GPIO operation
 //PIN 3
 P1SEL0 |= V_DETECT_R;
 P1SEL1 |= V_DETECT_R;
 //P1DIR NOT AFFECTED BY ADC
 //PIN 4
 P1SEL0 |= A4_SEEED;
 P1SEL1 |= A4_SEEED;
 //PIN 5
 P1SEL0 |= V_THUMB;
 P1SEL1 |= V_THUMB;
 //PIN 6
 P1SEL0 |= UCA0RXD;
 P1SEL1 &= ~UCA0RXD;
 //PIN 7
 P1SEL0 |= UCA0TXD;
 P1SEL1 &= ~UCA0TXD;
}


/*
Port 2
Pin 0: GPIO 
Pin 1: GPIO
Pin 2: GPIO
Pin 3: SWITCH 2
Pin 4: GPIO
Pin 5: GPIO
Pin 6: LFXOUT Clock operation
Pin 7: LFXIN Clock operation
*/
void Init_Port2(void){
//------------------------------------------------------------------------------
 P2DIR = DIR_INIT; // Set P1 direction to output
 P2OUT = OUT_INIT; // P1 set Low
 //PIN 0 
 P2SEL0 &= ~P2_0; // P2_0 GPIO operation
 P2SEL1 &= ~P2_0; // P2_0 GPIO operation
 P2DIR &= ~P2_0; // Direction = input
 //PIN 1
 P2SEL0 &= ~P2_1; // P2_1 GPIO operation
 P2SEL1 &= ~P2_1; // P2_1 GPIO operation
 P2DIR &= ~P2_1; // Direction = input
 //PIN 2
 P2SEL0 &= ~P2_2; // P2_2 GPIO operation
 P2SEL1 &= ~P2_2; // P2_2 GPIO operation
 P2DIR &= ~P2_2; // Direction = input
 //PIN 3
 P2SEL0 &= ~SW2; // SW2 Operation
 P2SEL1 &= ~SW2; // SW2 Operation
 P2DIR &= ~SW2; // Direction = input
 P2OUT |= SW2; // Configure pullup resistor
 P2REN |= SW2; // Enable pullup resistor
 P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
 P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
 P2IE |= SW2; // P2.6 interrupt enabled
 //PIN 4
 P2SEL0 &= ~P2_4; // P2_4 GPIO operation
 P2SEL1 &= ~P2_4; // P2_4 GPIO operation
 P2DIR &= ~P2_4; // Direction = input
 //PIN 5
 P2SEL0 &= ~P2_5; // P2_5 GPIO operation
 P2SEL1 &= ~P2_5; // P2_5 GPIO operation
 P2DIR &= ~P2_5; // Direction = input
 //PIN 6
 P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
 P2SEL1 |= LFXOUT; // LFXOUT Clock operation
 //PIN 7
 P2SEL0 &= ~LFXIN; // LFXIN Clock operation
 P2SEL1 |= LFXIN; // LFXIN Clock operation
 //------------------------------------------------------------------------------
}

/*
Port 3, ARGUMENT BASED, ONE SEL'S GPIO, OTHER SEL'S SMCLK
Pin 0: TEST PROBE
Pin 1: 0A20
Pin 2: OA2N
Pin 3: OA2P
Pin 4: SMCLK or GPIO
Pin 5: GPIO
Pin 6: IOT
Pin 7: GPIO
*/
void Init_Port3(int num1){
  if(num1){//if button value is set to smclk
  P3DIR = DIR_INIT;
  P3OUT = OUT_INIT;
  //PIN 0
  P3SEL0 &= ~TEST_PROBE;
  P3SEL1 &= ~TEST_PROBE;
  P3DIR |= TEST_PROBE;
  P3OUT &= ~TEST_PROBE;
  //PIN 1
  P3SEL0 |= OA20;
  P3SEL1 |= OA20;
  //DIR DON'T MATTER 
  //PIN 2
  P3SEL0 |= OA2N;
  P3SEL1 |= OA2N;
  //DIR DON'T MATTER
  //PIN 3
  P3SEL0 |= OA2P;
  P3SEL1 |= OA2P;
  //DIR DON'T MATTER
  //PIN 4
  P3SEL0 |= SMCLK_OUT; // for smclk setting sel0 = 1, sel1=0, 
  P3SEL1 &= ~SMCLK_OUT;
  P3DIR |= SMCLK_OUT;
  //SMLCLK DIR = OUT, NOT SURE ABOUT INIT VAL
  //PIN 5
  P3SEL0 &= ~P3_5;
  P3SEL1 &= ~P3_5;
  P3DIR &= ~P3_5;
  //PIN 6
  P3SEL0 |= IOT_LINK;
  P3SEL1 |= IOT_LINK;
  P3DIR  &= ~IOT_LINK;
  P3OUT  &= ~IOT_LINK;
  //NOT SURE ABOUT DIR OR INIT VAL
  //PIN 7
  P3SEL0 &= ~P3_7;
  P3SEL1 &= ~P3_7;
  P3DIR &= ~P3_7;
  }
  else{//if button value is set to gpio
  P3DIR = DIR_INIT;
  P3OUT = OUT_INIT;
  //PIN 0
  P3SEL0 &= ~TEST_PROBE;
  P3SEL1 &= ~TEST_PROBE;
  P3DIR |= TEST_PROBE;
  P3OUT &= ~TEST_PROBE;
  //PIN 1
  P3SEL0 |= OA20;
  P3SEL1 |= OA20;
  //DIR DON'T MATTER 
  //PIN 2
  P3SEL0 |= OA2N;
  P3SEL1 |= OA2N;
  //DIR DON'T MATTER
  //PIN 3
  P3SEL0 |= OA2P;
  P3SEL1 |= OA2P;
  //DIR DON'T MATTER
  //PIN 4
  P3SEL0 &= ~SMCLK_OUT;
  P3SEL1 &= ~SMCLK_OUT;
  P3DIR |= SMCLK_OUT;
  P3OUT &= ~SMCLK_OUT;
  //SMLCLK DIR = OUT, NOT SURE ABOUT INIT VAL
  //PIN 5
  P3SEL0 &= ~P3_5;
  P3SEL1 &= ~P3_5;
  P3DIR &= ~P3_5;
  //PIN 6
  P3SEL0 |= IOT_LINK;
  P3SEL1 |= IOT_LINK;
  P3DIR  &= ~IOT_LINK;
  P3OUT  &= ~IOT_LINK;
  //NOT SURE ABOUT DIR OR INIT VAL
  //PIN 7
  P3SEL0 &= ~P3_7;
  P3SEL1 &= ~P3_7;
  P3DIR &= ~P3_7;
  }
  
  
}

/*
Port 4
Pin 0: RESET LCD
Pin 1: SW1
Pin 2: UART
Pin 3: LCD GPIO
Pin 4: SMCLK or GPIO
Pin 5: CLK BUS
Pin 6: BUS
Pin 7: BUS
*/

void Init_Port4(void){
P4OUT = OUT_INIT; // P1 set Low
P4DIR = DIR_INIT; // Set P1 direction to output
// P4 PIN 0
P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
P4OUT &= ~RESET_LCD; // Set RESET_LCD On [Low] (Should this be low or high)?
P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
// P4 PIN 1
P4SEL0 &= ~SW1; // SW1 GPIO operation
P4SEL1 &= ~SW1; // SW1 GPIO operation
P4OUT |= SW1; // Configure pullup resistor
P4DIR &= ~SW1; // Direction = input
P4REN |= SW1; // Enable pullup resistor
P4IES |= SW1; // P2.0 Hi/Lo edge interrupt
P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
P4IE |= SW1; // P2.6 interrupt enabled
// P4 PIN 2
P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
// P4 PIN 3
P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

// P4 PIN 4
P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
// P4 PIN 5
P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
// P4 PIN 6
P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
// P4 PIN 7
P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
//--------------------------------------------------------------------
}
/*
Port 5
Pin 0: IOT RESET
Pin 1: GPIO
Pin 2: IOT SELECT
Pin 3: IOT PROG
Pin 4: IR
*/

void Init_Port5(void){
   P5OUT = OUT_INIT;
   P5DIR = DIR_INIT;
   //PIN 0
   P5SEL0 &= ~IOT_RESET;
   P5SEL1 &= ~IOT_RESET;
   P5DIR  |= IOT_RESET; //OUTPUT
   P5OUT &= ~IOT_RESET; //init condition = 0;
   //PIN 1
   P5SEL0 &= ~P5_1;
   P5SEL1 &= ~P5_1;
   P5DIR  &= ~P5_1; //INPUT
   //PIN 2
   P5SEL0 &= ~IOT_PROG_SEL;
   P5SEL1 &= ~IOT_PROG_SEL;
   P5DIR &= ~IOT_PROG_SEL; //INPUT
   //PIN 3      
   P5SEL0 &= ~IOT_PROG_MODE;
   P5SEL1 &= ~IOT_PROG_MODE;
   P5DIR &= ~IOT_PROG_MODE;//INPUT
   //PIN 4
   P5SEL0 &= ~IR_LED;
   P5SEL1 &= ~IR_LED;  
   P5DIR  |= IR_LED;//OUTPUT
   P5OUT &= ~IR_LED;//low
}

/*
Port 6
Pin 0: R FORWARD
Pin 1: L FORWARD
Pin 2: R REVERSE
Pin 3: L REVERSE
Pin 4: BACKLIGHT
Pin 5: GPIO
PIN 6: GREEN LED
*/

void Init_Port6(void){
 P6OUT = OUT_INIT;
 P6DIR = DIR_INIT;
 //P6 PIN 0
 P6SEL0 |= R_FORWARD;
 P6SEL1 &= ~R_FORWARD;
 P6DIR |= R_FORWARD;
 //NOT SURE ABOUT ANY OF THIS ^^^ I THINK ITS MOTOR CONTROL, SO OUTPUT, BUT I DON'T WANT THE MOTOR ON, BUT THIS MAY BE A FUNCTION
 //P6 PIN 1
 P6SEL0 |= L_FORWARD;
 P6SEL1 &= ~L_FORWARD;
 P6DIR |= L_FORWARD;//output
 //P6 PIN 2
 P6SEL0 |= R_REVERSE;
 P6SEL1 &= ~R_REVERSE;
 P6DIR |= R_REVERSE;//output
 //P6 PIN 3
 P6SEL0 |= L_REVERSE;
 P6SEL1 &= ~L_REVERSE;
 P6DIR |= L_REVERSE;//output
 //P6 PIN 4
 P6SEL0 &= ~LCD_BACKLITE;
 P6SEL1 &= ~LCD_BACKLITE;
 P6OUT &= ~LCD_BACKLITE;//LOW
 P6DIR |= LCD_BACKLITE;//output
 //P6 PIN 5
 P6SEL0 &= ~P6_5;
 P6SEL1 &= ~P6_5;
 P6DIR  |= P6_5;//OUTPUT
 P6OUT &= ~P6_5;//LOW
 //P6 PIN 6
 P6SEL0 &= ~GREEN_LED;
 P6SEL1 &= ~GREEN_LED;
 P6OUT &= ~GREEN_LED;//LOW
 P6DIR |= GREEN_LED;//output
 
}
