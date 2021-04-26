#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"
#include "timeFunc.h"

void main(void) {
  int i;
  long ticks;
  float timeInt[6];
  float timeLong[6];
  float timeFloat[6];
  float timeDouble[6];
  float timePerTick = 41.6; // time per tick in ns = 41.6ns for prescaler = 1
  
  Init_TCNT(); // initialise timer
    
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,0);
    timeInt[i] = ticks * timePerTick;
  }
  
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,1);
    timeLong[i] = ticks * timePerTick;
  }
  
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,2);
    timeFloat[i] = ticks * timePerTick;
  }
  
  for(i = 0; i < 6; i++){
    ticks = timeFunc(i,3);
    timeDouble[i] = ticks * timePerTick;
  }
  
  asm ("swi");

	EnableInterrupts;    


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}









