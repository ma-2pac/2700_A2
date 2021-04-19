#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

//#include "pwm.h"


void main(void) {

  //call the timer function
  
/*  
  Init_TC5();
  
  */

	EnableInterrupts;

  //enable led 
  DDRB = 0xFF;
  DDRJ = 0xF;
  PTJ = 0x00; 
  DDRH = 0x00;
  DDRT = 0x20;
  


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
