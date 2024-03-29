
#include "macros.h"

void Init_ADC(void){
ADCCTL0 = FALSE;	// Reset
ADCCTL0 |= ADCSHT_2;	// 16 ADC clocks
ADCCTL0 |= ADCMSC;	// MSC
ADCCTL0 |= ADCON;	// ADC ON
ADCCTL2 = FALSE;	// Reset
ADCCTL1 |= ADCSHS_0;	// 00b = ADCSC bit
ADCCTL1 |= ADCSHP;	// ADC sample-and-hold SAMPCON signal from sampling timer. ADCCTL1 &= ~ADCISSH;	// ADC invert signal sample-and-hold.
ADCCTL1 |= ADCDIV_0;	// ADC clock divider - 000b = Divide by 1
ADCCTL1 |= ADCSSEL_0;	// ADC clock MODCLK
ADCCTL1 |= ADCCONSEQ_0;	// ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY	identifies a conversion is in process

// ADCCTL2 Register
ADCCTL2 = FALSE;	// Reset
ADCCTL2 |= ADCPDIV0;	// ADC pre-divider 00b = Pre-divide by 1
ADCCTL2 |= ADCRES_2;	// ADC resolution 10b = 12 bit (14 clock cycle conversion time) ADCCTL2 &= ~ADCDF;	// ADC data read-back format 0b = Binary unsigned.
ADCCTL2 &= ~ADCSR;	// ADC sampling rate 0b = ADC buffer supports up to 200 ksps

// ADCMCTL0 Register
ADCMCTL0 |= ADCSREF_0;	// VREF - 000b = {VR+ = AVCC and VR� = AVSS } ADCMCTL0 |= ADCINCH_5;	// V_THUMB (0x20) Pin 5 A5

ADCIE |= ADCIE0;	// Enable ADC conv complete interrupt
ADCCTL0 |= ADCENC;	// ADC enable conversion.
ADCCTL0 |= ADCSC;	// ADC start conversion.
}

