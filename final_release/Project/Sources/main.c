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
#include "asciitable.h"

//char str[500];

//void tostring(char [], int);

void main(void) {
  //select port for pwm
  int port;
  
  
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
  
  //screate as ascii formatted table which can be used as the first output of the serial  
  create_ascii_table(timeInt, timeLong, timeFloat, timeDouble);
  
   
  /******/
  //ex 2
  //initilise serial
  Init_sci();
  
  
  
  /*****/
  //ex3 
  //enable leds for pwm visualisation 
  DDRB = 0xFF;
  DDRJ = 0xF;
  PTJ = 0x00; 
  DDRH = 0x00;
  
  //function called to initialise timers and output compare chanels ;
  port =3;
  enable_ports(port);
  
  
  //enble interrupts
  EnableInterrupts;    


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}











