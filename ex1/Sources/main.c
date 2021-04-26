#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>

#include "timers.h"
#include "timeFunc.h"

void main(void) {
  int i;
  long ticks;
  int length;
  float timeInt[6];
  float timeLong[6];
  float timeFloat[6];
  float timeDouble[6];
  float timePerTick = 41.6; // time per tick in ns = 41.6ns for prescaler = 1
  char buffer[512];
  
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

  Stop_TCNT();
  
  length = 0;
  //write chars to buffer + length and inc length by num of chars written
  for(i = 0; i < 6; i++){
    length += sprintf(buffer+length, "%.2f,%.2f,%.2f,%.2f\n",timeInt[i],timeLong[i],timeFloat[i],timeDouble[i]); 
  }
   
  /*
  operation,int16,long32,float32,double64
  add,int[0],long[0],float[0],double[0]
  mult,int[1],long[1],float[1],double[1]
  divide,int[2],long[2],float[2],double[2]
  sqrt,int[3],long[3],float[3],double[3]
  sin,int[4],long[4],float[4],double[4]
  cos,int[5],long[5],float[5],double[5]
  */
  
  serialPrint(&buffer);
  
  //asm ("swi");

	//EnableInterrupts;    


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}









