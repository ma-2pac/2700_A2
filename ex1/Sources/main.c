#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>

#include "timers.h"
#include "timeFunc.h"

void main(void) {
  int i;   
  long ticks;
  int length;
  // vectors for time elapsed by function
  float timeInt[6];
  float timeLong[6];
  float timeFloat[6];
  float timeDouble[6];
  float timePerTick = 41.6; // time per tick in ns = 41.6ns for prescaler = 1
  char buffer[512];   // buffer for serial output string
  
  Init_TCNT(); // initialise timer
  
  // loop over all 6 operations for int datatype and calculate time for each operation in ns 
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,0);
    timeInt[i] = ticks * timePerTick;
  }
  
  // loop over all 6 operations for long datatype and calculate time for each operation in ns 
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,1);
    timeLong[i] = ticks * timePerTick;
  }
  
  // loop over all 6 operations for float datatype and calculate time for each operation in ns 
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,2);
    timeFloat[i] = ticks * timePerTick;
  }
  
  // loop over all 6 operations for double datatype and calculate time for each operation in ns 
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,3);
    timeDouble[i] = ticks * timePerTick;
  }

  // kill timer and timer interrupts
  Stop_TCNT();
  
  
  length = 0;
  //write chars to buffer + length and inc. length by num of chars written
  for(i = 0; i < 6; i++){
    length += sprintf(buffer+length, "%.2f,%.2f,%.2f,%.2f\n",timeInt[i],timeLong[i],timeFloat[i],timeDouble[i]); 
  }
  
  // print tabulated data over serial
  serialPrint(&buffer);

  // loop forever
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}









