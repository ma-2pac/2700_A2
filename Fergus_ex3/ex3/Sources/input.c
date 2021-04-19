#include <stdio.h>

#include "derivative.h"      /* derivative-specific definitions */
#include "input.h"
#include <hidef.h>      /* common defines and macros */


void read_analog(void){

    int analog_input;

    
    DDRB = 0xFF;    //PORTB as output
    
    //DDRJ = 0xFF;    //PTJ as output for Dragon12+ LEDs
    //PTJ=0x0;        //Allow the LEDs to display data on PORTB pins
    
    ATD0CTL2 = 0x80;     //Turn on ADC,..No Interrupt
    MSDelay(1);	      //optional 	
    ATD0CTL3 = 0x08;  //one conversion, no FIFO
    ATD0CTL4 = 0xEB;  //8-bit resolu, 16-clock for 2nd phase,
                      //prescaler of 24 for Conversion Freq=1MHz
                      //prescaler values may become an error in the future  
    for(;;)
    {
      ATD0CTL5 = 0x87;  //Channel 7 (right justified, unsigned,single-conver,one chan only) 
		  // change this value for other channels.

      while(!(ATD0STAT0 & 0x80));
      analog_input = ATD0DR0L;  //dump it on LEDs
          
      //MSDelay(250);     /optional
    }
    
}

void MSDelay(unsigned int itime)
  {
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
  }













