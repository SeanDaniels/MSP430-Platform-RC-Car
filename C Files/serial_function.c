//******************************************************************************
//
//  Description: This file contains the function definitions for serial communication project
//
//  Sean Daniels
//  Spring 2019
//  Built with IAR Embedded Workbench
//******************************************************************************

#include "macros.h"

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char A0_Char_Rx[ONE_HUNDRED];
extern volatile unsigned char display_changed;


extern int   DISPLAY_END;
extern unsigned char one_second_count;
extern char PROCESS;


extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];


extern volatile char COMMAND_RECEIVED;
extern volatile unsigned int COMMAND_NUMBER;
extern char ipd1[TEN];
extern char ipd2[TEN];
extern volatile char command[TWO][EIGHT];


char message[TEN];
char expected_char = 'd';
char DURATION = ZERO;
char DURATION_IN_QUARTER_SECONDS=ZERO;
char DIRECTION='Z';
char DIRECTION_ARRAY[FIVE];
char FORWARD_OR_REVERSE;
char MOTOR;
char pending_command_number=ZERO;
char display_station_number;
unsigned int INCREMENT=ZERO;
extern char CAR_ACTION;
extern char BLstate;
char NEXT_ACTION;
char PENDING_FLAG=FALSE;
extern char BUSY;
extern volatile char state;
extern char IOT;
char EXIT_CIRCLE=FALSE;
extern char SETUP_COMMAND;
char found_ip = 'F';
char doneWritingToArray = 'F';
char key[FOUR]={'2','1','6','6'};




void out_character(char character){
  while(!(UCA0IFG&UCTXIFG));
    UCA0TXBUF = character; 
}

void out_string(char* string){
  switch(SETUP_COMMAND){
  case 'B':
   for(int i = ZERO; i<ELEVEN; i++){
    out_character(string[i]);
    __delay_cycles(sevfitty);
    }
    break;
  case 'E':
   for(int i = ZERO; i<TWENTYONE; i++){
    out_character(string[i]);
    __delay_cycles(sevfitty);
    }
    break;
  case 'F':
   for(int i = ZERO; i<SIXTEEN; i++){
    out_character(string[i]);
    __delay_cycles(sevfitty);
    }
    break;
  case 'G':
   for(int i = ZERO; i<TWENTY; i++){
    out_character(string[i]);
    __delay_cycles(sevfitty);
    }
    break;   
  default:
    break;
  }
  /*
  if(trigger_status_command=='T'){

  }
  if(trigger_port_config=='T'){

  }*/

}



void send_message(void){
    out_string(message); 
}


void char_by_char(void){
  for(int i = FALSE; i<=NINE; i++){
    display_line[DISPLAY_UPDATE_THREE][i] = message[i];
  }
  update_string(display_line[DISPLAY_UPDATE_THREE],THREE);
  display_changed=TRUE;
}



int check_key(void){
  for(int i = ZERO; i<FOUR; i++){
  if(command[COMMAND_NUMBER-ONE][i]!=key[i]){
    COMMAND_NUMBER--;
    return ZERO;
    
    }
  }
  return ONE;
}

void parse_command(void){ //command number = 2
  char index;
  if((COMMAND_NUMBER--)>ONE){
    pending_command_number=TRUE;
  }
  if(pending_command_number){
    index=(COMMAND_NUMBER+ONE)-(COMMAND_NUMBER*(COMMAND_NUMBER+ONE)); 
  }
  if(!pending_command_number)
    index=ZERO;
  for(int i = FOUR; i<EIGHT; i++){
    if(i==FOUR)
      DIRECTION = command[index][i];
    switch(DIRECTION){
    case 'P':
    if(i==FIVE)
      MOTOR = command[index][i];
    if(i==SIX)
      FORWARD_OR_REVERSE = command[index][i];
    if(i==SEVEN)
      INCREMENT = ((command[index][i] - HEX_TO_ASCII) * ONE_THOUSAND);   
      //direction_duration(DIRECTION);
    break;
    case '6':
      EXIT_CIRCLE=TRUE;
      DURATION='5';
      break;
    case 'D':
      display_station_number = command[index][SEVEN];
      break;
    case 'X':
        end_case();
        PENDING_FLAG=FALSE;
        NEXT_ACTION=FALSE;
        BUSY=FALSE;
        CAR_ACTION='Z';
    break;
    default:
    if(i==FIVE)
      DURATION = ((command[index][i] - HEX_TO_ASCII) * ONE_HUNDRED);
    if(i==SIX)
      DURATION += ((command[index][i] - HEX_TO_ASCII) * TEN);
    if(i==SEVEN)
      DURATION += ((command[index][i] - HEX_TO_ASCII));
      
    break;
    }
  }
  direction_duration(DIRECTION);
  if(!BUSY)
  CAR_ACTION=DIRECTION;
  if(BUSY){
    NEXT_ACTION=DIRECTION;
    PENDING_FLAG=TRUE;
  }
}

void direction_duration(char direction){
  switch(DIRECTION){
  case 'F':
    DIRECTION_ARRAY[ZERO]=DURATION;
    break;
  case 'B':
    DIRECTION_ARRAY[ONE]=DURATION;
    break;
  case 'R':
    DIRECTION_ARRAY[TWO]=DURATION;
    break;
  case 'L':
    DIRECTION_ARRAY[THREE]=DURATION;
    break;
 case 'P':
    DIRECTION_ARRAY[FOUR]=DURATION;
    break; 
  case '6':
      DIRECTION_ARRAY[THREE]=DURATION;
  default:
    break;    
  }
}
