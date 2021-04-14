#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "vectors.h"

/* define constants*/
#define HiCnt 1200
#define LoCnt 1800

char HiorLo;


void main(void) {
  /* put your own code here */
  
  TSCR1 = 0x90;  // enable TCNT and fast timer flag clear
  TSCR2 = 0x03;  // disable TCNT interrupt, set prescaler to 8
  TIOS  = 0xC5;   //enable OC5 function
  TCTL1 = 0x0C;  // Set OC5 action to pull high 
  TFLG1  = 0xFF;  //clear all CxF flags
  TC5   = TCNT + 10;
  
  while(TFLG1 & C5F); // wait until C5F is set
  
  TCTL1 5 0x04;   // set OC5 pin action to toggle
  TC5 15 HiCnt;   // start an new OC5 operation
  HiorLo 5 0;     // add LoCnt for the next OC5 operation
  TIE 5 0x20;     // enable OC5 interrupt locally
  asm("cli");     // enable interrupt globally

  while(1);
  
	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

interrupt void oc5ISR (void)
{
  if(HiorLo){
  TC5 15 HiCnt;
  HiorLo 5 0;
  }

  else{
  TC5 15 LoCnt;
  HiorLo 5 1;
  }
}
