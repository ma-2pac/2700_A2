#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"

void main(void) {

  unsigned int time1, time2;
  int a, b, c; // change these from int to desired datatype to test
  long times[5];
  float ns[5];
  float timePerTick = 41.6; // time per tick in ns 41.6ns for prescaler = 1
  long oFval = 65536; // time elapsed per time overflow
  
  Init_TCNT(); // initialise timer
  
  a = 5;
  b = 10;
  resetOF();
  time1 = TCNT; // save initial time
  c = b + a;
  time2 = TCNT;
  times[0] = (time2 - time1) + (overFlows * oFval); //calculate period
  
  resetOF();
  time1 = TCNT; // save initial time
  c = b * a;
  time2 = TCNT;
  times[1] = (time2 - time1) + (overFlows * oFval); //calculate period
  
  resetOF();
  time1 = TCNT; // save initial time
  c = b / a;
  time2 = TCNT;
  times[2] = (time2 - time1) + (overFlows * oFval); //calculate period
  
  resetOF();
  time1 = TCNT; // save initial time
  c = sqrt(b);
  time2 = TCNT;
  times[3] = (time2 - time1) + (overFlows * oFval); //calculate period
  
  resetOF();
  time1 = TCNT; // save initial time
  c = sin(b);
  time2 = TCNT;
  times[4] = (time2 - time1) + (overFlows * oFval); //calculate period
  
  // calculate time elapsed for each function
  for(a = 0; a < 5; a++){
    ns[a] = times[a] * timePerTick; 
  }

  asm ("swi");

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}









