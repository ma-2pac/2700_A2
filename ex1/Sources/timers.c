#include "timers.h"

// include the register/pin definitions

#include "derivative.h" // derivative-specific definitions

void Init_TCNT (void) {
  // set up the timer
  TSCR1=0x90; // enable timer counter, enable fast flag clear
  TSCR2=0x80; // enable TCNT overflow interrupt, set prescaler to 1
  resetOF; // reset overflow counter
}

void Stop_TCNT (void) {
  // set up the timer
  TSCR1=0x00; // enable timer counter, enable fast flag clear
  TSCR2=0x00; // enable TCNT overflow interrupt, set prescaler to 1
  resetOF; // reset overflow counter
}

void resetOF (void) {
  overFlows = 0; // set global overFlows variable to 0 
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED // Interrupt section for this module. Placement will be in NON_BANKED area.
__interrupt void TOF_ISR(void) { 
  overFlows = overFlows + 1; // increment global overFlows variable by 1
}