#include <stdio.h>

#include "derivative.h"      /* derivative-specific definitions */
#include <hidef.h>      /* common defines and macros */
#include "serialPrint.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"

void create_ascii_table(float* timeInt, float* timeLong, float* timeFloat,float* timeDouble){
  //initialise string arrays
  char start[100];
  char add[100];
  char mult[100];
  char div[100];
  char sqrt[100];
  char sin[100];
  char cos[100];
  char bar[100];
  char output[500];
  volatile int i=0;
  
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
  
  //editor to control how the table looks
  sprintf(SCIString, "%s%s%s%s%s%s%s", start,add, mult, div,sqrt,sin,cos);

}











