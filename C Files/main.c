//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Sean Daniels
//  Spring 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>


// Function Prototypes
void main(void);
  // Global Variables
extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];
extern char *display[CHAR_DISPLAY_INIT];
extern char RC;
extern volatile unsigned int READY_TO_SEND;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int one_time;

char IOT=TRUE;
char time_change;
char CLOCK_COUNTER = ZERO;
unsigned int twentymscount=ZERO;
unsigned int Last_Time_Sequence;
int cycle_time;
int display_update_count=FALSE;


void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports(USE_GPIO);                    // Initialize Ports
  Init_Clocks();                          // Initialize Clock System
  Init_Conditions();                     // Initialize Variables and Initial Conditions
  Init_Timers();                        // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();
  lcd_4line();
  initial_display_update(); //function located in init
  Init_Serial_UCA1(LOW);
  Init_Serial_UCA0(LOW);
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {   
    switch(Time_Sequence){
      case TWO_HUNDRED_FIFTY:                        
        if(one_time){
          one_time = FALSE;
        }
        Time_Sequence = ZERO;             
        break;
      default: break;
    }
    if(Last_Time_Sequence != Time_Sequence){ //Incrememting variables used to keep time throughout the system
        Last_Time_Sequence = Time_Sequence;
        display_update_count++;
        cycle_time++;
        twentymscount++;
        CLOCK_COUNTER++;
        time_change = TRUE;
    }
    if(display_update_count==DISPLAY_UPDATE_TIME){ // Controls display update, based on main system clock
      display_update_count=FALSE;
      update_display=TRUE;
    }  

     //Busy variable is controlled by command_command handle, command_handle processes 
    command_handle();//reads command, checks key, parses for instructions to be passed to the remainder of the system
    
    switch(IOT){//default true(first segment of project)
    case TRUE:
      iot_action();//take action as assigned by command handler
      break;
    default://IOT set to false by command handler when signal for black line segment is received
      ir_action();//take action as assigned by project description
      Read_Outs();//update IR detetor values, allowing the the correct action to be taken
      break;
    }
    
    if(RC){//once initial command is sent, start timing progression through course
      clock_update();
    }
    Display_Process();//update displays
    
  }//---------END OF MAIN LOOP-----------------//
  
  
  
 }
//-----------------END OF MAIN-----------------------------------------------------//




