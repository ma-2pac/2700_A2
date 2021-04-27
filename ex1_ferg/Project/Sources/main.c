#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "stdlib.h"
#include "timers.h"
#include "pwm.h"
#include "timeFunc.h"
#include "serialPrint.h"
#include <stdio.h>
#include <string.h>
#include "pwm_ports.h"  

//char str[500];

//void tostring(char [], int);

void main(void) {
  
  /******/
  //ex 1 initialisation variables
  int i;

  //variables for calculations
  long ticks;
  float timeInt[6];
  float timeLong[6];
  float timeFloat[6];
  float timeDouble[6];
  float timePerTick = 41.6; // time per tick in ns = 41.6ns for prescaler = 1
  
  //variables for storing calculations for printing to serial
  char start[100];
  char add[100];
  char mult[100];
  char div[100];
  char sqrt[100];
  char sin[100];
  char cos[100];
  char bar[100];
  
  //initialise timers for ex 1
  Init_TCNT();
  
  //run ex 1 calculations in main - not to disturb pwm interrupts
  for(i = 0; i < 6; i++){ //for integers
    ticks = timeFunc(i,0);
    timeInt[i] = ticks * timePerTick;
  }
  
  for(i = 0; i < 6; i++){ //for long integers
    ticks = timeFunc(i,1);
    timeLong[i] = ticks * timePerTick;
  }
  
  for(i = 0; i < 6; i++){ //for floats
    ticks = timeFunc(i,2);
    timeFloat[i] = ticks * timePerTick;
  }
  
  for(i = 0; i < 6; i++){ //for doubles
    ticks = timeFunc(i,3);
    timeDouble[i] = ticks * timePerTick;
  }
  
  //stop the counter
  Stop_TCNT();

  //copy results into strings for printing to serial
  sprintf(start, "  op|       Int|      Long|    Double|     Float\n\r");
  sprintf(add, "add | %10.2f|%10.2f|%10.2f|%10.2f\n\r",timeInt[0],timeLong[0],timeFloat[0],timeDouble[0]);
  sprintf(mult, "mult| %10.2f|%10.2f|%10.2f|%10.2f\n\r",timeInt[1],timeLong[1],timeFloat[1],timeDouble[1]);  
  sprintf(div, "div | %10.2f|%10.2f|%10.2f|%10.2f\n\r",timeInt[2],timeLong[2],timeFloat[2],timeDouble[2]);
  sprintf(sqrt, "sqrt| %10.2f|%10.2f|%10.2f|%10.2f\n\r",timeInt[3],timeLong[3],timeFloat[3],timeDouble[3]);
  sprintf(sin, "sin | %10.2f|%10.2f|%10.2f|%10.2f\n\r",timeInt[4],timeLong[4],timeFloat[4],timeDouble[4]);
  sprintf(cos, "cos | %10.2f|%10.2f|%10.2f|%10.2f\n\r!",timeInt[5],timeLong[5],timeFloat[5],timeDouble[5]);
  
  //create ascii bar for table
  for(i=0; i<(strlen(add)-2);i++){
    bar[i] = '-';
  }
  bar[i] = 10;
  bar[i+1] = 13;
  
  
  /******/
  //ex 2 and ex1 serial
  //initilise serial
  Init_sci(start, add, mult, div, sqrt, sin, cos, bar);
  
  
  
  /*****/
  //ex3 
  
  //enable leds for pwm visualisation 
  DDRB = 0xFF;
  DDRJ = 0xF;
  PTJ = 0x00; 
  DDRH = 0x00;
  
  //function called to initialise timers and output compare chanels ;
  enable_ports();
  
  
  //enble interrupts
  EnableInterrupts;    


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}











