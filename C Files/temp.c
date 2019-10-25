void calibrate_black(void){
  switch(state){
  case START:
    display_for_calibrate();
    break;
  case RUN:
    set_white_vals();
    break;
  case END:
    prompt_user_to_reset();
    break;
  default:break;
  }
}
void calibrate_white(void){
  switch(state){
  case START:
    display_for_calibrate();
    break;
  case RUN:
    set_white_vals();
    break;
  case END:
    prompt_user_to_reset();
    break;
  }
}

void set_white_vals(void){//I don't want to use a timer for this
    if(PROCESS == CALIBRATE_WHITE){
    Hex_To_Binary(V_DET_L);
    LCD_UPDATE(THREE,ZERO);
    strcpy(white_val_l, ADC_Value);
    Hex_To_Binary(V_DET_R);
    LCD_UPDATE(THREE,SIX);
    strcpy(white_val_r, ADC_Value);    
    }
    else{
    Hex_To_Binary(V_DET_L);
    LCD_UPDATE(THREE,ZERO);
    strcpy(black_val_l, ADC_Value);
    Hex_To_Binary(V_DET_R);
    LCD_UPDATE(THREE,SIX);
    strcpy(black_val_r, ADC_Value);
    }
    //pressing the switch locks the value of the sensors
     //gotta figure out what to do here, I want the switch to push me to the next event
    if(SUBPROCESS){
      strcpy(display_line[DISPLAY_UPDATE_ONE], " COMPLETE ");
      update_string(display_line[DISPLAY_UPDATE_ONE], ONE); 
      display_changed=TRUE;
      SUBPROCESS=FALSE;
      state = END;
    }

  

}
void display_for_calibrate(void){
  if(PROCESS == CALIBRATE_WHITE){
      strcpy(display_line[DISPLAY_UPDATE_ONE], "CALIBRATEW");
  }
  else{
      strcpy(display_line[DISPLAY_UPDATE_ONE], "CALIBRATEB");
  }

  update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
  strcpy(display_line[DISPLAY_UPDATE_TWO], "          ");
  update_string(display_line[DISPLAY_UPDATE_TWO], TWO);
  strcpy(display_line[DISPLAY_UPDATE_THREE], "          ");
  update_string(display_line[DISPLAY_UPDATE_THREE], THREE);  
  cycle_time=FALSE;
  state=RUN;
  display_changed=TRUE;
}