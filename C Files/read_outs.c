//read outs
#include "macros.h"


extern volatile unsigned int V_DET_L;
extern volatile unsigned int V_DET_R;
extern char ADC_Value[FOUR];
char LEFT_ON=FALSE;
char RIGHT_ON=FALSE;
char CAR_LOCATION;
int last_hundred_mili_second_count;
unsigned int hundred_mili_second_counter=ZERO;
extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];
char one=HEX_TO_ASCII;
char ten=HEX_TO_ASCII;
char tenth = HEX_TO_ASCII;
char hundred=HEX_TO_ASCII;
char initial_black_line_locator=FALSE;
char RC=FALSE;
extern char CLOCK_COUNTER;

void Read_Outs(void){
    L_Read_Out();
    Car_Loc();
    //clock_update();
}





void L_Read_Out(void){
  Hex_To_Binary(V_DET_L);
  Hex_To_Binary(V_DET_R);  
  if(V_DET_L < V_DET_L_EDGE){
    LEFT_ON=FALSE;
  }
  else{     
    LEFT_ON=TRUE;
  }
  if(V_DET_R < V_DET_R_EDGE){
    RIGHT_ON=FALSE;
  }
  else{        
    RIGHT_ON=TRUE;
  }
  if(V_DET_R>FIVE_HUNDRED){
    initial_black_line_locator=TRUE;
  }
  if(V_DET_R<FIVE_HUNDRED){
    initial_black_line_locator=FALSE;
  }

}


void Car_Loc(void){
  if(RIGHT_ON&&LEFT_ON){
    CAR_LOCATION=ON_LINE;
  }
  if(!RIGHT_ON&&!LEFT_ON){
    CAR_LOCATION = OFF_LINE;
  }
  if(RIGHT_ON && !LEFT_ON){
    CAR_LOCATION = ONLY_RIGHT;
  }
  if(LEFT_ON && !RIGHT_ON){
    CAR_LOCATION=ONLY_LEFT;
  }
}
void setup_timer(void){
  hundred_mili_second_counter=FALSE;
  tenth=HEX_TO_ASCII;
  one=HEX_TO_ASCII;
  ten=HEX_TO_ASCII;
  hundred=HEX_TO_ASCII;
  CLOCK_COUNTER=FALSE;
  RC=TRUE;
}

void clock_update(void){
  if(CLOCK_COUNTER==FIVE){//resetting counter that keeps timer to be dislayed on LCD
      hundred_mili_second_counter++;
      CLOCK_COUNTER=ZERO;
    }
  if(last_hundred_mili_second_count!=hundred_mili_second_counter){
    last_hundred_mili_second_count = hundred_mili_second_counter;
    tenth++;
    if(tenth==HEX_TO_ASCII_CUT){
      tenth = HEX_TO_ASCII;
      one++;
      if(one==HEX_TO_ASCII_CUT){
        one=HEX_TO_ASCII;
        ten++;
        if(ten==HEX_TO_ASCII_CUT){
          ten = HEX_TO_ASCII;
          hundred++;
          if(hundred==HEX_TO_ASCII_CUT){
            hundred = HEX_TO_ASCII;
          }
        }
      }
    }
  }
 
}
void final_out(void){
    display_line[THREE][ZERO]=hundred;
    display_line[THREE][ONE]=ten;
    display_line[THREE][TWO]=one;
    display_line[THREE][THREE]=tenth;
}

