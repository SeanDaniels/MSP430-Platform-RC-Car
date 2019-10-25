#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern unsigned int twentymscount;
extern volatile char MAIN_DRIVE;
extern volatile char SSIDfound;
extern volatile char IPfound;
extern char CAR_ACTION;
extern char PENDING_FLAG;
extern char PROCESS;
extern char IOT;
extern char TURNED;
extern char NEXT_ACTION;
extern char display_station_number;
extern volatile unsigned int COMMAND_NUMBER;
extern volatile char COMMAND_RECEIVED;
extern char  pending_command_number;
extern char RC;
char CAR_ACTION = 'S';
unsigned char ipcycle = ZERO;
char SETUP_COMMAND = 'A'
;extern volatile char trigger_status_command;
char status_command[ELEVEN]= {'A', 'T', '+','N','S','T','A','T','=','?',0x0D};
char port_config2[SIXTEEN]= {'A', 'T', '+','N','S','T','C','P','=','6','6','6','6',',','1', 0x0D};
char port_config1[TWENTYONE]= {'A', 'T', '+','P','I','N','G','=','g','o','o','g','l','e','.','c','o','m',',','3',0x0D};
char port_config3[TWENTY]= {'A', 'T', '+','W','S','Y','N','C','I','N','T','R','L','=','6','5','5','3','5', 0x0D};

void iot_action(void){
    switch(CAR_ACTION){
    case 'F':
      move_forward();
      break;
    case 'B':
      move_backwards();
    break;
    case 'R':
      turn_right();
      break;
    case 'L':
      turn_left();
      break;  
    case 'P':
      calibrate_pwm();
      break; 
    case 'S':
      setup_IOT();
      break;
    case 'D':
      display_station(display_station_number);
      break;
    case 'X':
      end_case();//SHUTS OFF ALL MOTORS
      PROCESS='Z';
      break;
    case 'J':
      PROCESS=APPROACHING_LINE;
      IOT=FALSE;
      break;
    case 'K':
      if(!TURNED)
        turn_left();
      if(TURNED)
        move_forward();
      break;
    default:
      if(!PENDING_FLAG){
        CAR_ACTION='Z';      
      }
      if(PENDING_FLAG){
        CAR_ACTION=NEXT_ACTION;
        PENDING_FLAG=FALSE;
      }
      break;
  }
  }

void command_handle(void){
  switch(COMMAND_RECEIVED){
      case 'T':
          if(check_key()){
            parse_command();
          }
          if(!(COMMAND_NUMBER)){
          COMMAND_RECEIVED='F'; 
          pending_command_number=FALSE;
          }
          if(RC==FALSE)
            setup_timer();//intitialize outuput timer once first command is received
        break;
      default:
        break;
    }
}

void setup_IOT(void){
  switch(SETUP_COMMAND){
  case 'A':
    if(twentymscount>TIME_TO_RESTART_IOT){
      P5OUT |= IOT_RESET;
      ipcycle=ZERO;
      SETUP_COMMAND = 'B';  
    }      
    break;
  case 'B':
    if(trigger_status_command=='T'){
      switch(ipcycle++){
      case ONE_HUNDRED:
        out_string(status_command);
        MAIN_DRIVE='B';
        SETUP_COMMAND = 'C';
        ipcycle=ZERO;
      break;
      default: break;
        }
    }      
  break;
  case 'C':
    if(SSIDfound == 'T'){
      
      //display_ssid();
     // display_success();
      SETUP_COMMAND='D';
    }    
  break;
  case 'D':
    if(IPfound=='T'){
      display_ip();//IP ADDR placed on lines 1 and 2
      SETUP_COMMAND='E';
    }    
  break;
  case 'E':
    out_string(port_config1);
    SETUP_COMMAND='F';
    break;
  case 'F':
    out_string(port_config2);
    SETUP_COMMAND='G';
    break;
  case 'G':
    out_string(port_config3);
    display_success();
    CAR_ACTION='Z';
    break;
  default:
  break;
  }
}