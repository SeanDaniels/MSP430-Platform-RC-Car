#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

extern char CAR_ACTION;
extern char PENDING_FLAG;
char PROCESS = FALSE;
extern char IOT;
extern char TURNED;
extern char NEXT_ACTION;
extern char display_station_number;
extern volatile unsigned int COMMAND_NUMBER;
extern volatile char COMMAND_RECEIVED;
extern char  pending_command_number;
extern char RC;
extern char BLstate;
extern volatile char state;
extern int cycle_time;
extern unsigned int twentymscount;
extern char CAR_LOCATION;
extern char APPROACH_CIRCLE;
extern char EXIT_CIRCLE;
char LAST_CAR_LOCATION;


void ir_action(void){
  switch(PROCESS){
    case APPROACHING_LINE:
      line_approach_setup();
    break;
    case LOOKING_FOR_LINE:
      Look_For_Line();
      break; 
    case ROTATE_RIGHT_AND_LOOK:
      Look_Right();
      break;
    case FOLLOW_LINE:
      Stay_On();
      break;      
    default:break;
  }
}

/*--------------------------------------------------------*/
/*----------Black Line approach state machine-------------*/
 void line_approach_setup(void){
      switch(BLstate){
      case START:
        BL_display('1');
        twentymscount=ZERO;
        BLstate=PAUSE;
        break;
      case PAUSE:
        BL_Pause(TWO_SECOND_PAUSE);//may have to tweak this to get 2 seconds right
        break;
      case MOVE_FORWARD:
        move_forward();
        break;
      case TURN_LEFT:
        turn_left();
        break;
      case END:
        end_case_bl();
        break;
      default:
        break;
      }
    }
/*--------------------------------------------------------*/
/*---------------------------------------------------------*/











/*-------------Look for line state machine----------------*/
/*--------------------------------------------------------*/
void Look_For_Line(void){
  switch(state){
  case START:
    Start_Forward();
    break;
  case RUN:
    Stop_At_Line();
    break;
  case END:
    end_case_bl();
    break;
  default: break;
  }
  
}
void Stop_At_Line(void){
  if(cycle_time>TWO){
  if(CAR_LOCATION==ON_LINE){
    Total_Stop();
    state = PAUSE;
    cycle_time=FALSE;
    twentymscount=FALSE;
  }
  }
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/

/*-------------rotate right and look state machine----------------*/
/*--------------------------------------------------------*/
void Look_Right(void){
  switch(state){
  case START:
    Start_Rot_Right();
    cycle_time=FALSE;
    break;
  case RUN:
    Stop_At_Line();
    break;
  case PAUSE:
    BL_Pause(TWO_SECOND_PAUSE);
    break;
  case END:
    end_case_bl();
    break;
  default: break;
  }
  
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/


/*------------follow line state maching----------------*/
/*--------------------------------------------------------*/
void Stay_On(void){
  switch(state){
  case START:
    Start_Forward();
    break;
  case RUN:
    Move_And_Test();
    break;
  case PAUSE:
    Total_Stop();
    APPROACH_CIRCLE=FALSE;
    BL_display('4');
    BL_Pause(TWO_SECOND_PAUSE);
    break;
  case END:
    Total_Stop();
    BL_Pause(TWO_SECOND_PAUSE);
    break;
  default: break;
  }
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/



/*------------Staying on the line---------------*/
/*--------------------------------------------------------*/
void Move_And_Test(void){
  if(!EXIT_CIRCLE){
    if(APPROACH_CIRCLE){
    if(twentymscount<120){
      if(LAST_CAR_LOCATION != CAR_LOCATION){
       LAST_CAR_LOCATION = CAR_LOCATION;
      if(CAR_LOCATION == ON_LINE){
        Total_Stop();
        RIGHT_FORWARD_SPEED = TEN_PERCENT_SPEED; // P6.0 Right Forward PWM ON amount
        LEFT_FORWARD_SPEED = TEN_PERCENT_SPEED;
      }
      if(CAR_LOCATION == ONLY_RIGHT){
        Total_Stop();
        RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM ON amount
        LEFT_FORWARD_SPEED = TEN_PERCENT_SPEED;
      }
      if(CAR_LOCATION == ONLY_LEFT){
        Total_Stop();
        RIGHT_FORWARD_SPEED = TEN_PERCENT_SPEED; // P6.0 Right Forward PWM ON amount
        LEFT_FORWARD_SPEED = WHEEL_OFF;
      }  
      if(CAR_LOCATION == OFF_LINE){
        Total_Stop();
        LEFT_REVERSE_SPEED = TEN_PERCENT_SPEED;
        RIGHT_FORWARD_SPEED = TEN_PERCENT_SPEED; 
        
     
      }
      
        } 
      }
    else{
      state=PAUSE;
      //APPROACH_CIRCLE=FALSE;
    }
    }
    else{
     if(LAST_CAR_LOCATION != CAR_LOCATION){
      LAST_CAR_LOCATION = CAR_LOCATION;
      if(CAR_LOCATION == ON_LINE){
        Total_Stop();
        RIGHT_FORWARD_SPEED = TEN_PERCENT_SPEED; // P6.0 Right Forward PWM ON amount
        LEFT_FORWARD_SPEED = TEN_PERCENT_SPEED;
      }
      if(CAR_LOCATION == ONLY_RIGHT){
        Total_Stop();
        RIGHT_FORWARD_SPEED   = WHEEL_OFF; // P6.0 Right Forward PWM ON amount
        LEFT_FORWARD_SPEED = TEN_PERCENT_SPEED;
      }
      if(CAR_LOCATION == ONLY_LEFT){
        Total_Stop();
        RIGHT_FORWARD_SPEED = TEN_PERCENT_SPEED; // P6.0 Right Forward PWM ON amount
        LEFT_FORWARD_SPEED = WHEEL_OFF;
      }  
      if(CAR_LOCATION == OFF_LINE){
        
        Total_Stop();
        LEFT_FORWARD_SPEED =TEN_PERCENT_SPEED;
        RIGHT_REVERSE_SPEED = TEN_PERCENT_SPEED; 
        
     
      }
       
        } 
    }
  }
  else{
    state=END;
    twentymscount=ZERO;
  }

}
