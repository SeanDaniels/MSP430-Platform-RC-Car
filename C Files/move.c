#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern char initial_black_line_locator;
extern char PROCESS;
extern char CAR_ACTION;
extern unsigned char one_second_count;
extern unsigned char quarter_second_count;
extern unsigned int twentymscount;
volatile char state = START;
extern char CAR_LOCATION;
extern int cycle_time;
extern volatile unsigned int V_DET_L;
extern volatile unsigned int V_DET_R;
extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];
extern volatile unsigned char display_changed;
extern char DIRECTION_ARRAY[FIVE];
extern char FORWARD_OR_REVERSE;
extern char MOTOR;
extern char IOT;
extern char EXIT_CIRCLE;
extern unsigned int INCREMENT;
unsigned int LEFT_REVERSE_PWM = STARTING_PWM;
unsigned int LEFT_FORWARD_PWM = STARTING_PWM;
unsigned int RIGHT_REVERSE_PWM = STARTING_PWM;
unsigned int RIGHT_FORWARD_PWM = STARTING_PWM;
char ipd1[TEN];
char ipd2[TEN];
char ssid[TEN];
char BUSY=FALSE;
char APPROACH_CIRCLE=TRUE;
char MF = FALSE;
char TURNED=FALSE;
char BLstate=START;
char LENGTH_OF_FIRST_FORWARD=TRAVEL_TIME_F_ONE;
char LENGTH_OF_SECOND_FORWARD=TRAVEL_TIME_F_TWO; 
char NINETY_DEG=LENGTH_OF_90_DEG_LEFT_TURN;
//PWM Speeds, left is wheel moves faster;
unsigned int LEFT_FORWARD_ADJUST=THIRTY_THOUSAND;







void DISABLE_MOTORS(void){
//TEN_PERCENT_SPEED=WHEEL_OFF;
LEFT_FORWARD_PWM=WHEEL_OFF;
RIGHT_FORWARD_PWM=WHEEL_OFF;
RIGHT_REVERSE_PWM=WHEEL_OFF;
LEFT_REVERSE_PWM=WHEEL_OFF;
LEFT_FORWARD_ADJUST=WHEEL_OFF;
}
/*--------------------------------------------------------*/
/*----functions used by all movement state machines-------*/
void Stop_After_Time(char duration){
  if(twentymscount==duration*TWELVE){
    state = END;
    }
  
}
void BL_Pause(char duration){
  if(twentymscount==duration*TWELVE){
    switch(PROCESS){
    case APPROACHING_LINE:
      if(MF==THREE){
        BLstate=END;
        MF=ZERO;
      }
      else
        BLstate=MOVE_FORWARD;
      break;
    case ROTATE_RIGHT_AND_LOOK:
      state=END;
      break;
    case FOLLOW_LINE:
      switch(state){
      case PAUSE:
        state=START;
        break;
      case END:
        BL_display('5');
        IOT=TRUE;
        BUSY=FALSE;
        PROCESS='Z';
        TURNED=FALSE;
        CAR_ACTION='K';
        state = START;
        break;
      }
      break;
    }
  }
}

void end_case_bl(void){
      Total_Stop();
      state = START;
      if(PROCESS == FOLLOW_LINE){
        PROCESS = FALSE;
      }
      if(PROCESS == ROTATE_RIGHT_AND_LOOK){
        PROCESS = FOLLOW_LINE; 
        BL_display('3');
      }
      if(PROCESS == APPROACHING_LINE){
        PROCESS = ROTATE_RIGHT_AND_LOOK;
      }
      
 
}
void end_case(void){
  switch(IOT){
  case TRUE:
    if(CAR_ACTION!='K'){
    Total_Stop();
    CAR_ACTION='Z';
    BUSY=FALSE;
    og_IOT_display();
    }
    else{
      if(TURNED){
        Total_Stop();
        CAR_ACTION='Z';
        BL_display('8');
        final_out();
      }
      else
        TURNED=TRUE;
    }
    state = START;
    break;
  default:
    Total_Stop();
    state=START;
    switch(BLstate){
    case TURN_LEFT:
      if(MF==TWO){
        Init_IR();
        BLstate=PAUSE;
        BL_display('2');
      }
      else{
        BLstate=MOVE_FORWARD;
      }
      break;
    case MOVE_FORWARD:
      BLstate=TURN_LEFT;
      if(MF<TWO)
      MF++;
      if(MF==THREE){
        BL_display('7');
        P6OUT |= LCD_BACKLITE; 
        BLstate=PAUSE;
        
      }
      break;
    default:
      break;
    }
    break;
  }
}


void Total_Stop(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF; 
  LEFT_FORWARD_SPEED = WHEEL_OFF; 
  RIGHT_REVERSE_SPEED = WHEEL_OFF; 
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}
/*----functions used by all movement state machines-------*/
/*--------------------------------------------------------*/




/*--------------------------------------------------------*/
/*------Forward movement state machine and functions------------------*/
void move_forward(void){
  switch(state){
  case START:
    if(IOT){
      if(CAR_ACTION!='K'){
      BUSY=TRUE;
      clear_display();
      movement_display();      
      }
    }
    Start_Forward();
    cycle_time=FALSE;
    break;
  case RUN:
    if(IOT){
      if(CAR_ACTION=='K')
        DIRECTION_ARRAY[ZERO]=TRAVEL_TIME_F_TWO;
      Stop_After_Time(DIRECTION_ARRAY[ZERO]);
    }
    if(!IOT){
      if(!MF)     
        Stop_After_Time(LENGTH_OF_SECOND_FORWARD);//this is the length of time to travel forward after turning left 
      if(MF)
        Stop_After_Time(LENGTH_OF_FIRST_FORWARD);   
      if(MF==TWO){
        if(cycle_time>DELAY_TIME_FOR_CAR_LOC_UPDATE){
        if(initial_black_line_locator){
          MF++;
          state = END;
        }
        }
      }
    }
    break;
  case END:
    /*if(IOT){
      if(CAR_ACTION=='K')
        //TURNED=FALSE;
    }*/  
    end_case();
    
    break;
  default: break;
  }
  
}
void Start_Forward(void){
  Forward_On();
  twentymscount=ZERO;
  state = RUN;
}
void Forward_On(void){
  if(PROCESS!=FOLLOW_LINE){
  RIGHT_FORWARD_SPEED = RIGHT_FORWARD_PWM; // P6.0 Right Forward PWM ON amount
  LEFT_FORWARD_SPEED = LEFT_FORWARD_ADJUST;
  }
  else{
    RIGHT_FORWARD_SPEED = TEN_PERCENT_SPEED; // P6.0 Right Forward PWM ON amount
    LEFT_FORWARD_SPEED = TEN_PERCENT_SPEED;
  }
}
/*------Forward movement state machine and functions------------------*/
/*--------------------------------------------------------*/


/*--------------------------------------------------------*/
/*------backward movement state machine and functions------------------*/
void move_backwards(void){
  switch(state){
  case START:
    BUSY=TRUE;
    clear_display();
    movement_display();
    Start_Reverse();
    break;
  case RUN:
    Stop_After_Time(DIRECTION_ARRAY[ONE]);
    break;
  case END:
    end_case();
    break;
  default: break;
  }
  
}
void Start_Reverse(void){
  Reverse_On();
  twentymscount=ZERO;
  state = RUN;
}
void Reverse_On(void){
  RIGHT_REVERSE_SPEED = RIGHT_REVERSE_PWM; // P6.0 Right Forward PWM ON amount
  LEFT_REVERSE_SPEED = LEFT_REVERSE_PWM; 
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/

/*--------------------------------------------------------*/
/*------left turn movement state machine and functions------------------*/
void turn_left(void){
  switch(state){
  case START:
    if(IOT){ 
     if(CAR_ACTION!='K'){
     BUSY=TRUE;
     clear_display();
     movement_display();
    }
    }
    Start_Rot_Left();

    break;
  case RUN:
    if(IOT){
      if(CAR_ACTION=='K')
        DIRECTION_ARRAY[THREE]=LENGTH_OF_90_DEG_LEFT_TURN;
      Stop_After_Time(DIRECTION_ARRAY[THREE]);
    }
    if(!IOT)
      if(MF==TWO)
        Stop_After_Time(FOUR);
      else
      Stop_After_Time(NINETY_DEG); //will probably need to tweak this value, this is what determines how close to a 90deg left turn the car makes
    break;
  case END:
    end_case();
  }
}

void Start_Rot_Left(void){
  Travel_CCW();
  twentymscount=ZERO;
  state=RUN;
}
void Travel_CCW(void){
  if(CAR_ACTION=='K')
    LEFT_FORWARD_SPEED = LEFT_FORWARD_PWM;
  else
  RIGHT_FORWARD_SPEED = RIGHT_FORWARD_PWM; // P6.0 Right Forward PWM ON amount
  //LEFT_REVERSE_SPEED = LEFT_REVERSE_PWM;
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/

/*--------------------------------------------------------*/
/*------right turn movement state machine and functions------------------*/
void turn_right(void){
  switch(state){
  case START:
    if(IOT){
      BUSY=TRUE;
      clear_display();
      movement_display();
      Start_Rot_Right();
    }
    if(!IOT){
      Start_Rot_Right();
    }
    break;
  case RUN:
    if(IOT){
      Stop_After_Time(DIRECTION_ARRAY[TWO]);
    }
    if(!IOT){
      Stop_After_Time(NINETY_DEG);//may have to tweak this to get a perfect right turn
    }
    break;
  case END:
    if(IOT)
      og_IOT_display();
    end_case(); 
  }
}
void Start_Rot_Right(void){
  Travel_CW();
  twentymscount=ZERO;
  state = RUN;
}
void Travel_CW(void){
  //RIGHT_REVERSE_SPEED = RIGHT_REVERSE_PWM; // P6.0 Right Forward PWM ON amount
  if(IOT)
  LEFT_FORWARD_SPEED = LEFT_FORWARD_PWM;
  else{
    RIGHT_REVERSE_SPEED = TEN_PERCENT_SPEED;
    LEFT_FORWARD_SPEED = TEN_PERCENT_SPEED;
  }
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/


 
 
  
/*--------------------------------------------------------*/
/*------pwm calibration state machine and functions------------------*/
void calibrate_pwm(void){
  switch(MOTOR){
  case 'L': //LEFT MOTOR
    switch(FORWARD_OR_REVERSE){
    case 'R'://REVERSE
      if(state==START){
      LEFT_REVERSE_PWM=LEFT_REVERSE_PWM-INCREMENT;        
      }
      //calibrate_test('A');
      
      break;
    default:
      if(state==START)
      LEFT_FORWARD_PWM=LEFT_FORWARD_PWM-INCREMENT;
      //calibrate_test('B');
      break;
    }
    break;
  case 'U'://RESET ALL PWMS TO MAX
    RIGHT_FORWARD_PWM = STARTING_PWM;
    RIGHT_REVERSE_PWM = STARTING_PWM;
    LEFT_FORWARD_PWM = STARTING_PWM;
    LEFT_REVERSE_PWM = STARTING_PWM;
    break;
  default://RIGHT MOTOR
    switch(FORWARD_OR_REVERSE){
    case 'R'://REVERSE
      if(state==START)
       RIGHT_REVERSE_PWM=RIGHT_REVERSE_PWM-INCREMENT;
       //calibrate_test('C');
      break;
    default:
      if(state==START)
      RIGHT_FORWARD_PWM=RIGHT_FORWARD_PWM-INCREMENT;
      //calibrate_test('D');
      break;
    }    
    break;
  }
  end_case();
}
/*--------------------------------------------------------*/
/*--------------------------------------------------------*/


