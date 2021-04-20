#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "pwm.h"
#include "input.h"


void main(void) {

  //int analog_input;

  //call the timer function
  
  
  //Init_TC5();

	EnableInterrupts;

  //enable led 
  DDRB = 0xFF;
  DDRJ = 0xF;
  PTJ = 0x00; 
  DDRH = 0x00;
  DDRT = 0x20;
  
  read_analog();
  
  

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
