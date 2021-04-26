#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "stdlib.h"
#include "timers.h"
#include "timeFunc.h"
#include "serialPrint.h"
#include <stdio.h>
#include <string.h>
  
volatile int pos;
volatile int num;
volatile int rem, len = 0, n;
char str[500];

void tostring(char [], int);

void main(void) {
  int i;
  char start[] = "Operation, Int, Long, Double, Float\n";
  char add[100];
  char mult[100];
  char div[100];
  char sqrt[100];
  char sin[100];
  char cos[100];
  
  
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
  
  //stop the counter
  Stop_TCNT();

  //build the table for serial
   /* 
    operation,int16,long32,float32,double64
  add,int[0],long[0],float[0],double[0]
  mult,int[1],long[1],float[1],double[1]
  divide,int[2],long[2],float[2],double[2]
  sqrt,int[3],long[3],float[3],double[3]
  sin,int[4],long[4],float[4],double[4]
  cos,int[5],long[5],float[5],double[5]
  */
  sprintf(add, "addition%.2f,%.2f,%.2f,%.2f\n\r",timeInt[0],timeLong[0],timeFloat[0],timeDouble[0]);
  sprintf(mult, "multiplication, %.2f,%.2f,%.2f,%.2f\n\r",timeInt[1],timeLong[1],timeFloat[1],timeDouble[1]);  
  sprintf(div, "division, %.2f,%.2f,%.2f,%.2f\n\r",timeInt[2],timeLong[2],timeFloat[2],timeDouble[2]);
  sprintf(sqrt, "square root, %.2f,%.2f,%.2f,%.2f\n\r",timeInt[3],timeLong[3],timeFloat[3],timeDouble[3]);
  sprintf(sin, "sin, %.2f,%.2f,%.2f,%.2f\n\r",timeInt[4],timeLong[4],timeFloat[4],timeDouble[4]);
  sprintf(cos, "cos, %.2f,%.2f,%.2f,%.2f\n\r!",timeInt[5],timeLong[5],timeFloat[5],timeDouble[5]);
  
  
  //function that builds serial table 
  
  //initialise serial and print table for ex 1
  //use marcos code
  Init_sci(start, add, mult, div, sqrt, sin, cos);
  
  //initialise timer output channels 
  
  //enble interrupts
  EnableInterrupts;    


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}



void tostring(char str[], int num){
    
    n = num;
    while (n != 0){
        len++;
        n /= 10;
    }
    for (pos = 0; pos < len; pos++){
        rem = num % 10;
        num = num / 10;
        str[len - (pos + 1)] = rem + '0';
    }
    
    str[len] = '\0';
}









