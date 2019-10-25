//******************************************************************************
//
//  Description: This file contains the inits for serial a0 and a1
//
//  Sean Daniels
//  Spring 2019
//  Built with IAR Embedded Workbench
//******************************************************************************
#include "macros.h"

extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;
extern int DISPLAY_END;


extern volatile char USB_Char_Rx[SMALL_RING_SIZE] ;
extern volatile char USB_Char_Tx[LARGE_RING_SIZE] ;
extern int recieved;

void Init_Serial_UCA0(char BAUD){ 
  int i;
  for(i=FALSE; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = ZERO;	// USB Rx Buffer
    }
  //usb_rx_ring_wr = BEGINNING;
  //usb_rx_ring_rd = BEGINNING;
  UCA0CTLW0 = ZERO;	// Use word register
  UCA0CTLW0 |= UCSWRST;	// Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK;	// Set SMCLK as fBRCLK
  if(BAUD==LOW){
    UCA0BRW = LOW_BAUD_RATE_CONTROL_REGISTER ;
    UCA0MCTLW = LOW_MODULATION_ONTROL_REGISTER ;
    }
  else if(BAUD==HIGH){
    UCA0BRW = HIGH_BAUD_RATE_CONTROL_REGISTER;
    UCA0MCTLW = HIGH_MODULATION_CONTROL_REGISTER;
    }
  UCA0CTLW0 &= ~UCSWRST;	// Set Software reset enable
  UCA0IE |= UCRXIE;	// Enable RX interrupt
}


void Init_Serial_UCA1(char BAUD){ 
  int i;
  for(i=FALSE; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = ZERO;	// USB Rx Buffer
  }
  //usb_rx_ring_wr = BEGINNING;
  //usb_rx_ring_rd = BEGINNING;
// Configure UART 0
  UCA1CTLW0 = ZERO;	// Use word register
  UCA1CTLW0 |= UCSWRST;	// Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK;	// Set SMCLK as fBRCLK
 if(BAUD==LOW){
    UCA1BRW = LOW_BAUD_RATE_CONTROL_REGISTER;
    UCA1MCTLW = LOW_MODULATION_ONTROL_REGISTER;
  }
 else if(BAUD==HIGH){
    UCA1BRW = HIGH_BAUD_RATE_CONTROL_REGISTER;
    UCA1MCTLW = HIGH_MODULATION_CONTROL_REGISTER;
  }
  UCA1CTLW0 &= ~UCSWRST;	// Set Software reset enable
  UCA1IE |= UCRXIE;	// Enable RX interrupt
}
