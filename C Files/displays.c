#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern int PROCESS;
extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];
extern volatile unsigned char display_changed;
extern volatile char ip[TWENTY];
extern volatile char SSID[TEN];
extern volatile char command[TWO][EIGHT];
int ipindex;
int i = FALSE;
extern char CAR_ACTION;
extern char ipd1[TEN];
extern char ipd2[TEN];
extern char ssid[TEN];
extern unsigned int LEFT_REVERSE_PWM;
extern unsigned int LEFT_FORWARD_PWM;
extern unsigned int RIGHT_REVERSE_PWM;
extern unsigned int RIGHT_FORWARD_PWM;
int n ;


void clear_display(void){
    strcpy(display_line[DISPLAY_UPDATE_ZERO], "          ");
    update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    strcpy(display_line[DISPLAY_UPDATE_ONE], "          ");
    update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
    strcpy(display_line[DISPLAY_UPDATE_TWO], "          ");
    update_string(display_line[DISPLAY_UPDATE_TWO], TWO);
    strcpy(display_line[DISPLAY_UPDATE_THREE], "          ");
    update_string(display_line[DISPLAY_UPDATE_THREE], THREE);  
    display_changed=TRUE; 
}
void display_success(void){
 update_string("xW8NG4CMDx", ZERO);
 display_changed=TRUE;
}

void display_ssid(void){ //4->16
    char dotCount=ZERO;
    //int i = ZERO;
    ipindex=ZERO;
    for(int j=ZERO; j<TEN; j++){
      //display_line[DISPLAY_UPDATE_ZERO][j]=ip[ipindex-ONE]
      if(SSID[ipindex++]=='\0'){
        dotCount++;
      }
      if(dotCount<ONE){
        display_line[DISPLAY_UPDATE_ZERO][j+TWO]=SSID[ipindex-ONE];
      }
  update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
  strcpy(ssid,display_line[DISPLAY_UPDATE_ZERO]);
  display_changed=TRUE;
 }
}

void display_ip(void){ //4->16
    char dotCount=ZERO;
    int i = ZERO;
    ipindex=ZERO;
    for(int j=ZERO; j<TWO_DISPLAY_LINES; j++){
      if(ip[ipindex++]=='.'){
        dotCount++;
      }
      if(dotCount<=TWO){
        display_line[DISPLAY_UPDATE_ONE][j+TWO]=ip[ipindex-ONE];
      }
      else {
        display_line[DISPLAY_UPDATE_TWO][(i++)+THREE]=ip[ipindex-TWO];
      }
  update_string(display_line[DISPLAY_UPDATE_TWO], TWO);
  update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
  strcpy(ipd1,display_line[DISPLAY_UPDATE_ONE]);
  strcpy(ipd2,display_line[DISPLAY_UPDATE_TWO]);
  display_changed=TRUE;
  //IPfound=='F';
 }
}

void movement_display(void){
  switch(CAR_ACTION){
  case 'F':
    strcpy(display_line[DISPLAY_UPDATE_ONE], "  FORWARD ");
    update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
    break;
  case 'B':
    strcpy(display_line[DISPLAY_UPDATE_ONE], "  REVERSE ");
    update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
    break;
  case 'L':
    strcpy(display_line[DISPLAY_UPDATE_ONE], "   LEFT   ");
    update_string(display_line[DISPLAY_UPDATE_ONE], ONE);
    break;
  case 'R':
    strcpy(display_line[DISPLAY_UPDATE_ONE], "  RIGHT   ");
    update_string(display_line[DISPLAY_UPDATE_ONE], ONE);    
    break;
  default:
    break;    
  }
    display_changed=TRUE;
    P6OUT |= LCD_BACKLITE;
}
void og_IOT_display(void){
  lcd_4line();
  update_string("xW8NG4CMDx", ZERO);
  //update_string("          ",ONE);
  update_string(ipd1, ONE);
  update_string(ipd2, TWO);
  P6OUT &= ~LCD_BACKLITE;  
  display_changed=TRUE;
}


void display_station(char station){
  switch(station){
  case '1':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 01");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '2':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 02");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
     break;    
  case '3':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 03");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '4':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 04");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '5':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 05");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '6':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 06");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '7':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 07");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;    
  case '8':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "ARRIVED 08");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;    
  default:
    break;
  }
  station='Z';
  display_changed=TRUE;
  CAR_ACTION='Z';
}
void PWM_display(char cond){
  switch(cond){
    case 'A':
      update_string(display_line[DISPLAY_UPDATE_THREE], THREE);
      display_changed=TRUE;     
      break;
    case 'B':
      update_string(display_line[DISPLAY_UPDATE_THREE], THREE);
      display_changed=TRUE;  
      break;
    case 'C':
      update_string(display_line[DISPLAY_UPDATE_THREE], THREE);
      display_changed=TRUE;  
      break;
    case 'D':      
      update_string(display_line[DISPLAY_UPDATE_THREE], THREE);
      display_changed=TRUE;  
      break;
    default:
      break;
  }
}

void BL_display(char cond){
  switch(cond){
  case '1':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], " BL START ");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '2':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "BL INTRCPT");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '3':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "BL TRAVEL ");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '4':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "BL CIRCLE ");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '5':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "BL  EXIT  ");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;    
  case '6':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "BLCOMPLETE");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  case '7':
     strcpy(display_line[DISPLAY_UPDATE_ZERO], " BL found ");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;    
  default:
     strcpy(display_line[DISPLAY_UPDATE_ZERO], "  DONE    ");
     update_string(display_line[DISPLAY_UPDATE_ZERO], ZERO);
    break;
  }
  display_changed=TRUE;
}