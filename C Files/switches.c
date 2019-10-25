#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

char BUTTON_FLAG = FALSE;
char BUTTON_PRESS = FALSE;
char event=NONE;
void Switches_Process(void);
int counter=FALSE;
extern int delay_start;
volatile extern char state;

extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];
extern volatile unsigned char display_changed;
char db1 = FALSE;
char db2 = FALSE;
extern volatile unsigned char Switch1;
extern volatile unsigned char Switch2;
unsigned int Last_Debounce_One = FALSE;
unsigned int Last_Debounce_Two= FALSE;
extern volatile unsigned int debounce_count;
extern volatile unsigned int Debounce;
char button_counter = FALSE;
char begin_transmission = FALSE;
extern char PROCESS;
char SUBPROCESS = FALSE;


//Interrupt_switch handles the debounce for the switches through enabling and disabling various other interrupt
//The function also updates display with the current switch being debounced
void interrupt_switch(void){
    if(Switch1){
      //turn off backlight, done in ISR
      if(Last_Debounce_One != debounce_count){ //want to pass value from debounce count to a new variable, not sure how to do that
        Last_Debounce_One = debounce_count;
        db1++;
      switch(db1){
        case DEBOUNCE_DISPLAY:
        break;
        case DEBOUNCE_TIME:       
          db1 = FALSE;// clear db1 count
          Last_Debounce_One = FALSE;
          //counter zero, increment process to one
          //transmission_process();
          begin_transmission = TRUE;
          Switch1 = FALSE;// clear switch 
          P4IFG &= ~SW1;//clear the flags
          P4IE |= SW1; //enable the interrupt
        break;
      default: break;
        
}
}
}
if(Switch2){
      //turn off backlight, done in ISR
      if(Last_Debounce_Two != debounce_count){ //want to pass value from debounce count to a new variable, not sure how to do that
        Last_Debounce_Two = debounce_count;
        db2++;
      switch(db2){
        case DEBOUNCE_DISPLAY:
        break;
        case DEBOUNCE_TIME:       
          db2 = FALSE;// clear db1 count
          Last_Debounce_Two = FALSE;
          //change_baud();
          Switch2 = FALSE;// clear switch 1
          P2IFG &= ~SW2;//clear the flags
          P2IE |= SW2; //enable the interrupt
        break;
      default: break;
        
}
}
}
if ((!Switch1)&&(!Switch2)){
  if(Debounce == TRUE){
  Debounce = FALSE;
  TB0CCTL1 &= ~CCIE; //disable debounce timer
  TB0CCTL1 &= ~CCIFG; //clear debounce timer flag
  TB0CCTL2 &= ~CCIFG;//clear blink timer flag
  TB0CCTL2 |= CCIE; //enable blink timer flag
  }

}
}

    

    
  


 