//------------------------------------------------------------------------------
//
//  Description: This file contains all the defines used in the program
//
//
//  Sean Daniels
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------ 
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

#define ZERO                           (0x00)
#define ONE                            (1)
#define TWO                            (2)
#define THREE                          (3)
#define FOUR                           (4)
#define FIVE                           (5)
#define SIX                            (6)
#define SEVEN                          (7)
#define EIGHT                          (8)
#define NINE                           (9)
#define TEN                            (10)
#define ELEVEN                         (11)
#define TWELVE                         (12)
#define THIRTEEN                       (13)
#define SIXTEEN                        (16)
#define TWENTY                         (20)
#define TWENTYONE                      (21)
#define TWENTY_FIVE                    (25)
#define FIFTY                          (50)
#define ONE_HUNDRED                    (100)
#define ONE_HUNDRED_FIFTY              (150)
#define TWO_HUNDRED                    (200)
#define FIVE_HUNDRED                    (500)
#define TWO_HUNDRED_FIFTY              (250)
#define ONE_THOUSAND                   (1000)
#define FIFTEEN_HUNDRED                (1500)
#define TWELVE_THOUSAND                (12000)
#define TWENTY_THOUSAND                (20000)
#define THIRTY_THOUSAND                (30000)
#define FORTY_THOUSAND                  (40000)

#define TWO_SECOND_PAUSE               (16)





#define TRUE                           (1)
#define FALSE                          (0)

#define USE_GPIO                       (0x00)
#define USE_SMCLK                      (0x01)

#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF    (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED)
#define ALWAYS                         (1)
#define RESET_STATE                    (0)
#define RED_LED                     (0x01) // RED LED 0
#define GRN_LED                     (0x40) // GREEN LED 1

#define DISPLAY_LINE_ROW_INIT 4
#define DISPLAY_LINE_COL_INIT 11
#define CHAR_DISPLAY_INIT 4

#define DISPLAY_UPDATE_ZERO 0
#define DISPLAY_UPDATE_ONE 1
#define DISPLAY_UPDATE_TWO 2
#define DISPLAY_UPDATE_THREE 3


#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)

//port init
#define DIR_INIT (0xff) // inititalize direction to 0xff
#define OUT_INIT (0x00) // initialize output to 0x00
// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2
#define V_DETECT_R (0x08) // 3
#define A4_SEEED (0x10) // 1 A4_SEEED
#define V_THUMB (0x20) // 5
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define P2_0 (0x01) // 0
#define P2_1 (0x02) // 1
#define P2_2 (0x04) // 2
#define SW2 (0x08) // 3 SW2
#define P2_4 (0x10) // 4
#define P2_5 (0x20) // 5
#define LFXOUT (0x40) // XOUTR
#define LFXIN (0x80) // XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA20 (0x02) // 1 Photodiode Circuit
#define OA2N (0x04) // 2 Photodiode Circuit
#define OA2P (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT (0x10) // 4 SMCLK
#define P3_5 (0x20) // 5
#define IOT_LINK (0x40) // 6 IOT_LINK
#define P3_7 (0x80) // 7


// port 4 pins
#define RESET_LCD (0x01) //0 LCD RESET
#define SW1 (0x02)// 1 SW1
#define UCA1RXD  (0x04)// 2 back channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output-UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

//port 5 pins
#define IOT_RESET (0x01)
#define P5_1 (0x02)
#define IOT_PROG_SEL (0x04)
#define IOT_PROG_MODE (0x08)
#define IR_LED (0x10)

//port 6 pins
#define R_FORWARD (0x01)
#define L_FORWARD (0x02)
#define R_REVERSE (0x04)
#define L_REVERSE (0x08)
#define LCD_BACKLITE (0x10)
#define P6_5 (0x20)
#define GREEN_LED (0x40)


//shape macros
#define NONE  ('N')
#define FIGURE_EIGHT  ('F')
#define CIRCLE  ('C')
#define TRIANGLE ('T')
#define WAIT  ('W')
#define START ('S')
#define RUN  ('R')
#define END  ('E')
#define RUNTWO ('P')
#define WAITCASETWO ('Z')
#define WHEEL_COUNT_TIME (50)
#define RIGHT_COUNT_TIME (7)
#define LEFT_COUNT_TIME (1000)
#define TRAVEL_DISTANCE (55)
#define FIG_TRAV (28)
#define WAITING2START (1000)
#define DELAYCIRCTWO (50)
#define RUNTHREE ('X')
#define RUNFOUR ('Y')



#define ANGLE_DIST (300)
#define LEG_DIST    (TRAVEL_DISTANCE/2)
#define GO_STRAIGHT_DIST_FOUR (4);
#define GO_STRAIGHT_DIST (3)
#define GO_STRAIGHT_COUNT (6)
#define STRAIGHT_R_COUNT (80)
#define STRAIGHT_L_COUNT (46)

#define BLINK_TIME (10)

#define TB0CCR0_INTERVAL  (10000) // 500000 / (1 / 20msec) MAIN TIMER
#define TB0CCR1_INTERVAL  (50000)// 500000/ (1/100msec) DEBOUNCE COUNTER
#define TB0CCR2_INTERVAL   (25000)// 50 msec BLINK

#define RANGE_OF_FLAG_VECTOR (14)
#define DEBOUNCE_DISPLAY (2)
#define DEBOUNCE_TIME (10)

#define DISPLAY_UPDATE_TIME (10)
#define THUMB (0)
#define L_DET (1)
#define R_DET (2)
#define HEX_TO_ASCII (0x30)
#define HEX_TO_ASCII_CUT (0x3A)

//AT HOME EDGES
//vdetl and vdetr are flipped
#define V_DET_L_EDGE (260)
#define V_DET_R_EDGE (230)

#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)

#define WHEEL_PERIOD (50000)
#define STARTING_PWM (50000)
#define TEN_PERCENT_SPEED (12000)
#define WHEEL_OFF (0)

#define APPROACHING_LINE  ('0')
#define LOOKING_FOR_LINE ('1')
#define ROTATE_RIGHT_AND_LOOK ('2')
#define FOLLOW_LINE (3)
//#define TURN_IN (9)

#define ON_LINE (1)
#define OFF_LINE (0)
#define ONLY_RIGHT (2) 
#define ONLY_LEFT (3)
#define DELAY_TIME_FOR_CAR_LOC_UPDATE (2)
#define CIRCLE_TIME (1000)

#define LOW ('L')
#define HIGH ('H')

#define HIGH_BAUD_RATE_CONTROL_REGISTER (1)
#define LOW_BAUD_RATE_CONTROL_REGISTER (4)
#define HIGH_MODULATION_CONTROL_REGISTER (0x4A11)
#define LOW_MODULATION_ONTROL_REGISTER (0x5551)
#define TIME_TO_RESTART_IOT             (1000)

#define BEGINNING	(0)
#define SMALL_RING_SIZE	(30)
#define LARGE_RING_SIZE (16)
#define sevfitty        (750)
#define VECTOR_INTERRUPT_RANGE (0x08)
#define TWO_DISPLAY_LINES (18)
#define LENGTH_OF_90_DEG_LEFT_TURN  (0x03);
#define TRAVEL_TIME_F_ONE        (0x08);
#define TRAVEL_TIME_F_TWO       (0x0E); 
// for pwm
//wheel period 40k - 60k


#define PAUSE             (1)
#define TURN_LEFT         (3)
#define MOVE_FORWARD      (2)
#define TURN_RIGHT        (4)