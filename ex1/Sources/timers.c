#include "timers.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


void Init_TCNT (void) {
  // set up the timer
  TSCR1=0x90;
  TSCR2=0x80;
  resetOF;
}


void resetOF (void) {
  overFlows = 0; 
}

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TOF_ISR(void) { 
  
  overFlows = overFlows + 1;
  
}
