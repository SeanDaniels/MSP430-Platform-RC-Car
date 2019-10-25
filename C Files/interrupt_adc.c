#include "macros.h"

unsigned int CHANNEL = THUMB;

volatile unsigned int ADC_THUMB=FALSE;
volatile unsigned int V_DET_L=FALSE;
volatile unsigned int V_DET_R=FALSE;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
  case ADCIV_NONE:
    break;
  case ADCIV_ADCOVIFG:	// When a conversion result is written to the ADCMEM0
// before its previous conversion result was read.
    break;
  case ADCIV_ADCTOVIFG:
    break;// ADC conversion-time overflow break;
  case ADCIV_ADCHIIFG:	// Window comparator interrupt flags
    break;
  case ADCIV_ADCLOIFG:
    break;// Window comparator interrupt flag break;
  case ADCIV_ADCINIFG:
    break;// Window comparator interrupt flag break;
  case ADCIV_ADCIFG:
     ADCCTL0 &= ~ADCENC;
     switch(CHANNEL++){
       case THUMB:
         ADC_THUMB=ADCMEM0;
         ADCMCTL0 &= ~ADCINCH_5;
         ADCMCTL0 |= ADCINCH_2;
        break;
      case L_DET:
         V_DET_L=ADCMEM0;
         ADCMCTL0 &= ~ADCINCH_2;
         ADCMCTL0 |= ADCINCH_3;        
        break;
      case R_DET:
         V_DET_R=ADCMEM0;
         ADCMCTL0 &= ~ADCINCH_2;
         ADCMCTL0 |= ADCINCH_5;
         CHANNEL = FALSE;
        break;
  default: break;
     }
      
            // ADCMEM0 memory register with the conversion result
  ADCCTL0 |= ADCENC;
  ADCCTL0 |= ADCSC;
  break;// Channel A5 ADCCTL0 |= ADCSC;	// Start next sample break;
default: break;
}
}
