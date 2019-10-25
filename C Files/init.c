//------------------------------------------------------------------------------
//
//  Description: This file contains the general initialization routines
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

extern char display_line[FOUR][ELEVEN];
extern char *display[FOUR];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Init_Conditions(void);
void Init_LEDs(void);
void Init_Clocks(void);

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=ZERO;i<ELEVEN;i++){
    display_line[ZERO][i] = RESET_STATE;
    display_line[ONE][i] = RESET_STATE;
    display_line[TWO][i] = RESET_STATE;
    display_line[THREE][i] = RESET_STATE;
  }
  display_line[ZERO][TEN] = ZERO;
  display_line[ONE][TEN] = ZERO;
  display_line[TWO][TEN] = ZERO;
  display_line[THREE][TEN] = ZERO;

  display[ZERO] = &display_line[ZERO][ZERO];
  display[ONE] = &display_line[ONE][ZERO];
  display[TWO] = &display_line[TWO][ZERO];
  display[THREE] = &display_line[THREE][ZERO];
  update_display = ZERO;
  update_display_count = ZERO;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}
void initial_display_update(void){
  strcpy(display_line[DISPLAY_UPDATE_ZERO], "Project 10");
  update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
  strcpy(display_line[DISPLAY_UPDATE_ONE], "          ");
  update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
  strcpy(display_line[DISPLAY_UPDATE_TWO], "          ");
  update_string(display_line[DISPLAY_UPDATE_TWO], TWO);
  strcpy(display_line[DISPLAY_UPDATE_THREE], "          ");
  update_string(display_line[DISPLAY_UPDATE_THREE], THREE);
  enable_display_update();
  Display_Update(THREE,TWO,ONE,ZERO);
}
void Init_IR(void){
  P5OUT |= IR_LED;
}