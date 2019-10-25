//******************************************************************************
//
//  Description: This file contains the ISR's for serial communication
//
//  Sean Daniels
//  Spring 2019
//  Built with IAR Embedded Workbench
//******************************************************************************

#include "macros.h"
#include <string.h>



// global variables
//volatile 
unsigned int index=FALSE;
volatile unsigned int A0_usb_rx_ring_wr=FALSE;
volatile unsigned int READY_TO_SEND=ONE;
volatile unsigned int COMMAND_NUMBER = ZERO;

volatile char COMMAND_RECEIVED = 'F';
volatile char command[TWO][EIGHT];
volatile char ip[TWENTY];
volatile char SSID[TEN];
volatile char USB_Char_Rx[SMALL_RING_SIZE] ;
volatile char A0_Char_Rx[ONE_HUNDRED];
volatile char previous_letter = 'T';
volatile char double_d = 'F';
volatile char MAIN_DRIVE = 'A';
volatile char trigger_status_command = 'F';
volatile char SSIDfound = 'F';
volatile char IPfound = 'F';
volatile char eqCount = ZERO;

volatile char received_12 = FALSE;
char received = ZERO;
char transmitted = ZERO;
unsigned int tempRXcount;

//------------------------------------------------------------------------------
#pragma vector=EUSCI_A1_VECTOR 
__interrupt void eUSCI_A1_ISR(void){ 
    volatile char tempRX;
    switch(__even_in_range(UCA1IV,VECTOR_INTERRUPT_RANGE)){
          case ZERO:	// Vector 0 - no interrupt
          break;
          case TWO:     // Vector 2 - RXIFG
            switch(READY_TO_SEND){
            case ZERO:
              tempRX = UCA1RXBUF;
              UCA0TXBUF = tempRX; // pass what is written to a1 interrupt to a0 interrupt
              READY_TO_SEND=ONE;              
              break;
            case ONE:
              tempRX = UCA1RXBUF;
              USB_Char_Rx[tempRXcount++]=tempRX;
              if(tempRX == '$'){  // I don't want to check each character, I wan't to check for this character until I find it, and then ignore the next x characters
                READY_TO_SEND=TWO;
                USB_Char_Rx[ZERO]=tempRX;
                tempRXcount=ZERO;
                
              } 
              else{
                UCA0TXBUF = tempRX; // pass what is written to a1 interrupt to a0 interrupt                          
              }                          
              break;
            case TWO: //dollarsign has been caught, watch next 8 characters
              switch(tempRXcount++){
              case ZERO:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;              
              case ONE:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;
              case TWO:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;
              case THREE:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;
              case FOUR:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;
              case FIVE:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;
              case SIX:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                 break;
              case SEVEN:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                break;
              case EIGHT:
                USB_Char_Rx[tempRXcount]=UCA1RXBUF;
                READY_TO_SEND=ONE;
                tempRXcount=ZERO;
                received = TRUE;
                break;                
              default: break;
              }
              break;
            default: break;
            
            }
          break;
          case FOUR:	// Vector 4 – TXIFG
          break; 
          default: break;
}
}

#pragma vector=EUSCI_A0_VECTOR 
__interrupt void eUSCI_A0_ISR(void){ 
    unsigned int A0_tempRX;
    
    switch(__even_in_range(UCA0IV,VECTOR_INTERRUPT_RANGE)){
          case ZERO:	// Vector 0 - no interrupt
          break;
          case TWO:	// Vector 2 - RXIFG
            A0_tempRX = UCA0RXBUF; // take what is passed to a0, which is given to a0 in the a1 service routine and pass it to A0_tempRX
            UCA1TXBUF = A0_tempRX; //take what was passed to a0 and pass it back to a1
            A0_Char_Rx[A0_usb_rx_ring_wr++]=A0_tempRX;
            if(A0_usb_rx_ring_wr >=ONE_HUNDRED){
              A0_usb_rx_ring_wr = BEGINNING;
            }            
            switch(MAIN_DRIVE){/*------MAIN DRIVE SWITCH----*/    
            case 'A': /*-Waiting to confirm init-*/
              switch(A0_tempRX){
              case '-'://Using the first dash as a watch to determine NWCONN-SUCCESS has been printed
                trigger_status_command = 'T';//iot_setup now sends command to iot module that produce a string from which ip and ssid is copied, that function sets MAIN_DRIVE to 'B'
                break;
              default:
                break;
              }
            break;
            case 'B':/*-------looking for specific letters----*/
              switch(A0_tempRX){
              case '=':
                eqCount++;
                if(eqCount==SIX){
                  MAIN_DRIVE='C';
                }
                if(eqCount==TEN){
                  MAIN_DRIVE='D';
                  eqCount=ZERO;
               }
              default:
              break;
             } 
              
            break;/*-------end looking for specific letters----*/
          
            case 'C':/*---------Copying SSID-------------*/
              switch(A0_tempRX){
              case ' '://Assume SSID is found once first space is found, that's why '"Sean's ' is printed
                MAIN_DRIVE='B';
                SSIDfound='T';
                index=ZERO;
                break;
              default:
                SSID[index]=A0_tempRX;
                index++;
              break;
                  }
            break; /*---------End of copying SSID-------------*/ 
              
            case 'D':/*---------Copying IP-------------*/
              switch(A0_tempRX){
              case ' ':
                MAIN_DRIVE='E';
                A0_usb_rx_ring_wr=BEGINNING;
                IPfound='T';
                index=ZERO;
                break;
              default:
                ip[index++]=A0_tempRX;
              break;
                  }
            break; /*---------End of copying IP-------------*/    
            
            case 'E':/*----------------watching for commands---------*/
              switch(A0_tempRX){
              case '$':
                MAIN_DRIVE = 'F';
                A0_usb_rx_ring_wr=BEGINNING;                
                COMMAND_NUMBER++;
                break;
              default:
              break;
                  }              
            break;/*----------------end of watching for commands---------*/
            
            
            case 'F':/*----------------watching for commands---------*/
              switch(A0_tempRX){
              case '\r':
                index=ZERO;
                MAIN_DRIVE = 'E';
                COMMAND_RECEIVED = 'T';
                break;
              case '$':
                index=ZERO;
                COMMAND_NUMBER++;
                break;                
              default:
                command[COMMAND_NUMBER-ONE][index++]=A0_tempRX;
              break;
                  }              
            break;/*----------------end of watching for commands---------*/            
            
            
            default:  /*----MAINDRIVEDEFAULT------*/
            break;/*----MAINDRIVEDBREAK------*/
            
            }/*------MAIN DRIVE SWITCH END----*/    
            
          break;/*-----case TWO break-----*/
          
          case FOUR:	// Vector 4 – TXIFG
          break; 
          default: break;
}
}

