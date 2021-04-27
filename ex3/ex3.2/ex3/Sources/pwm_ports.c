#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "pwm_ports.h"



//choose which ports to enable for the pwm signal
void enable_ports(int port){

  //mainsection from book
  TSCR1 = 0x90; // enable TCNT and fast timer flag clear
  TSCR2 = 0x07; // disable TCNT interrupt, set prescaler to 128
  TFLG1 = 0xFF; // clear all cl flag
  
  switch(port){
    case 1: //no pins enables
      Init_TC1(); //enable port 1
      break;
    case 2:
      Init_TC2(); //enable port 2
      break;
    case 3:
      Init_TC3(); //enable port 3
      break;
    case 4:
      Init_TC4(); //enable port 4
      break;
    case 5:
      Init_TC5(); //enable port 5
      break;
    default:
      Init_TC5(); //enable port 5
      break;
  }
}


// configure port 1 for output
void Init_TC1 (void) {
   //configure 01c
   TIOS = 0x20; // enable OC1 function
   TCTL2 = 0x0C; //pull PT1 to high
   TIE = 0x02; //enable interrupt of channel 1
   
   TC1 = TCNT + 100;
   while(TFLG1 & TFLG1_C1F); // wait until OC0 pin go high after counting 2100   //debug
   TCTL2 = 0x04; // set OC1 pin action to toggle
   TC1 = TC1 + 900;   

}

// configure port 2 for output
void Init_TC2 (void) {
   //configure 02c
   TIOS = 0x04; // enable OC2 function
   TCTL2 = 0x30; //pull PT2 to high
   TIE = 0x04; //enable interrupt of channel 2
   
   TC2 = TCNT + 100;
   while(TFLG1 & TFLG1_C2F); // wait until OC0 pin go high after counting 2100   //debug
   TCTL2 = 0x10; // set OC5 pin action to toggle
   TC2 = TC2 + 900;
}

// configure port 3 for output
void Init_TC3 (void) {
   
   //configure 03c
   TIOS = 0x08; // enable OC3 function
   TCTL2 = 0xC0; // pull PT3 high
   TIE = 0x08; //enable interrupt of channel 3
   
   TC3 = TCNT + 100;
   while(TFLG1 & TFLG1_C3F); // wait until OC0 pin go high after counting 2100   //debug
   TCTL2 = 0x40; // set OC3 pin action to toggle
   TC3 = TC3 + 900;
}

// configure port 4 for output
void Init_TC4 (void) {
   
   //configure 04c
   TIOS = 0x10; // enable OC5 function
   TCTL1 = 0x03; //Pull PT4 to high
   TIE = 0x10; //enable interrupt of channel 4
   
   TC4 = TCNT + 100;
   while(TFLG1 & TFLG1_C4F); // wait until OC0 pin go high after counting 2100   //debug
   TCTL1 = 0x01; // set OC4 pin action to toggle
   TC4 = TC4 + 900;

}

// configure port 5 for output
void Init_TC5 (void) {   
   //configure 05c
   TIOS = 0x20; // enable OC5 function
   TCTL1 = 0x0C; //pull pin for PT5 high
   TIE = 0x20; //enable interrupt of channel 5
   
   TC5 = TCNT + 100;
   while(TFLG1 & TFLG1_C5F); // wait until OC0 pin go high after counting 2100   //debug
   TCTL1 = 0x04; // set OC5 pin action to toggle
   TC5 = TC5 + 900;
   HiorLo = 0;
}