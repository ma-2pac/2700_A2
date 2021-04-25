#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "pwm.h"
#include "input.h"

#define START_CYCLE 1
#define WAIT_CYCLE 0


void main(void) {
  /* put your own code here */
  int Hi_count;
  
  //int analog_input;

  //call the timer function
  
  //enable led 
  DDRB = 0xFF;
  DDRJ = 0xF;
  PTJ = 0x00; 
  DDRH = 0x00;
  
  //Init_sci();
  
  Init_TC5();

	EnableInterrupts;
  
  
  //DDRT = 0x20;
  
  //read_analog();

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
