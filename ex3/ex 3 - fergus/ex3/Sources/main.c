#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "pwm.h"
#include "input.h"



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
  
  while(1){
    Hi_count = Duty_Hi_Calculator();
  
  }

  
  Init_TC5();

	EnableInterrupts;


  
  
  //DDRT = 0x20;
  
  //read_analog();

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
