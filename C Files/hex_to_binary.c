#include "macros.h"

char thousandsT = FALSE;
char hundredsT = FALSE;
char tensT = FALSE;
char onesT = FALSE;
char ADC_Value[FOUR]="    ";
extern char display_line[DISPLAY_LINE_ROW_INIT][DISPLAY_LINE_COL_INIT];
extern volatile unsigned char display_changed;

void Hex_To_Binary(volatile unsigned int ValuePassedT){
  thousandsT = FALSE;
  hundredsT = FALSE;
  tensT = FALSE;
  onesT = FALSE;
  while(ValuePassedT >= ONE_THOUSAND){
    thousandsT++;
    ValuePassedT = ValuePassedT - ONE_THOUSAND;
  }
  while(ValuePassedT >= ONE_HUNDRED){
    hundredsT++;
    ValuePassedT = ValuePassedT - ONE_HUNDRED;
  }
  while(ValuePassedT>= TEN){
    tensT++;
    ValuePassedT = ValuePassedT - TEN;
  }
  while(ValuePassedT>= ONE){
    onesT++;
    ValuePassedT = ValuePassedT - ONE;
  }
  thousandsT += HEX_TO_ASCII;
  hundredsT += HEX_TO_ASCII;
  tensT += HEX_TO_ASCII;
  onesT += HEX_TO_ASCII;
  ADC_Value[ZERO]=thousandsT;
  ADC_Value[ONE]=hundredsT;
  ADC_Value[TWO]=tensT;
  ADC_Value[THREE]=onesT;
  //strcpy(display_line[DISPLAY_UPDATE_TWO], ADC_Value);
  //update_string(display_line[DISPLAY_UPDATE_TWO], TWO);
}